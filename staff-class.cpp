#include "staff-class.h"

void import_student() {
	cout << "Import students of a class\n" << endl;

	ifstream fi;

	string classID;

	ClassList classList;
	if (!classList.load()) {
		system("pause");
		fi.close(); return;
	}

	const int max_turn = 3;
	int turn = 0;
	do {
		cout << "Enter the imported class: ";
		cin >> classID;

		bool check = true;
		for (auto iter = classList.head; iter != nullptr; iter = iter->next)
			if (iter->ID == classID) { check = false; break; }
		if (!check) {
			cout << classID << " have already been imported!\n" << endl;
			if (++turn == max_turn) break;
			continue;
		}

		fi.open("csv files/" + classID + "-student.csv");
		if (!fi.is_open()) {
			cout << classID << "-student.csv not found\n" << endl;
			if (++turn == max_turn) break;
		}
	} while (!fi.is_open());
	if (!fi.is_open()) {
		system("pause");
		return;
	}
	
	classList.append(classID);
	classList.update();
	classList._delete();

	StudentList studentList;

	fi.ignore(100, '\n');

	while (!fi.eof()) {
		fi.ignore(100, ',');
		Student tmp;

		do {
			char ch; fi.get(ch);
			if (ch != ',') tmp.general.ID += ch;
			else break;
		} while (true); // ID

		do {
			char ch; fi.get(ch);
			if (ch != ',') tmp.general.fullname += ch;
			else break;
		} while (true); // Last name

		tmp.general.fullname += ' ';

		do {
			char ch; fi.get(ch);
			if (ch != ',') tmp.general.fullname += ch;
			else break;
		} while (true); // First name

		do {
			char ch; fi.get(ch);
			if (ch == 'M') tmp.general.sex = 1;
			else if (ch == 'F') tmp.general.sex = 0;
			if (ch == ',') break;
		} while (true); // Sex

		do {
			char ch; fi.get(ch);
			if (ch != '/')
				tmp.general.DoB.day = tmp.general.DoB.day * 10 + (ch - 48);
			else break;
		} while (true); // DoB day

		do {
			char ch; fi.get(ch);
			if (ch != '/')
				tmp.general.DoB.month = tmp.general.DoB.month * 10 + (ch - 48);
			else break;
		} while (true); // DoB month

		do {
			char ch; fi.get(ch);
			if (ch != '\n')
				tmp.general.DoB.year = tmp.general.DoB.year * 10 + (ch - 48);
			else break;
		} while (true); // DoB year

		tmp.general.position = 2;
		tmp.classID = classID;
		tmp.status = 1;

		studentList.append(tmp);
	}

	fi.close();

	studentList._delete(studentList.tail);
	studentList.update(classID);

	StudentList studentAllList;
	if (!studentAllList.loadAll()) {
		system("pause");
		return;
	}
	for (auto iter = studentList.head; iter != nullptr; iter = iter->next)
		studentAllList.append(iter->student);
	studentAllList.updateAll();
	studentAllList._delete();

	AccountList accountList;
	if (!accountList.load()) {
		system("pause");
		return;
	}

	for (auto p = studentList.head; p != nullptr; p = p->next) {
		Account tmp;

		tmp.userID = p->student.general.ID;
		tmp.password = p->student.general.DoB.password();
		tmp.position = 2;

		accountList.append(tmp);
	}
	studentList._delete();

	accountList.update();
	accountList._delete();

	cout << "Import " << classID << " data successfully!\n" << endl;
	cin.ignore(100, '\n');
	system("pause");
}

void add_new_student() {
	cout << "Add a new student to a class\n" << endl;

	ifstream fi;

	Student student;

	const int max_turn = 3;
	int turn = 0;
	do {
		cout << "Enter new student's class: ";
		getline(cin, student.classID);

		fi.open("data/class/" + student.classID + "-student.gulu");
		if (!fi.is_open()) {
			cout << student.classID << " not found\n" << endl;
			if (++turn == max_turn) break;
		}
	} while (!fi.is_open());
	if (!fi.is_open()) {
		system("pause");
		return;
	}

	fi.close();

	cout << "Full name: ";
	getline(cin, student.general.fullname);
	
	cout << "Student ID: ";
	getline(cin, student.general.ID);

	cout << "Date of Birth:\n";
	student.general.DoB.input();

	cout << "Sex (0 Female / 1 Male): ";
	cin >> student.general.sex;
	
	student.general.position = 2;
	student.status = 1;

	StudentList studentList;
	if (!studentList.load(student.classID)) {
		system("pause");
		return;
	}
	studentList.append(student);
	studentList.update(student.classID);
	studentList._delete();

	if (!studentList.loadAll()) {
		system("pause");
		return;
	}
	studentList.append(student);
	studentList.updateAll();
	studentList._delete();

	Account account;
	account.userID = student.general.ID;
	account.password = student.general.DoB.password();
	account.position = 2;

	AccountList accountList;
	if (!accountList.load()) {
		system("pause");
		return;
	}
	accountList.append(account);
	accountList.update();
	accountList._delete();

	cout << '\n' << student.general.fullname << " has been added into " << student.classID << " successfully!\n" << endl;
	system("pause");
}

