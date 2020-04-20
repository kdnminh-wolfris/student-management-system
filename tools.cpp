#include "function.h"

int int_option(int numberChoice) {
	cout << "\nChoose an option to continue...\n" << endl;
	char ch;
	do ch = _getch();
	while (!('0' <= ch && ch <= 48 + numberChoice - 1));
	return ch - '0';
}

bool bool_option(string operation) {
	cout << "Are you sure you want to " << operation << "?\n";
	cout << "[Y]ES          [N]O\n\n";
	cout << "Press Y/N to continue...\n" << endl;
	char ch;
	do ch = _getch();
	while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
	return ch == 'Y' || ch == 'y';
}