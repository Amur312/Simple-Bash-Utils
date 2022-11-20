#ifndef SRC_S21_cat_H
#define SRC_S21_cat_H

#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include <unistd.h>
struct s_flag
{
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
};

void parsStr(int file_dict);
void ParserFlag(int argc, char *argv[], struct s_flag *flags);
void OpenFile(int argc, char *argv[], struct s_flag flags);
void PrintCat(FILE *file, struct s_flag flags);

#endif // SRC_S21_cat_H
