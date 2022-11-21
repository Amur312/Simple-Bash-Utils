#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include <unistd.h>
struct s_flag {
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
};

void ParserFlag(int argc, char *argv[], struct s_flag *flags);
void OpenFile(int argc, char *argv[], struct s_flag flags);
void PrintCat(FILE *file, struct s_flag flags);

#endif  // SRC_CAT_S21_CAT_H_
