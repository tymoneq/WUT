#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define NUM_OF_LINES 32
#define LINE_SIZE 64

#define ERR(source)                                                \
  (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), \
   exit(EXIT_FAILURE))

struct Tower {
  char read_buf[128];
  char line_buf[512];
  size_t line_len;
};

void usage(char* pname) {
  fprintf(stderr, "USAGE:%s recipe tower1 [tower2 ... tower5]\n", pname);
  exit(EXIT_FAILURE);
}

int open_recipe(const char* file) {
  int fd = open(file, O_RDWR | O_CREAT | O_EXCL, 0644);
  if (fd < 0) {
    if (errno == EEXIST) {
      fd = open(file, O_RDWR);
    }
    if (fd < 0) {
      ERR("ERROR opening recipe file");
    }
    off_t size = lseek(fd, 0, SEEK_END);
    if (size != 2048) {
      ERR("Ta ksiega to nie przepis!");
    }
    lseek(fd, 0, SEEK_SET);

  } else {
    char buf[LINE_SIZE];
    for (int i = 0; i < LINE_SIZE - 1; i++)
      buf[i] = ' ';
    buf[LINE_SIZE - 1] = '\n';

    for (int i = 0; i < NUM_OF_LINES; i++) {
      ssize_t bytes_wrote = write(fd, buf, LINE_SIZE);
      if (bytes_wrote != LINE_SIZE) {
        ERR("Something went wrong when writing to a file");
      }
    }
    lseek(fd, 0, SEEK_SET);
  }
  return fd;
}

int open_babcia(const char* tower) {
  int fd = open(tower, O_RDONLY | O_NONBLOCK);
  char error_message[256];
  snprintf(error_message, sizeof(error_message), "Nie ma babci na wieży %s",
           tower);
  struct stat buf;
  int ret = stat(tower, &buf);

  if (fd < 0 || ret == -1 || !(S_ISFIFO(buf.st_mode))) {
    ERR(error_message);
  }

  return fd;
}

void proces_line(char* line_buf, ssize_t line_len, int recipe_fd) {
  if (line_len < 3 || !isdigit((unsigned char)line_buf[0]) ||
      !isdigit((unsigned char)line_buf[1]) || line_buf[2] != ':') {
    fprintf(stderr, "Babcia się zagadała: %s\n", line_buf);
    return;
  }
  char line_num_buf[3];
  line_num_buf[2] = '\0';
  memcpy(line_num_buf, line_buf, 2);
  int line_num = (line_buf[0] - '0') * 10 + line_buf[1] - '0';
  if (line_num < 0 || line_num > 31) {
    fprintf(stderr, "Babcia się zagadała: %s\n", line_buf);
    return;
  }

  size_t content_len = line_len - 3;
  if (content_len > LINE_SIZE - 1) {
    content_len = LINE_SIZE - 1;
  }

  char write_buf[LINE_SIZE];
  memset(write_buf, ' ', LINE_SIZE);
  memcpy(write_buf, line_buf + 3, content_len);
  write_buf[LINE_SIZE - 1] = '\n';

  off_t offset = line_num * LINE_SIZE;

  if (lseek(recipe_fd, offset, SEEK_SET) == -1) {
    ERR("Error when doing lseek");
  }
  if (write(recipe_fd, write_buf, LINE_SIZE) == -1) {
    ERR("Error writing recipe");
  }
  printf("Krok %s zapisany\n", line_num_buf);
}

void read_babcia(int babcia_fd, int recipe_fd, struct Tower* tower) {
  ssize_t bytes_read;

  while ((bytes_read =
              read(babcia_fd, tower->read_buf, sizeof(tower->read_buf))) > 0) {
    for (ssize_t i = 0; i < bytes_read; i++) {
      if (tower->read_buf[i] == '\n') {
        tower->line_buf[tower->line_len] = '\0';
        proces_line(tower->line_buf, tower->line_len, recipe_fd);
        tower->line_len = 0;
      } else if (tower->line_len < sizeof(tower->line_buf) - 1 &&
                 tower->read_buf[i] != '\0') {
        tower->line_buf[tower->line_len++] = tower->read_buf[i];
      }
    }
  }
  if (tower->line_len > 0) {
    tower->line_buf[tower->line_len] = '\0';
    fprintf(stderr, "Babcia się zagadała: %s\n", tower->line_buf);
  }
}

