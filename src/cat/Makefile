GCC=gcc -Wall -Wextra -Werror -std=c11

all: s21_cat

s21_cat:
	$(GCC) $@.c -o $@
check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config s21_cat.c
		cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
		python3 ../../materials/linters/cpplint.py --extensions=c s21_cat.c s21_cat.h
		rm CPPLINT.cfg
		make s21_cat

rebuild: clean all

clean:
	rm -rf s21_cat *.o log.txt