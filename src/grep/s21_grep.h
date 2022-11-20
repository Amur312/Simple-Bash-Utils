#ifndef SRC_S21_GREP_H
#define SRC_S21_GREP_H



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <getopt.h>
#include <regex.h>


#define BuffSize 4096
struct s_flags
{
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
    int empty_lines;
    
};



void RegexComp(char *argv[], char *patternE, FILE *file, struct s_flags flag,int files_count);
void OpenFile(int argc, char *argv[], struct s_flags flag, char *patternE);
void ParsFlag(int argc, char *argv[], struct s_flags *flag, char *patternE);

void f_flag(char *optarg, int *e_count, char *patternE, struct s_flags *flag);
void e_flag(char* optarg, int* e_count, char* patternE, struct s_flags* flag);


#endif  // SRC_S21_GREP_H