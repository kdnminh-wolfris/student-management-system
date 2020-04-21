#include "function.h"

bool login(User& user) {
	Config config;
	load_config(config);

	if (config.login_status) {
		user.ID = config.curID;
		user.position = config.curPosition;
	}
	else {
		string pw;
		do {
			cout << "User ID: ";
			cin >> user.ID;
			cout << "Password: ";
			cin >> pw;
			int err = verified(user, pw);
			if (err == 1)
				cout << "Incorrect ID or password.\n" << endl;
			else if (err == 2) return false;
			else break;
		} while (true);

		cout << "Sucessfully login!\n" << endl;
	}

	bool err = get_info(user); // true: no error / false: error

	if (err && !config.login_status && config.keep_login) {
		config.login_status = 1;
		config.curID = user.ID;
		config.curPosition = user.position;
		update_config(config);
	}
	
	return err;
}

int verified(User& user, string& pw) {
	ifstream fi;
	fi.open("data/account.gulu");
	if (!fi.is_open()) {
		cout << "Error: Missing account.gulu file\n" << endl;
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

		if (tmp_ID == user.ID && tmp_pw == pw) {
			fi >> user.position;

			fi.close();
			return 0;
		}

		fi.ignore(100, '\n');
	}

	fi.close();
	return 1;
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

		while (numberStaff--) {
			string tmpID;
			fi.ignore(100, '\n');
			getline(fi, tmpID);

			if (tmpID == user.ID) {
				getline(fi, user.fullname);

				fi >> user.DoB.year;
				fi >> user.DoB.month;
				fi >> user.DoB.day;

				fi >> user.sex;

				fi.close();
				return true;
			}

			fi.ignore(100, '\n');
			fi.ignore(100, '\n');
			fi.ignore(100, '\n');
		}
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




		break;
	}
	}

	cout << "Error: User infomation not found\n" << endl;

	fi.close();
	return false;
}

void menu(User& user) {
	/*
		View profile
		Functions
		Change password
		Logout
	*/

	cout << "[ 0 ] Profile\n";
	int numberFunction = menuFunction(user.position);
	cout << "[ " << numberFunction + 1 << " ] Change password\n";
	cout << "[ " << numberFunction + 2 << " ] Logout\n";

	int option = int_option(numberFunction + 3);
	if (option == numberFunction + 2) {
		if (bool_option("logout")) {
			ofstream fo;
			fo.open("data/config.gulu");
			fo << "0\n\n";
			fo.close();
			return;
		}
		else return menu(user);
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