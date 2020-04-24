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

bool load_account(int& numberAccount, nodeAccount*& listAccount) {
	ifstream fi;
	fi.open("data/account.gulu");
	if (!fi.is_open()) {
		cout << "Error: Missing account.gulu file\n" << endl;
		return false;
	}

	fi >> numberAccount;

	nodeAccount* cur;
	listAccount = cur = nullptr;

	fi.ignore(100, '\n');

	for (int i = 0; i < numberAccount; ++i) {
		if (i == 0)
			listAccount = cur = new nodeAccount,
			cur->next = nullptr;
		else
			cur->next = new nodeAccount,
			cur = cur->next,
			cur->next = nullptr;

		fi.ignore(100, '\n');
		getline(fi, cur->data.userID);
		getline(fi, cur->data.password);
		fi >> cur->data.position;
		fi.ignore(100, '\n');
	}

	fi.close();
	return true;
}

void update_account(int numberAccount, nodeAccount* listAccount) {
	ofstream fo;
	fo.open("data/account.gulu");

	fo << numberAccount << "\n";
	while (listAccount != nullptr) {
		fo << "\n" << listAccount->data.userID;
		fo << "\n" << listAccount->data.password;
		fo << "\n" << listAccount->data.position;
		fo << '\n';
		nodeAccount* tmp = listAccount;
		listAccount = listAccount->next;
		delete tmp;
	}

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

bool get_info(User& user) {
	ifstream fi;
	switch (user.position) {
		case 0: {
			fi.open("data/academic_staff.gulu");
			if (!fi.is_open()) {
				cout << "Error: Missing academic_staff.gulu file\n" << endl;
				return false;
			}

			int numberStaff;
			fi >> numberStaff;
			fi.ignore(100, '\n');

			string tmpID = user.ID;

			while (numberStaff--) {
				fi.ignore(100, '\n');
				getline(fi, user.ID);
				getline(fi, user.fullname);

				fi >> user.DoB.year;
				fi >> user.DoB.month;
				fi >> user.DoB.day;

				fi >> user.sex;
				fi.ignore(100, '\n');

				if (tmpID == user.ID) {
					fi.close(); return true;
				}
			}

			fi.close();
			cout << "Error: Missing this user in academic_staff.gulu\n" << endl;
			return false;
		}
		case 1: {
			fi.open("data/lecturer.gulu");
			if (!fi.is_open()) {
				cout << "Error: Missing lecturer.gulu file\n" << endl;
				return false;
			}



			break;
		}
		case 2: {
			fi.open("data/student.gulu");
			if (!fi.is_open()) {
				cout << "Error: Missing student.gulu file\n" << endl;
				return false;
			}

			int numberStudent;
			fi >> numberStudent;
			fi.ignore(100, '\n');

			string tmpID, tmpClassCode;
			bool found = false;

			while (numberStudent--) {
				fi.ignore(100, '\n');
				getline(fi, tmpID);
				getline(fi, tmpClassCode);
				if (tmpID == user.ID) {
					found = true;
				}
			}

			fi.close();
			if (!found) {
				cout << "Error: Missing this user in student.gulu\n" << endl;
				return false;
			}

			fi.open("data/class/" + tmpClassCode + "/student.gulu");
			if (!fi.is_open()) {
				cout << "Error: Missing " << tmpClassCode << "/student.gulu file\n" << endl;
				return false;
			}

			fi >> numberStudent;
			fi.ignore(100, '\n');

			tmpID = user.ID;

			while (numberStudent--) {
				fi.ignore(100, '\n');
				getline(fi, user.ID);
				getline(fi, user.fullname);

				fi >> user.DoB.year;
				fi >> user.DoB.month;
				fi >> user.DoB.day;

				fi >> user.sex;
				fi.ignore(100, '\n');
				fi.ignore(100, '\n');

				if (tmpID == user.ID) {
					fi.close(); return true;
				}
			}

			fi.close();
			cout << "Error: Missing this user in " << tmpClassCode << "/student.gulu\n" << endl;
			return false;
		}
	}

	cout << "Error: User infomation not found\n" << endl;

	fi.close();
	return false;
}