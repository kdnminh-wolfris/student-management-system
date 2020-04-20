#include "function.h"

bool login(User& _user) {
	ifstream fi;
	fi.open("data/config.txt");
	if (!fi.is_open()) {
		cout << "Error: Missing config.txt file";
		return false;
	}

	int logged_in = 0;
	fi >> logged_in;
	fi.ignore();

	if (logged_in) {
		getline(fi, _user.ID);
		fi >> _user.position;
	}
	else {
		string pw;
		do {
			cout << "User ID: ";
			cin >> _user.ID;
			cout << "Password: ";
			cin >> pw;
			int err = verified(_user, pw);
			if (err == 1)
				cout << "Incorrect ID or password.\n" << endl;
			else if (err == 2) return false;
			else break;
		} while (true);

		cout << "Sucessfully login!\n" << endl;
	}

	fi.close();
	return get_info(_user);
}

int verified(User& _user, string& pw) {
	ifstream fi;
	fi.open("data/account.txt");
	if (!fi.is_open()) {
		cout << "Error: Missing account.txt file";
		return 2;
	}

	int numberAccount;
	fi >> numberAccount;
	fi.ignore(100, '\n');

	while (numberAccount--) {
		string tmp_ID, tmp_pw;
		fi.ignore(100, '\n');
		getline(fi, tmp_ID);
		getline(fi, tmp_pw);

		if (tmp_ID == _user.ID && tmp_pw == pw) {
			fi >> _user.position;

			fi.close();
			return 0;
		}

		fi.ignore(100, '\n');
	}

	fi.close();
	return 1;
}

bool get_info(User& _user) {
	ifstream fi;
	switch (_user.position) {
		case 0: {
			fi.open("data/academic_staff.txt");
			if (!fi.is_open()) {
				cout << "Error: Missing academic_staff.txt file";
				return false;
			}

			int numberStaff;
			fi >> numberStaff;
			fi.ignore(100, '\n');

			while (numberStaff--) {
				string tmpID;
				fi.ignore(100, '\n');
				getline(fi, tmpID);

				if (tmpID == _user.ID) {
					getline(fi, _user.fullname);

					fi >> _user.DoB.year;
					fi >> _user.DoB.month;
					fi >> _user.DoB.day;

					fi >> _user.sex;
					
					fi.close();
					return true;
				}

				fi.ignore(100, '\n');
				fi.ignore(100, '\n');
				fi.ignore(100, '\n');
			}
		}
		case 1: {
			fi.open("data/lecturer.txt");
			if (!fi.is_open()) {
				cout << "Error: Missing lecturer.txt file";
				return false;
			}




			break;
		}
		case 2: {
			fi.open("data/student.txt");
			if (!fi.is_open()) {
				cout << "Error: Missing student.txt file";
				return false;
			}




			break;
		}
	}

	cout << "Error: User infomation not found";

	fi.close();
	return false;
}

