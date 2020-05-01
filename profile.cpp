#include "function.h"

void view_profile(User& user) {
	cout << "=========================================================\n";

	if (user.position < 2) {
		if (user.sex) cout << "Mr. ";
		else cout << "Ms. ";
	}
	cout << user.fullname << " (ID: " << user.ID << ")\n";

	cout << endl;

	cout << "D.o.B: ";
	month_in_text(user.DoB.month);
	cout << " " << user.DoB.day << ", " << user.DoB.year;
	cout << "\n";

	cout << "Sex: ";
	if (user.sex) cout << "Male\n"; else cout << "Female\n";

	cout << endl;

	cout << "Job title: ";
	if (user.position == 0) profileStaff(user);
	else if (user.position == 1) profileLecturer(user);
	else if (user.position == 2) profileStudent(user);

	cout << endl;

	cout << "=========================================================\n";
	cout << "Press any key to continue...\n";
	cout << endl; _getch(); // Pause the console for reading purpose
}

void profileStaff(User& user) {
	cout << "Academic Staff\n";
}

void profileLecturer(User& user) {
	cout << "Lecturer\n";

	Lecturer lecturer;
	lecturer.general = user;
	loadLecturer(lecturer);

	cout << "Degree: " << lecturer.degree << '\n';
}

void profileStudent(User& user) {
	Student student;
	student.general = user;
	loadStudent(student);

	cout << "Student (";
	switch (student.status) {
		case 0: {
			cout << "graduated";
			break;
		}
		case 1: {
			cout << "studying";
			break;
		}
		case 2: {
			cout << "reserved";
			break;
		}
	}
	cout << ")\n";

	cout << "Class: " << student.class_ << '\n';

	int graduation_year = (student.class_[0] - 48) * 10 + (student.class_[1] - 48) + 4;
	cout << "Graduation year: " << graduation_year << "\n";
}