void edit_student() {
	cout << "Edit student infomation\n" << endl;

	StudentList studentList;
	studentList.loadAll();

	Student student;

	const int max_turn = 3;
	int turn = 0;
	do {
		cout << "Enter the student's ID: ";
		string SID; getline(cin, SID);

		bool found = false;
		for (auto iter = studentList.head; iter != nullptr; iter = iter->next)
			if (iter->student.general.ID == SID) {
				student = iter->student;
				found = true;
			}

		if (!found)
			cout << SID << " not exists\n" << endl;
		else break;

		++turn;
	} while (turn < max_turn);
	if (turn == max_turn) {
		system("pause");
		return;
	}

	studentList._delete();

	if (!studentList.load(student.classID)) {
		system("pause");
		return;
	}
	for (auto iter = studentList.head; iter != nullptr; iter = iter->next)
		if (iter->student.general.ID == student.general.ID) {
			student = iter->student;
			break;
		}
	
	string tmp;

	cout << "Student ID (enter a blank to maintain the current)\n";
	cout << student.general.ID << " -> ";
	getline(cin, tmp);
	if (tmp != "") student.general.ID = tmp;

	cout << "Full name (enter a blank to maintain the current)\n";
	cout << student.general.fullname << " -> ";
	getline(cin, tmp);
	if (tmp != "") student.general.fullname = tmp;

	cout << "Date of Birth:\n";
	student.general.DoB.input();

	cout << "Sex (0 Female / 1 Male): ";
	cin >> student.general.sex;

	student.general.position = 2;
	student.status = 1;

	for (auto iter = studentList.head; iter != nullptr; iter = iter->next)
		if (iter->student.general.ID == student.general.ID) {
			iter->student = student;
			break;
		}

	studentList.update(student.classID);
	studentList._delete();

	AccountList accountList;
	if (!accountList.load()) {
		system("pause");
		return;
	}

	for (auto iter = accountList.head; iter != nullptr; iter = iter->next)
		if (iter->account.userID == student.general.ID) {
			iter->account.password = student.general.DoB.password();
			break;
		}

	accountList.update();
	accountList._delete();

	cout << "Edit " << student.general.fullname << "'s information successfully!\n" << endl;
	system("pause");
}

void remove_student() {
	cout << "Remove a student\n" << endl;

	StudentList studentList;
	if (!studentList.loadAll()) {
		system("pause");
		return;
	}

	Student student;

	const int max_turn = 3;
	int turn = 0;
	do {
		cout << "Enter the student's ID: ";
		string SID; getline(cin, SID);

		bool found = false;
		for (auto iter = studentList.head; iter != nullptr; iter = iter->next)
			if (iter->student.general.ID == SID) {
				student = iter->student;
				found = true;
			}

		if (!found)
			cout << SID << " not exists\n" << endl;
		else break;

		++turn;
	} while (turn < max_turn);
	if (turn == max_turn) {
		system("pause");
		return;
	}

	studentList._delete();

	if (!studentList.load(student.classID)) {
		system("pause");
		return;
	}
	for (auto iter = studentList.head; iter != nullptr; iter = iter->next)
		if (iter->student.general.ID == student.general.ID) {
			student = iter->student;
			break;
		}

	cout << "Please give the reason to remove this student:\n";
	cout << "[ 0 ] Graduated                 [ 1 ] Reserved\n";
	int option = int_option(2);

	if (option == 0) student.status = 0;
	else student.status = 2;

	if (!bool_option("remove this student")) {
		studentList._delete();
		return;
	}

	for (auto iter = studentList.head; iter != nullptr; iter = iter->next)
		if (iter->student.general.ID == student.general.ID) {
			iter->student = student;
			break;
		}

	studentList.update(student.classID);
	studentList._delete();

	studentList.loadAll();
	for (auto iter = studentList.head; iter != nullptr; iter = iter->next)
		if (iter->student.general.ID == student.general.ID) {
			studentList._delete(iter);
			break;
		}
	studentList.updateAll();
	studentList._delete();

	AccountList accountList;
	if (!accountList.load()) {
		system("pause");
		return;
	}
	for (auto iter = accountList.head; iter != nullptr; iter = iter->next)
		if (iter->account.userID == student.general.ID) {
			accountList._delete(iter);
			break;
		}
	accountList.update();
	accountList._delete();

	cout << "Remove " << student.general.fullname << " successfully!\n" << endl;
	system("pause");
}

