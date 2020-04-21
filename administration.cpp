#include "function.h"

bool login(User& user, Config& config) {
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
			cout << endl;

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

void menu(User& user, Config& config) {
	/*
		View profile
		Functions
		Change password
		Logout
	*/

	cout << "[ 0 ] Profile\n";
	int numberFunction = menuFunction(1, user.position);
	numtag(numberFunction + 1); cout << "Settings\n";
	numtag(numberFunction + 2); cout << "Change password\n";
	numtag(numberFunction + 3); cout << "Logout\n";
	
	int option = int_option(numberFunction + 4);

	if (option == numberFunction + 2) {
		if (changePassword(user, config))
			cout << "Password changed sucessfully!\n" << endl;
	}

	if (option == numberFunction + 3) {
		if (bool_option("logout")) {
			Config config;
			load_config(config);
			config.login_status = 0;
			update_config(config);

			cout << "Logged out.\n" << endl;
			return;
		}
		else return menu(user, config);
	}
}

int menuFunction(int start, int user_position) {
	if (user_position == 0) {
		numtag(start + 0); cout << "Class\n";
		numtag(start + 1); cout << "Course\n";
		numtag(start + 2); cout << "Scoreboard\n";
		numtag(start + 3); cout << "Attendance list\n";
		return 4;
	}
	else if (user_position == 1) return 7;
	else return 4;
}

bool changePassword(User& user, Config& config) {
	string pw;
	int turn = 0;
	do {
		++turn;
		cout << "Please enter your current password to continue:\n";
		cin >> pw;
		cout << endl;

		int err = verified(user, pw);
		if (err == 1)
			cout << "Incorrect password.\n" << endl;
		else if (err == 2) return false;
		else break;
		
		if (turn == 3) {
			cout << "You have entered the password incorrectly " << config.max_enterpw_turn << " time";
			if (config.max_enterpw_turn > 1) cout << "s";
			cout << "! Failed to change password.\n" << endl;
			return false;
		}
	} while (true);

	do {
		cout << "New password: ";
		cin >> pw;
		cout << endl;

		string confirm_pw;
		cout << "Confirm new password: ";
		cin >> confirm_pw;
		cout << endl;

		if (pw != confirm_pw)
			cout << "New password and confirm password don't match!\n" << endl;
		else break;
	} while (true);

	ifstream fi;
	fi.open("data/account.gulu");
	if (!fi.is_open()) {
		cout << "Error: Missing account.gulu file\n" << endl;
		return false;
	}

	int numberAccount;
	fi >> numberAccount;

	AccountNode* list, * cur;
	list = cur = nullptr;

	fi.ignore(100, '\n');

	for (int i = 0; i < numberAccount; ++i) {
		if (i == 0)
			list = cur = new AccountNode,
			cur->next = nullptr;
		else
			cur->next = new AccountNode,
			cur = cur->next,
			cur->next = nullptr;

		fi.ignore(100, '\n');
		getline(fi, cur->data.userID);
		getline(fi, cur->data.password);
		fi >> cur->data.position;
		fi.ignore(100, '\n');

		if (cur->data.userID == user.ID)
			cur->data.password = pw;
	}

	fi.close();

	ofstream fo;
	fo.open("data/account.gulu");
	
	fo << numberAccount << "\n";
	while (list != nullptr) {
		fo << "\n" << list->data.userID;
		fo << "\n" << list->data.password;
		fo << "\n" << list->data.position;
		fo << '\n';
		cur = list;
		list = list->next;
		delete cur;
	}

	fo.close();
	return true;
}