#include "staff_class.h"

void import_from_csv() {
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
			cout << "Error: Missing " << classID << "-student.csv file\n" << endl;
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
			char ch; fi >> ch;
			if (ch != ',') tmp.general.ID += ch;
			else break;
		} while (true);

		do {
			char ch; fi >> ch;
			if (ch != ',') tmp.general.fullname += ch;
			else break;
		} while (true);

		fi >> tmp.general.sex;
		fi.ignore();

		fi >> tmp.general.DoB.year >> tmp.general.DoB.month >> tmp.general.DoB.day;

		tmp.general.position = 2;
		tmp.class_ = classID;
		tmp.status = 1;

		studentList.append(tmp);
	}

	fi.close();

	studentList.tail = studentList.tail->prev;
	delete studentList.tail->next;
	studentList.tail->next = nullptr;

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
	system("pause");
}

void add_new_student() {
	ifstream fi;

	Student student;

	const int max_turn = 3;
	int turn = 0;
	do {
		cout << "Enter new student's class: ";
		getline(cin, student.class_);

		fi.open("data/class/" + student.class_ + "-student.gulu");
		if (!fi.is_open()) {
			cout << "Error: Missing " << student.class_ << "-student.gulu file\n" << endl;
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
	if (!studentList.load(student.class_)) {
		system("pause");
		return;
	}
	studentList.append(student);
	studentList.update(student.class_);
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

	cout << '\n' << student.general.fullname << " has been added into " << student.class_ << " successfully!\n" << endl;
	system("pause");
}