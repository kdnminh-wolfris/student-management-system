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

	if (option == 0) view_profile(user);
	else if (option == numberFunction + 1) {



	}
	else if (option == numberFunction + 2) {
		if (changePassword(user, config))
			cout << "Password changed sucessfully!\n" << endl;
	}
	else if (option == numberFunction + 3) {
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
	else optionFunction(option - 1, user.position);
}

int menuFunction(int start, int user_position) {
	if (user_position == 0) {
		numtag(start + 0); cout << "Class\n";
		numtag(start + 1); cout << "Course\n";
		numtag(start + 2); cout << "Scoreboard\n";
		numtag(start + 3); cout << "Attendance list\n";
		return 4;
	}
	else if (user_position == 1) {
		numtag(start + 0); cout << "View course list\n";
		numtag(start + 1); cout << "View course's student list\n";
		numtag(start + 2); cout << "View course's attendance list\n";
		numtag(start + 3); cout << "Edit an attendance\n";
		numtag(start + 4); cout << "Import scoreboard\n";
		numtag(start + 5); cout << "Edit student grade\n";
		numtag(start + 6); cout << "View scoreboard\n";
		return 7;
	}
	else {
		numtag(start + 0); cout << "Check-in\n";
		numtag(start + 1); cout << "View check-in result\n";
		numtag(start + 2); cout << "View schedules\n";
		numtag(start + 3); cout << "View course scores\n";
		return 4;
	}
}

void optionFunction(int option, int user_position) {
	if (user_position == 0) {
		switch (option) {
			case 0: {
				cout << "Class Manangement\n" << endl;

				numtag(0); cout << "Import students of a class\n";
				numtag(1); cout << "Add a new student to a class\n";
				numtag(2); cout << "Edit student infomation\n";
				numtag(3); cout << "Remove a student\n";
				numtag(4); cout << "Change a student from class A to class B\n";
				numtag(5); cout << "View list of classes\n";
				numtag(6); cout << "View list of students in a class\n";

				option = int_option(7);

				switch (option) {
					case 0: {
						//import_student_from_csv();
						break;
					}
					case 1: {

						break;
					}
					case 2: {
						//edit_a_student();
						break;
					}
					case 3: {
						//remove_a_student();
						break;
					}
					case 4: {

						break;
					}
					case 5: {
						view_class_list();
						break;
					}
					case 6: {
						
						break;
					}
				}
			}
		}
	}
	else if (user_position == 1) {

	}
	else if (user_position == 2) {

	}
}