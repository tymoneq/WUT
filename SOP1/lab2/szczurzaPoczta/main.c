#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>

#define MAX_FIFOS 5
#define BATCH_BYTES 10
#define TIMEOUT 100

#define ERR(source)                                                \
  (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), \
   exit(EXIT_FAILURE))
void usage(char* pname) {
  fprintf(stderr, "USAGE:%s smbox file [fifo ... fifon]\n", pname);
  exit(EXIT_FAILURE);
}

struct node {
  unsigned char header_size;
  unsigned char message_size;
  char* header;
  char* message;

  struct node* next;
  struct node* prev;
};

struct node* add_new(struct node* tail,
                     unsigned char header_size,
                     unsigned char message_size,
                     char* header,
                     char* message) {
  struct node* new_node = (struct node*)malloc(sizeof(struct node));

  new_node->header_size = header_size;
  new_node->message_size = message_size;
  new_node->header = header;
  new_node->message = message;
  new_node->prev = tail;
  new_node->next = NULL;
  if (tail != NULL)
    tail->next = new_node;
  return new_node;
}

void free_list(struct node* head) {
  struct node* next;
  while (head != NULL) {
    if (head->message)
      free(head->message);
    if (head->header)
      free(head->header);
    next = head->next;
    free(head);
    head = next;
  }
}

void set_nonblocking(int fd) {
  int flags = fcntl(fd, F_GETFL);
  if (flags == -1) {
    ERR("fcntl");
  }
  flags |= O_NONBLOCK;
  if (fcntl(fd, F_SETFL, flags) == -1) {
    ERR("setting non blocking");
  }
}
off_t get_file_size(int fd) {
  off_t smbox_size = lseek(fd, 0, SEEK_END);
  if (smbox_size <= 0) {
    ERR("lseek");
  }

  lseek(fd, 0, SEEK_SET);
  return smbox_size;
}

void h_action(struct node* current, struct node* head, int fd) {
  fflush(NULL);
  int cnt = 0;
  for (struct node* p = head; p != NULL; p = p->next) {
    cnt++;
  }
  if (cnt == 0)
    return;

  struct iovec* iov = malloc(sizeof(struct iovec) * (cnt * 3));
  if (iov == NULL)
    ERR("malloc");

  int cur = 0;
  for (struct node* p = head; p != NULL; p = p->next) {
    if (p == current) {
      iov[cur].iov_base = "-> ";
      iov[cur].iov_len = 3;
      cur++;
    }
    iov[cur].iov_base = p->header;
    iov[cur].iov_len = p->header_size - 1;
    cur++;

    iov[cur].iov_base = "\n";
    iov[cur].iov_len = 1;
    cur++;
  }

  if (writev(STDOUT_FILENO, iov, cur) < 0) {
    free(iov);
    ERR("writev");
  }
  free(iov);
}
void run(int fd, struct node* head) {
  set_nonblocking(0);
  struct pollfd fds[2] = {{0, POLLIN, 0}};
  nfds_t num_of_descriptors = 1;

  off_t smbox_size = get_file_size(fd);

  char intput_buf[BATCH_BYTES];

  struct node* current = head;
  while (1) {
    int ret = poll(fds, num_of_descriptors, TIMEOUT);

    if (ret == -1) {
      ERR("poll");
    }
    if (ret == 0) {
      continue;
    }
    if (!(fds[0].revents & POLLIN)) {
      continue;
    }
    int read_bytes = read(0, intput_buf, BATCH_BYTES);

    if (read_bytes == -1) {
      if (errno == EINTR || errno == EAGAIN)
        continue;
      ERR("read");
    }
    if (read_bytes == 0)
      break;

    for (int i = 0; i < read_bytes; i++) {
      switch (intput_buf[i]) {
        case 'w': {
          if (current->prev != NULL) {
            current = current->prev;
            h_action(current, head, fd);
          }

          break;
        }
        case 's': {
          if (current->next != NULL) {
            current = current->next;
            h_action(current, head, fd);
          }

          break;
        }
        case 'd': {
          fflush(NULL);
          char* mem = mmap(NULL, smbox_size, PROT_READ | PROT_WRITE,
                           MAP_PRIVATE, fd, 0);

          if (mem == MAP_FAILED) {
            ERR("mmap");
          }

          int wrote_bytes = 0;
          int write_size = 0;
          while (wrote_bytes < smbox_size) {
            if (wrote_bytes + BATCH_BYTES <= smbox_size) {
              write_size = BATCH_BYTES;
            } else {
              write_size = smbox_size - wrote_bytes;
            }
            int code = write(1, mem + wrote_bytes, write_size);
            if (code == -1) {
              ERR("write");
            }
            wrote_bytes += code;
          }

          munmap(mem, smbox_size);
          fflush(NULL);
          break;
        }
        case 'h': {
          h_action(current, head, fd);
          break;
        }
        case 'm': {
          fflush(NULL);
          struct iovec iov[4] = {
              {current->header, current->header_size - 1},
              {"\n", 1},
              {current->message, current->message_size - 1},
              {"\n", 1},
          };
          if (writev(STDOUT_FILENO, iov, 4) < 0) {
            ERR("writev");
          }
          fflush(NULL);
          break;
        }
        case 'q': {
          if (fd > 0)
            close(fd);
          free_list(head);
          exit(0);
        }
        case '\n': {
          continue;
        }
        default: {
          printf("Invalid input\n");
        }
      }
    }
    fflush(NULL);
  }
}

void process_file(int fd, struct node** tail) {
  off_t smbox_size = get_file_size(fd);
  off_t current_offset = 0;

  unsigned char header_buf[2];
  while (current_offset < smbox_size) {
    if (read(fd, header_buf, 2) != 2) {
      ERR("read");
    }

    if (header_buf[0] < 2 || header_buf[1] < 2)
      ERR("Wrong header");
    char* header = (char*)malloc(header_buf[0]);
    char* message = (char*)malloc(header_buf[1]);
    if (header == NULL || message == NULL)
      ERR("malloc failed");

    ssize_t read_bytes = read(fd, header, header_buf[0]);
    if (read_bytes == -1 || read_bytes != header_buf[0])
      ERR("read");
    read_bytes = read(fd, message, header_buf[1]);
    if (read_bytes == -1 || read_bytes != header_buf[1])
      ERR("read");

    if (header[header_buf[0] - 1] != '\0' || message[header_buf[1] - 1] != '\0')
      ERR("Wrong header");

    *tail = add_new(*tail, header_buf[0], header_buf[1], header, message);

    current_offset += (off_t)2 + (off_t)header_buf[0] + (off_t)header_buf[1];
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    usage(argv[0]);
  }

  int fd = open(argv[1], O_RDONLY);

  if (fd < 0) {
    ERR("Open");
  }
  struct node* head = NULL;
  struct node* tail = NULL;

  process_file(fd, &tail);

  struct node* p = tail;
  while (p->prev != NULL) {
    p = p->prev;
  }
  head = p;

  run(fd, head);

  if (fd > 0)
    close(fd);
  free_list(head);

  return 0;
}
