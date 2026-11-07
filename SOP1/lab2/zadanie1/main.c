#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ERR(source)                                                \
  (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), \
   exit(EXIT_FAILURE))

#define FILE_BUF_LEN 256

void usage(const char* const pname) {
  fprintf(stderr, "USAGE:%s path_1 path_2\n", pname);
  exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    usage(argv[0]);
  }

  int fd_source = open(argv[1], O_RDONLY);
  if (fd_source < 0) {
    ERR("Source file doesn't exist");
  }
  int fd_destination = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd_destination < 0) {
    ERR("Something went wrong when opening destination file");
  }

  char buf[FILE_BUF_LEN];

  ssize_t read_bytes = 0;

  while ((read_bytes = read(fd_source, buf, FILE_BUF_LEN)) != -1) {
    if (read_bytes == 0) {
      break;
    }

    ssize_t write_bytes = write(fd_destination, buf, read_bytes);
    if (write_bytes != read_bytes) {
      printf("Something went wrong read %ld bytes but wrote only %ld",
             read_bytes, write_bytes);
    }
  }

  close(fd_source);
  close(fd_destination);
  return 0;
}