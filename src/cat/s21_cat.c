#include "s21_cat.h"

// argc -счетчик аргументов  *argv -указатель на 0 индекс каждого аргумента
int main(int argc, char *argv[]) {
  struct s_flag flags = {0};
  if (argc == 1) {
    parsStr(STDIN_FILENO);
  } else {
    ParserFlag(argc, argv, &flags);
    OpenFile(argc, argv, flags);
  }
  return 0;
}

void parsStr(
    int file_dict) {  // когда пользователь вводит просто саt без аргументов
  char buff[4096];
  int byte_read;
  byte_read = read(file_dict, buff, 4096);  // read return error -1
  while (byte_read > 0) {
    printf("%.*s", byte_read, buff);
    byte_read = read(file_dict, buff, 4096);
  }
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
  int number = 1;
  char pr_ch = 0;
  while ((ch = fgetc(file)) != EOF) {
    if (flags.s) {
      if (ch == '\n') {
        ++pr_ch;
        if (pr_ch > 2) {
          continue;
        }
      } else {
        pr_ch = 0;
      }
    }
    if (flags.b) {
      if (new_line) {
        if (ch != '\n') {
          printf("%6d\t", number++);
          new_line = 0;
        }
      }
      if (ch == '\n')
        new_line = 1;
    }
    if (flags.e) {
      if (ch == '\n')
        printf("%c", '$');
    }
    if (flags.n) {
      if (new_line) {
        printf("%6d\t", number++);
        new_line = 0;
      }
      if (ch == '\n')
        new_line = 1;
    }

    if (flags.t) {
      if (ch == '\t') {
        printf("%c", '^');
        ch = 'I';
      }
    }
    if (flags.v) {
      if (!isprint(ch) && ch != 10 &&
          ch != 9) {  // isprint() -проверяет, является ли символ печатаемым
                     // (включая пробел)
        printf("^");
        if (ch == 127)
          ch -= 64;
        else
          ch += 64;
      }
    }
    printf("%c", ch);
  }
}
