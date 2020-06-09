#include "menu.h"

void menu(User& user, Config& config) {
	/*
		View profile
		Functions
		Change password
		Logout
	*/

	cout << "[ 0 ] Profile\n";

	int numberFunction = menuFunction(1, user);

	numtag(numberFunction + 1); cout << "Change password\n";
	numtag(numberFunction + 2); cout << "Logout\n";

	int option = int_option(numberFunction + 4);

	if (option == 0) user.view_profile();
	else if (option == numberFunction + 1) {
		if (changePassword(user, config))
			cout << "Password changed sucessfully!\n" << endl;
	}
	else if (option == numberFunction + 2) {
		if (bool_option("logout")) {
			Config config;
			config.load();
			config.login_status = 0;
			config.update();

			cout << "Logged out.\n" << endl;
			return;
		}
		else return menu(user, config);
	}
	else optionFunction(option - 1, user);
}

int menuFunction(int start, User& user) {
	if (user.position == 0) {
		numtag(start + 0); cout << "Class\n";
		numtag(start + 1); cout << "Course\n";
		numtag(start + 2); cout << "Scoreboard\n";
		numtag(start + 3); cout << "Attendance list\n";
		return 4;
	}
	else if (user.position == 1) {
		numtag(start + 0); cout << "View course list\n";
		numtag(start + 1); cout << "View course's student list\n";
		numtag(start + 2); cout << "View course's attendance list\n";
		numtag(start + 3); cout << "Edit attendance list\n";
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

void optionFunction(int option, User& user) {
	if (user.position == 0) {
		switch (option) {
			case 0: {
				cout << "Class Manangement\n" << endl;

				numtag(0); cout << "Import students of a class\n";
				numtag(1); cout << "Add a new student to a class\n";
				numtag(2); cout << "Edit student infomation\n";
				numtag(3); cout << "Remove a student\n";
				numtag(4); cout << "Move a student to another class\n";
				numtag(5); cout << "View list of classes\n";
				numtag(6); cout << "View list of students of a class\n";
				numtag(7); cout << "Back to main menu\n";

				option = int_option(8);

				switch (option) {
					case 0: {
						import_student();
						break;
					}
					case 1: {
						add_new_student();
						break;
					}
					case 2: {
						edit_student();
						break;
					}
					case 3: {
						remove_student();
						break;
					}
					case 4: {
						move_student();
						break;
					}
					case 5: {
						view_class_list();
						break;
					}
					case 6: {
						view_student_list_of_class();
						break;
					}
				}

				break;
			}
			case 1: {
				cout << "Course Management\n" << endl;

				numtag(0); cout << "Import a course\n";
				numtag(1); cout << "Add a new course\n";
				numtag(2); cout << "Edit course information\n";
				numtag(3); cout << "Remove a course\n";
				numtag(4); cout << "Add a student to a course\n";
				numtag(5); cout << "Remove a student from a course\n";
				numtag(6); cout << "View list of courses\n";
				numtag(7); cout << "View list of students of a course\n";
				numtag(8); cout << "View attendance list of a course\n";
				numtag(9); cout << "View list of lecturers\n";
				numtag(10); cout << "Back to main menu\n";

				int option = int_option(11);

				switch (option) {
					case 0: {
						import_course();
						break;
					}
					case 1: {
						add_new_course();
						break;
					}
					case 2: {
						edit_course();
						break;
					}
					case 3: {
						remove_course();
						break;
					}
					case 4: {
						add_student_to_course();
						break;
					}
					case 5: {
						remove_student_from_course();
						break;
					}
					case 6: {
						view_course_list();
						break;
					}
					case 7: {
						view_student_list_of_course();
						break;
					}
					case 8: {
						view_attendance_list_of_course();
						break;
					}
					case 9: {
						view_lecturer_list();
						break;
					}
				}

				break;
			}
			case 2: {
				cout << "Scoreboard Management\n" << endl;

				numtag(0); cout << "View scoreboard of a course\n";
				numtag(1); cout << "Export scoreboard of a course to csv file\n";
				numtag(2); cout << "Back to main menu\n";

				int option = int_option(3);

				switch (option) {
					case 0: {
						view_scoreboard_course();
						break;
					}
					case 1: {
						export_scoreboard();
						break;
					}
				}
				
				break;
			}
			case 3: {
				cout << "Attendance List Management\n" << endl;

				numtag(0); cout << "View attendance list of a course\n";
				numtag(1); cout << "Export an attendance list to csv file\n";
				numtag(2); cout << "Back to main menu\n";

				int option = int_option(3);

				switch (option) {
					case 0: {
						view_attendance_list_of_course();
						break;
					}
					case 1: {
						export_attendance_list();
						break;
					}
				}

				break;
			}
		}
	}
	else if (user.position == 1) {
		Lecturer lecturer;
		lecturer.general = user;
		lecturer.load();

		switch (option) {
			case 0: {
				lecturer.view_course_list();
				break;
			}
			case 1: {
				view_student_list_of_course();
				break;
			}
			case 2: {
				view_attendance_list_of_course();
				break;
			}
			case 3: {
				lecturer.edit_attendance();
				break;
			}
			case 4: {
				lecturer.import_scoreboard();
				break;
			}
			case 5: {
				lecturer.edit_student_grade();
				break;
			}
			case 6: {
				lecturer.view_scoreboard();
				break;
			}
		}
	}
	else if (user.position == 2) {
		Student student;
		student.general = user;
		student.load();

		switch (option) {
			case 0: {
				student.check_in();
				break;
			}
			case 1: {
				student.view_check_in();
				break;
			}
			case 2: {
				student.view_schedule();
				break;
			}
			case 3: {
				student.view_course_score();
			}
		}
	}
}