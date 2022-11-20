GCC=gcc -Wall -Wextra -Werror -std=c11

all: s21_cat

s21_cat:
	$(GCC) $@.c -o $@

rebuild: clean all

clean:
	rm -rf s21_cat