void move_student() {
	cout << "Move a student to another class\n" << endl;

	StudentList studentList;
	if (!studentList.loadAll()) {
		system("pause");
		return;
	}

	Student student;

	const int max_turn = 3;
	int turn = 0;
	do {
		cout << "Enter the student's ID: ";
		string SID; getline(cin, SID);

		bool found = false;
		for (auto iter = studentList.head; iter != nullptr; iter = iter->next)
			if (iter->student.general.ID == SID) {
				student = iter->student;
				found = true;
			}

		if (!found)
			cout << SID << " not exists\n" << endl;
		else break;

		++turn;
	} while (turn < max_turn);
	if (turn == max_turn) {
		system("pause");
		return;
	}

	for (auto iter = studentList.head; iter != nullptr; iter = iter->next)
		if (iter->student.general.ID == student.general.ID) {
			studentList._delete(iter);
			break;
		}
	studentList.updateAll();
	studentList._delete();

	if (!studentList.load(student.classID)) {
		system("pause");
		return;
	}
	for (auto iter = studentList.head; iter != nullptr; iter = iter->next)
		if (iter->student.general.ID == student.general.ID) {
			student = iter->student;
			studentList._delete(iter);
			break;
		}
	studentList.update(student.classID);
	studentList._delete();

	string prev_class = student.classID;

	ifstream fi;
	turn = 0;
	do {
		cout << "Enter the class to move in: ";
		string tmp; getline(cin, tmp);

		fi.open("data/class/" + tmp + "-student.gulu");
		if (!fi.is_open()) {
			cout << tmp << " not found\n" << endl;
			if (++turn == max_turn) break;
		}
		else student.classID = tmp;
	} while (!fi.is_open());
	bool class_not_found = false;
	if (fi.is_open()) fi.close();
	else class_not_found = true;

	if (!studentList.load(student.classID)) {
		system("pause");
		return;
	}
	studentList.append(student);
	studentList.update(student.classID);
	studentList._delete();

	if (!studentList.loadAll()) {
		system("pause");
		return;
	}
	studentList.append(student);
	studentList.updateAll();
	studentList._delete();

	Account account;
	account.userID = student.general.ID;
	account.password = student.general.DoB.password();
	account.position = 2;

	AccountList accountList;
	if (!accountList.load()) {
		system("pause");
		return;
	}
	accountList.append(account);
	accountList.update();
	accountList._delete();

	if (!class_not_found)
		cout << "Move " << student.general.fullname << " from " << prev_class,
		cout << " to " << student.classID << " successfully!\n" << endl;
	system("pause");
}

void view_class_list() {
	cout << "View list of classes\n" << endl;

	ifstream in;
	in.open("data/class/class.gulu");
	if (!in.is_open())
	{
		cout << "Error: Missing class.gulu file\n";
		return;
	}

	ClassList classList;
	if (!classList.load()) {
		system("pause");
		return;
	}

	int x = classList.size();

	cout << "There ";
	if (x == 1) cout << "is"; else cout << "are";
	cout << " " << x << " class";
	if (x != 1) cout << "es";
	cout << ":\n\n";
	int i = 0;
	for (auto iter = classList.head; iter != nullptr; iter = iter->next)
		numtag(++i), cout << iter->ID << '\n';
	in.close();
	cout << endl;
	system("pause");
}

void view_student_list_of_class() {
	cout << "View list of students in a class\n" << endl;

	string class_code;

	ifstream fi;
	const int max_turn = 3;
	int turn = 0;
	do {
		cout << "Enter the class to view student list: ";
		string tmp; getline(cin, tmp);

		fi.open("data/class/" + tmp + "-student.gulu");
		if (!fi.is_open()) {
			cout << tmp << " not found\n" << endl;
			if (++turn == max_turn) break;
		}
		else class_code = tmp;
	} while (!fi.is_open());
	if (!fi.is_open()) {
		system("pause");
		return;
	}
	fi.close();

	StudentList studentList;
	if (!studentList.load(class_code)) {
		system("pause");
		return;
	}
	
	int nStudent = studentList.count();    

	cout << "\nThere ";
	if (nStudent == 1) cout << "is"; else cout << "are";
	cout << " " << nStudent << " student";
	if (nStudent != 1) cout << "s";
	cout << " in " << class_code << "\n";

	int i = 0;
	for (auto iter = studentList.head; iter != nullptr; iter = iter->next)
		if (iter->student.status == 1) {
			cout << "\n"; numtag(++i); cout << "\n";
			cout << iter->student.general.fullname << " (ID: " << iter->student.general.ID << ")\n";

			cout << "D.o.B: ";
			month_in_text(iter->student.general.DoB.month);
			cout << " " << iter->student.general.DoB.day << ", " << iter->student.general.DoB.year;
			cout << "\n";

			cout << "Sex: ";
			if (iter->student.general.sex) cout << "Male\n"; else cout << "Female\n";
		}

	cout << endl;
	system("pause");
}