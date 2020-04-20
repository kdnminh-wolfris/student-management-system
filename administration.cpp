#include "function.h"

bool login(User& _user) {
	ifstream fi;
	fi.open("data/config.txt");
	if (!fi.is_open()) {
		cout << "Error: Missing config.txt file\n" << endl;
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

	bool err = get_info(_user); // true: no error / false: error

	if (err && !logged_in) {
		ofstream fo;
		fo.open("data/config.txt");
		fo << "1\n" << _user.ID << "\n" << _user.position;
		fo.close();
	}

	return err;
}

int verified(User& _user, string& pw) {
	ifstream fi;
	fi.open("data/account.txt");
	if (!fi.is_open()) {
		cout << "Error: Missing account.txt file\n" << endl;
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
			cout << "Error: Missing academic_staff.txt file\n" << endl;
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
			cout << "Error: Missing lecturer.txt file\n" << endl;
			return false;
		}




		break;
	}
	case 2: {
		fi.open("data/student.txt");
		if (!fi.is_open()) {
			cout << "Error: Missing student.txt file\n" << endl;
			return false;
		}




		break;
	}
	}

	cout << "Error: User infomation not found\n" << endl;

	fi.close();
	return false;
}

void menu(User& _user) {
	/*
		View profile
		Functions
		Change password
		Logout
	*/

	cout << "[ 0 ] Profile\n";
	int numberFunction = menuFunction(_user.position);
	cout << "[ " << numberFunction + 1 << " ] Change password\n";
	cout << "[ " << numberFunction + 2 << " ] Logout\n";

	int option = int_option(numberFunction + 3);
	if (option == numberFunction + 2) {
		if (bool_option("logout")) {
			ofstream fo;
			fo.open("data/config.txt");
			fo << "0\n\n";
			fo.close();
			return;
		}
		else return menu(_user);
	}
}

int menuFunction(int user_position) {
	if (user_position == 0) {
		cout << "[ 1 ] Class\n";
		cout << "[ 2 ] Course\n";
		cout << "[ 3 ] Scoreboard\n";
		cout << "[ 4 ] Attendance list\n";
		return 4;
	}
	else if (user_position == 1) return 7;
	else return 4;
}