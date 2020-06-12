#include "option.h"

int int_option(int numberChoice) {
	cout << "\nChoose an option to continue...: ";
	cout.flush();

	char ch; int ret = 0;

	do {
		ch = _getch();
		if ('0' <= ch && ch <= '9') {
			if (numberChoice > 1 && ch == '1' && ret == 0) {
				ret = 1;
				cout << 1;
				if (numberChoice <= 10)
					break;
			}
			else if (ret == 1) {
				if (10 + ch - '0' < numberChoice) {
					ret = 10 + ch - '0';
					cout << ch;
					break;
				}
			}
			else if (ch - '0' < numberChoice) {
				ret = ch - '0';
				cout << ch;
				break;
			}
		}
		else if (ch == 13 && ret == 1)
			break;
	} while (true);

	cout << '\n' << endl;

	return ret;
}

bool bool_option(string operation) {
	if (operation != "")
		cout << "Are you sure you want to " << operation << "?\n";
	cout << "[Y]ES          [N]O\n\n";
	cout << "Press Y/N to continue...\n" << endl;
	char ch;
	do ch = _getch();
	while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
	return ch == 'Y' || ch == 'y';
}