void replace_berries(int recipe_fd) {
  const size_t file_size = 2048;
  const char* oldword = "raw~berries";
  const char* newword = "raspberries";
  const size_t word_len = 11;
  int empty_lines = 0;
  int swap_counter = 0;

  char* map =
      mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, recipe_fd, 0);
  if (map == MAP_FAILED) {
    ERR("map failed");
  }

  for (size_t i = 0; i < file_size - word_len; i++) {
    if (memcmp(oldword, map + i, word_len) == 0) {
      memcpy(map + i, newword, word_len);
      swap_counter++;
      i += word_len - 1;
    }
  }
  char print_buf[LINE_SIZE + 4];
  print_buf[2] = ':';
  print_buf[LINE_SIZE + 3] = '\0';

  for (size_t i = 0; i < NUM_OF_LINES; i++) {
    int offset = i * LINE_SIZE;
    if (strncmp(map + offset, " ", 1) == 0) {
      empty_lines++;
      continue;
    }
    print_buf[0] = i / 10 + '0';
    print_buf[1] = i % 10 + '0' + 1;

    memcpy(print_buf + 3, map + offset, LINE_SIZE);
    for (int j = sizeof(print_buf) - 2; j >= 0; j--) {
      if (print_buf[j] != ' ' && print_buf[j] != '\n') {
        print_buf[j + 1] = '\0';
        break;
      }
    }

    printf("%s\n", print_buf);
  }

  printf("Brudy księżniczki Joanny wyczyszczone: %d\n", swap_counter);
  if (empty_lines > 0) {
    printf("Brakuje %d kroków, tort sie zapadnie!\n", empty_lines);
  } else {
    printf("Tort gotowy!\n");
  }

  munmap(map, file_size);
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    usage(argv[0]);
  }

  int fd = open_recipe(argv[1]);

  nfds_t babcia_count = argc - 2;
  struct pollfd* fds =
      (struct pollfd*)malloc(sizeof(struct pollfd) * babcia_count);

  if (fds == NULL) {
    ERR("Error when malloc memory for fds");
  }

  struct Tower* towers =
      (struct Tower*)malloc(sizeof(struct Tower) * babcia_count);

  if (towers == NULL)
    ERR("Error malloc towers");
  for (unsigned int i = 0; i < babcia_count; i++) {
    fds[i].fd = open_babcia(argv[2 + i]);
    fds[i].events = POLLIN;
    fds[i].revents = 0;
    towers[i].line_len = 0;
  }

  unsigned int active_towers = babcia_count;
  while (active_towers > 0) {
    int ready = poll(fds, babcia_count, 3000);

    if (ready == -1) {
      ERR("poll");
    }
    if (ready == 0) {
      printf("Babcie dolewają herbatki…\n");
      continue;
    }

    for (unsigned int i = 0; i < babcia_count; i++) {
      if (fds[i].fd < 0)
        continue;
      if (fds[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
        close(fds[i].fd);
        fds[i].fd = -1;
        active_towers--;
        continue;
      }
      if (!(fds[i].revents & POLLIN))
        continue;
      read_babcia(fds[i].fd, fd, &towers[i]);
    }
  }

  replace_berries(fd);

  if (fd > 0)
    close(fd);
  for (unsigned int i = 0; i < babcia_count; i++)
    if (fds[i].fd > 0)
      close(fds[i].fd);

  if (towers)
    free(towers);

  if (fds)
    free(fds);

  return 0;
}
