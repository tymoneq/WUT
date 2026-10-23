#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PATH 1024

#define ERR(source)                                                \
  (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), \
   exit(EXIT_FAILURE))

void usage(char* pname) {
  fprintf(stderr, "USAGE:%s -n Name -p OCTAL -s SIZE\n", pname);
  exit(EXIT_FAILURE);
}

struct node {
  char* dir_name;
  struct node* next;
};

struct node* add_to_list(char* dir_name, struct node* head) {
  struct node* new_node = (struct node*)malloc(sizeof(struct node));
  if (new_node == NULL)
    ERR("Malloc failed");

  new_node->next = head;
  new_node->dir_name = dir_name;
  return new_node;
}

int valid_extension(char* name, char* extension) {
  if (extension == NULL)
    return 1;

  const char* dot = strrchr(name, '.');

  if (!dot || dot == name)
    return 0;

  dot = dot + 1;
  return strcmp(dot, extension) == 0;
}

void list_dir(DIR* dir, int fd, int depth, char* extension, char* dir_name) {
  dprintf(fd, "Path: %s\n", dir_name);

  struct dirent* dp;
  struct stat filestat;
  char full_path[MAX_PATH];

  do {
    if ((dp = readdir(dir)) != NULL) {
      snprintf(full_path, sizeof(full_path), "%s/%s", dir_name, dp->d_name);
      if (stat(full_path, &filestat) == -1)
        continue;

      if (S_ISREG(filestat.st_mode)) {
        if (valid_extension(dp->d_name, extension) == 1) {
          dprintf(fd, "%s %ld\n", dp->d_name, filestat.st_size);
        }
      } else if (S_ISDIR(filestat.st_mode) && depth > 1) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
          continue;

        DIR* child_dir = opendir(full_path);

        if (child_dir == NULL) {
          perror("Error opening dir");
          continue;
        }
        list_dir(child_dir, fd, depth - 1, extension, full_path);
        if (child_dir)
          closedir(child_dir);
      }
    }
  } while (dp != NULL);
}

void print_dir(struct node* head, int fd, int depth, char* extension) {
  struct node* next = NULL;
  DIR* dir;
  while (head != NULL) {
    dir = opendir(head->dir_name);
    if (dir == NULL) {
      perror("Error opening dir");
      continue;
    }
    list_dir(dir, fd, depth, extension, head->dir_name);

    next = head->next;
    free(head);
    head = next;
    if (dir != NULL)
      closedir(dir);
  }
}

int set_out_file() {
  char* env = getenv("L1_OUTPUTFILE");
  if (env) {
    int fd = open(env, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (fd > 0)
      return fd;
  }
  return -1;
}

int main(int argc, char* argv[]) {
  int c;
  char* extension = NULL;
  char* dir_name = NULL;
  int o_flag = 0;
  int d = 1;
  struct node* head = NULL;
  int fd = -1;

  //  head = add_to_list("/home/tymon/coding/Kaleidoscope", head);
  //  d = 2;

  while ((c = getopt(argc, argv, "p:e:d:o")) != -1) {
    switch (c) {
      case 'p': {
        dir_name = optarg;
        head = add_to_list(dir_name, head);
        break;
      }
      case 'd': {
        if (d == 1) {
          d = strtol(optarg, (char**)NULL, 10);
        } else {
          usage(argv[0]);
        }
        break;
      }
      case 'e': {
        if (extension == NULL) {
          extension = optarg;

        } else {
          usage(argv[0]);
        }
        break;
      }
      case 'o': {
        if (o_flag == 0) {
          o_flag = 1;
          fd = set_out_file();
        } else {
          usage(argv[0]);
        }
        break;
      }
    }
  }

  if (fd > 0) {
    print_dir(head, fd, d, extension);
    close(fd);
  } else {
    print_dir(head, 1, d, extension);
  }
  return 0;
}
