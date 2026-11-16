#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define NUM_OF_LINES 32
#define LINE_SIZE 64

#define ERR(source)                                                \
  (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), \
   exit(EXIT_FAILURE))

void usage(char* pname) {
  fprintf(stderr, "USAGE:%s recipe tower1 [tower 2 ...]\n", pname);
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
    off_t currentPosition = lseek(fd, 0, SEEK_CUR);
    off_t size = lseek(fd, 0, SEEK_END);
    lseek(fd, currentPosition, SEEK_SET);

    if (size != 2048) {
      ERR("Ta ksiega to nie przepis!");
    }

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
  }
  return fd;
}

int open_babcia(const char* tower) {
  int fd = open(tower, O_RDONLY);
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

void read_babcia(int babcia_fd, int recipe_fd) {
  char read_buf[128];
  char line_buf[512];
  size_t line_len = 0;
  ssize_t bytes_read;

  while ((bytes_read = read(babcia_fd, read_buf, sizeof(read_buf))) > 0) {
    for (ssize_t i = 0; i < bytes_read; i++) {
      if (read_buf[i] == '\n') {
        line_buf[line_len] = '\0';
        proces_line(line_buf, line_len, recipe_fd);
        line_len = 0;
      } else if (line_len < sizeof(line_buf) - 1 && read_buf[i] != '\0') {
        line_buf[line_len++] = read_buf[i];
      }
    }
  }
  if (line_len > 0) {
    line_buf[line_len] = '\0';
    fprintf(stderr, "Babcia się zagadała: %s\n", line_buf);
  }
}
int main(int argc, char* argv[]) {
  if (argc < 2) {
    usage(argv[0]);
  }

  int fd = open_recipe(argv[1]);

  int fd_babcia = open_babcia(argv[2]);

  read_babcia(fd_babcia, fd);

  if (fd > 0)
    close(fd);

  if (fd_babcia > 0)
    close(fd_babcia);

  return 0;
}
