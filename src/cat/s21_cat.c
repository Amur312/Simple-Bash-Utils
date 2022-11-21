#include "s21_cat.h"

// argc -счетчик аргументов  *argv -указатель на 0 индекс каждого аргумента
int main(int argc, char *argv[]) {
  struct s_flag flags = {0};
  if (argc >= 2) {
    ParserFlag(argc, argv, &flags);
    OpenFile(argc, argv, flags);
  } else {
    printf("Please enter a filename\n");
  }
  return 0;
}

void ParserFlag(int argc, char *argv[], struct s_flag *flags) {
  struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                  {"number", 0, 0, 'n'},
                                  {"squeeze-blank", 0, 0, 's'},
                                  {0, 0, 0, 0}};
  int command = 0;
  int options = 0;

  while ((options = getopt_long(argc, argv, "benstvET", long_options,
                                &command)) != -1) {
    switch (options) {
    case 'b':
      flags->b = 1;
      break;
    case 'v':
      flags->v = 1;
      break;
    case 'e':
      flags->v = 1;
      flags->e = 1;
      break;
    case 'E':
      flags->e = 1;
      break;
    case 'n':
      flags->n = 1;
      break;
    case 's':
      flags->s = 1;
      break;
    case 't':
      flags->v = 1;
      flags->t = 1;
      break;
    case 'T':
      flags->t = 1;
      break;
    default:
      printf("error\n");
      break;
    }
  }
  if (flags->b == 1) {
    flags->n = 0;
  }
}

void OpenFile(int argc, char *argv[], struct s_flag flags) {
  int index_argv = 1;
  while (*argv[index_argv] == '-') {
    index_argv++;
  }

  for (int i = index_argv; i < argc; i++) {
    FILE *fd = fopen(argv[i], "r");
    if ((!fd)) {
      printf("cat: %s: No such file or directory\n", argv[i]);
    } else {
      PrintCat(fd, flags);
      fclose(fd);
    }
  }
}

void PrintCat(FILE *file, struct s_flag flags) {
  char ch = 0;
  int new_line = 1;
  int line = 1;
  int empty_lines = 0;
  while ((ch = fgetc(file)) != EOF) {
    if (flags.s) {
      if (ch == '\n') {
        ++empty_lines;
        if (empty_lines > 2) {
          continue;
        }
      } else {
        empty_lines = 0;
      }
    }
    if (flags.n && new_line) {
      printf("%6d\t", line);
      ++line;
      new_line = 0;
    }
    if (flags.b && new_line && ch != '\n') {
      printf("%6d\t", line);
      ++line;
      new_line = 0;
    }
    if (flags.e && ch == '\n') {
      printf("$");
    }
    if (flags.t && ch == '\t') {
      printf("^");
      ch = 'I';
    }
    if (flags.v && ch != '\n' && ch != '\t') {
      if (ch >= 0 && ch <= 31) {
        printf("^");
        ch += 64;
      } else if (ch == 127) {
        printf("^");
        ch -= 64;
      }
    }
    if (ch == '\n') {
      new_line = 1;
    }
    printf("%c", ch);
  }
}
