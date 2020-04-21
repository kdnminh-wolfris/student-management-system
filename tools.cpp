#include "function.h"

void numtag(int num) {
	cout << "[";
	if (num < 10)
		cout << " ";
	cout << num << " ] ";
}

bool load_config(Config& config) {
	ifstream fi;
	fi.open("data/config.gulu");
	if (!fi.is_open()) {
		cout << "Error: Missing config.gulu file\n" << endl;
		return false;
	}

	fi >> config.login_status; fi.ignore(100, '\n');
	getline(fi, config.curID);
	fi >> config.curPosition;
	fi >> config.keep_login;
	fi >> config.max_enterpw_turn;

	fi.close();
	return true;
}

void update_config(Config& config) {
	ofstream fo;
	fo.open("data/config.gulu");

	fo << config.login_status << '\n';
	fo << config.curID << '\n';
	fo << config.curPosition << '\n';
	fo << config.keep_login << '\n';
	fo << config.max_enterpw_turn;

	fo.close();
}

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