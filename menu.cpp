#include "function.h"

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