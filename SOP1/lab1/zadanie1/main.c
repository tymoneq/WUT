#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAX_PATH 256
#define ERR(source)                                                \
  (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), \
   exit(EXIT_FAILURE))

void usage(char* pname) {
  fprintf(stderr, "USAGE:%s -n Name -p OCTAL -s SIZE\n", pname);
  exit(EXIT_FAILURE);
}

struct node {
  struct node* next;
  char* dir_name;
};

struct node* add_to_list(char* dir_name, struct node* head) {
  struct node* new_node = (struct node*)malloc(sizeof(struct node));
  if (new_node == NULL) {
    ERR("Malloc failed");
  }
  new_node->dir_name = dir_name;
  new_node->next = head;

  return new_node;
}

void free_node(struct node* p) {
  free(p);
}

void print_info(struct node* head, int fd) {
  struct node* next_node = head;
  struct dirent* dp = NULL;
  struct stat filestat;
  DIR* dir;
  char full_path[1024];

  while (head != NULL) {
    dprintf(fd, "SCIEZKA:\n%s\n", head->dir_name);

    // listing DIR
    dir = opendir(head->dir_name);
    if (dir != NULL) {
      dprintf(fd, "LISTA PLIKÓW:\n");
      do {
        if ((dp = readdir(dir)) != NULL) {
          snprintf(full_path, sizeof(full_path), "%s/%s", head->dir_name,
                   dp->d_name);
          if (stat(full_path, &filestat))
            continue;
          dprintf(fd, "%s %ld\n", dp->d_name, filestat.st_size);
        }
      } while (dp != NULL);
    }
    closedir(dir);

    next_node = head->next;
    free_node(head);
    head = next_node;
  }
}

int main(int argc, char* argv[]) {
  int c;
  char* dir_name = NULL;
  char* out_file_name = NULL;
  struct node* head = NULL;
  int fd = -1;

  while ((c = getopt(argc, argv, "p:o:")) != -1) {
    switch (c) {
      case 'p': {
        dir_name = optarg;
        head = add_to_list(dir_name, head);
        break;
      }
      case 'o': {
        if (out_file_name == NULL) {
          out_file_name = optarg;
        } else {
          usage(argv[0]);
        }
        break;
      }
      default:
        usage(argv[0]);
    }
  }

  if (out_file_name != NULL) {
    fd = open(out_file_name, O_RDWR | O_TRUNC | O_CREAT, 0644);
    if (fd < 0)
      ERR("Couldn't open file");
  }

  if (fd > 0) {
    print_info(head, fd);
  } else {
    print_info(head, 1);
  }

  if (fd > 0) {
    close(fd);
  }
  return 0;
}
