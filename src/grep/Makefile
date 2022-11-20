GCC=gcc -Wall -Wextra -Werror -std=c11

all: s21_grep

s21_grep:
	$(GCC) $@.c -o $@

rebuild: clean all

clean:
	rm -rf s21_grep