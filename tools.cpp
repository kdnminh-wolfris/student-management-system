#include "function.h"

bool load_config(Config& config) {
	ifstream fi;
	fi.open("data/config.txt");
	if (!fi.is_open()) {
		cout << "Error: Missing config.txt file\n" << endl;
		return false;
	}

	fi >> config.login_status; fi.ignore(100, '\n');
	getline(fi, config.curID);
	fi >> config.curPosition;
	fi >> config.keep_login;

	fi.close();
	return true;
}

bool update_config(Config& config) {
	ofstream fo;
	fo.open("data/config.txt");
	if (!fo.is_open()) {
		cout << "Error: Missing config.txt file\n" << endl;
		return false;
	}

	fo << config.login_status << '\n';
	fo << config.curID << '\n';
	fo << config.curPosition << '\n';
	fo << config.keep_login;

	fo.close();
	return true;
}

int int_option(int numberChoice) {
	cout << "\nChoose an option to continue...\n" << endl;
	char ch;
	do ch = _getch();
	while (!('0' <= ch && ch <= 48 + numberChoice - 1));
	return ch - '0';
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