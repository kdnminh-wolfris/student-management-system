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

	int numberAccount;
	nodeAccount* listAccount;

	if (!load_account(numberAccount, listAccount))
		return false;

	for (nodeAccount* p = listAccount; p != nullptr; p = p->next)
		if (p->data.userID == user.ID) {
			p->data.password = pw; break;
		}

	update_account(numberAccount, listAccount);
	return true;
}