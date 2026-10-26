#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define REQUIREMENTS "requirements"
#define MAX_PATH 256
#define ERR(source)                                                \
  (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), \
   exit(EXIT_FAILURE))

void usage(char* pname) {
  fprintf(stderr, "USAGE:%s -c Create -v ENV name -i Install -r Remove\n",
          pname);
  exit(EXIT_FAILURE);
}

struct node {
  char* env_name;
  struct node* next;
};

struct node* add_node(char* env_name, struct node* head) {
  struct node* new_node = (struct node*)malloc(sizeof(struct node));

  if (new_node == NULL) {
    ERR("Malloc failed");
  }
  new_node->env_name = env_name;
  new_node->next = head;
  return new_node;
}

void free_list(struct node* head) {
  struct node* next = NULL;
  while (head != NULL) {
    next = head->next;
    free(head);
    head = next;
  }
}

void create_envs(struct node* head) {
  struct node* cur = head;

  FILE* ptr;
  char full_path[MAX_PATH];

  while (cur != NULL) {
    int val = mkdir(cur->env_name, 0755);
    if (val == -1) {
      ERR("Problem creating DIR");
    }
    snprintf(full_path, sizeof(full_path), "%s/%s", cur->env_name,
             REQUIREMENTS);
    ptr = fopen(full_path, "w");
    if (ptr == NULL) {
      ERR("Error createing requirements file");
    }
    fclose(ptr);
    cur = cur->next;
  }
}

void create_package_file(char* file_path) {
  int fd = open(file_path, O_CREAT | O_WRONLY, 0444);

  if (fd < 0) {
    ERR("Creating package file");
  }

  write(fd, "adhfha", 6);

  close(fd);
}

void install_to_envs(struct node* head, const char* package_name) {
  struct node* cur = head;
  FILE* ptr;

  char package_name_copy[128];
  char full_path[MAX_PATH];

  strcpy(package_name_copy, package_name);

  char* res = strtok(package_name_copy, "=");

  while (cur != NULL) {
    snprintf(full_path, sizeof(full_path), "%s/%s", cur->env_name,
             REQUIREMENTS);

    FILE* fptr = fopen(full_path, "r");
    if (fptr == NULL) {
      fclose(fptr);
      ERR("ENV doesn't exist");
    }

    snprintf(full_path, sizeof(full_path), "%s/%s", cur->env_name, res);

    ptr = fopen(full_path, "r");
    // plik nie istnieje
    if (ptr == NULL) {
      create_package_file(full_path);
      snprintf(full_path, sizeof(full_path), "%s/%s", cur->env_name,
               REQUIREMENTS);

      FILE* fptr = fopen(full_path, "a+");
      if (fptr) {
        fprintf(fptr, "%s\n", package_name);
        fclose(fptr);
      }
    } else {
      fclose(ptr);
      ERR("Package already exist");
    }

    cur = cur->next;
  }
}

void remove_file(char* file_path) {
  if (remove(file_path) != 0) {
    ERR("Unable to delete the file.");
  }
}
void remove_package(FILE* fptr, FILE* ftemp, char* package) {
  char buf[128];
  while (fscanf(fptr, "%s", buf) == 1) {
    if (strstr(buf, package) != 0) {
    } else {
      fprintf(ftemp, "%s\n", buf);
    }
  }
}
void remove_from_envs(struct node* head, const char* package_name) {
  struct node* cur = head;
  FILE* ptr;

  char package_name_copy[128];
  char full_path[MAX_PATH];
  char temp_file[MAX_PATH];

  strcpy(package_name_copy, package_name);

  char* res = strtok(package_name_copy, "=");

  while (cur != NULL) {
    snprintf(full_path, sizeof(full_path), "%s/%s", cur->env_name,
             REQUIREMENTS);

    FILE* fptr = fopen(full_path, "r");
    if (fptr == NULL) {
      fclose(fptr);
      ERR("ENV doesn't exist");
    }

    snprintf(full_path, sizeof(full_path), "%s/%s", cur->env_name, res);

    ptr = fopen(full_path, "r");
    // plik istnieje
    if (ptr != NULL) {
      fclose(ptr);
      remove_file(full_path);

      snprintf(full_path, sizeof(full_path), "%s/%s", cur->env_name,
               REQUIREMENTS);

      FILE* fptr = fopen(full_path, "rw+");

      snprintf(temp_file, sizeof(temp_file), "%s/%s", cur->env_name, "tmp");
      FILE* ftmp = fopen(temp_file, "w");

      if (ftmp == NULL) {
        ERR("Creating temp file");
      }

      if (fptr) {
        remove_package(fptr, ftmp, res);
        fclose(fptr);
        fclose(ftmp);

        snprintf(full_path, sizeof(full_path), "%s/%s", cur->env_name,
                 REQUIREMENTS);
        remove_file(full_path);
        rename(temp_file, full_path);
      }

    } else {
      ERR("Package doesn't exist");
    }
    cur = cur->next;
  }
}

int main(int argc, char* argv[]) {
  int c;
  char* env_name = NULL;
  int install_flag = 0;
  char* package_name = NULL;
  int remove_flag = 0;
  int create_flag = 0;

  struct node* head = NULL;

  while ((c = getopt(argc, argv, "i:v:r:c")) != -1) {
    switch (c) {
      case 'c': {
        if (create_flag == 0) {
          create_flag = 1;
        } else {
          usage(argv[0]);
        }
        break;
      }
      case 'v': {
        env_name = optarg;
        head = add_node(env_name, head);
        break;
      }
      case 'i': {
        if (install_flag == 0 && package_name == NULL) {
          install_flag = 1;
          package_name = optarg;
        } else {
          usage(argv[0]);
        }
        break;
      }
      case 'r': {
        if (remove_flag == 0 && package_name == NULL) {
          remove_flag = 1;
          package_name = optarg;
        } else {
          usage(argv[0]);
        }
        break;
      }
    }
  }

  if (create_flag) {
    create_envs(head);
  }

  if (install_flag) {
    install_to_envs(head, package_name);
  }

  else if (remove_flag) {
    remove_from_envs(head, package_name);
  }

  free_list(head);

  return 0;
}
