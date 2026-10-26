#define _XOPEN_SOURCE 700

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>

#define AUTHOR "author"
#define TITLE "title"
#define GENRE "genre"

#define ERR(source)                                                \
  (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), \
   exit(EXIT_FAILURE))

// join 2 path. returned pointer is for newly allocated memory and must be freed
char* join_paths(const char* path1, const char* path2) {
  char* res;
  const int l1 = strlen(path1);
  if (path1[l1 - 1] == '/') {
    res = malloc(strlen(path1) + strlen(path2) + 1);
    if (!res)
      ERR("malloc");
    strcpy(res, path1);
  } else {
    res =
        malloc(strlen(path1) + strlen(path2) + 2);  // additional space for "/"
    if (!res)
      ERR("malloc");
    strcpy(res, path1);
    res[l1] = '/';
    res[l1 + 1] = 0;
  }
  return strcat(res, path2);
}

void usage(int argc, char** argv) {
  (void)argc;
  fprintf(stderr, "USAGE: %s path\n", argv[0]);
  exit(EXIT_FAILURE);
}

void print_file_data(FILE* fptr) {
  char* line = NULL;
  char line_copy[1024];
  size_t len = 0;
  ssize_t nread;
  char* author = NULL;
  char* title = NULL;
  char* genre = NULL;

  char* key;
  char* val;

  while ((nread = getline(&line, &len, fptr)) != -1) {
    strcpy(line_copy, line);

    key = strtok(line_copy, ":");
    val = strtok(NULL, ":");

    if (strcmp(key, AUTHOR) == 0) {
      author = (char*)malloc(strlen(val) + 1);
      strcpy(author, val);
    } else if (strcmp(key, TITLE) == 0) {
      title = (char*)malloc(strlen(val) + 1);
      strcpy(title, val);
    } else if (strcmp(key, GENRE) == 0) {
      genre = (char*)malloc(strlen(val) + 1);
      strcpy(genre, val);
    }
  }

  printf("author: ");
  if (author) {
    printf("%s", author);
    free(author);
  } else {
    printf("unknown\n");
  }

  printf("title: ");
  if (title) {
    printf("%s", title);
    free(title);
  } else {
    printf("unknown\n");
  }

  printf("genre: ");
  if (genre) {
    printf("%s", genre);
    free(genre);
  } else {
    printf("unknown\n");
  }

  if (line)
    free(line);
}

void read_data_from_file(char* file) {
  FILE* fptr = fopen(file, "r");
  if (fptr == NULL) {
    ERR("Error while opening a file");
  }
  print_file_data(fptr);

  fclose(fptr);
}

int main(int argc, char** argv) {
  if (argc != 2) {
    usage(argc, argv);
  }

  char* file = argv[1];
  read_data_from_file(file);

  return 0;
}
