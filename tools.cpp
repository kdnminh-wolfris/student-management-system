#include "function.h"

int choose_option(int high) {
	char ch;
	do ch = _getch();
	while ('0' <= ch && ch <= '0' + high);
	return ch;
}