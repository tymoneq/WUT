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

  ssize_t read_bytes = 0;
  char read_buf[128];
  while ((read_bytes = read(fd, read_buf, LINE_SIZE)) > 0) {
    int num = (read_buf[0] - '0') * 10 + read_buf[1] - '0';
    // if (num < 0 || num > 31) {
    //   continue;
    // }
    write(0, &read_buf, LINE_SIZE);
  }
  if (read_bytes < 0) {
    ERR("Error when reading from babcia");
  }

  return fd;
}
int main(int argc, char* argv[]) {
  if (argc < 2) {
    usage(argv[0]);
  }

  int fd = open_recipe(argv[1]);

  int fd_babcia = open_babcia(argv[2]);

  if (fd > 0)
    close(fd);

  if (fd_babcia > 0)
    close(fd_babcia);

  return 0;
}
