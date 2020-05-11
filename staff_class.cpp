#include "staff_class.h"

void import_from_csv() {
	ifstream fi;

	string classID;

	const int max_turn = 3;
	int turn = 0;
	do {
		cout << "Enter the imported class: ";
		cin >> classID;

		fi.open("csv files/" + classID + "-student.csv");
		if (!fi.is_open()) {
			cout << "There is no file called " << classID << "-student.csv!\n" << endl;
			if (++turn == max_turn) break;
		}
	} while (!fi.is_open());
	if (!fi.is_open()) return;

	ClassList classList;
	if (!classList.load()) {
		fi.close(); return;
	}
	
	classList.append(classID);
	classList.update();
	classList._delete();

	fi.ignore(100, '\n');

	StudentList studentList;
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
	}

	fi.close();

	studentList.update(classID);
	studentList._delete();

	AccountList accountList;
	accountList.load();

	for (auto p = studentList.head; p != nullptr; p = p->next) {
		Account tmp;

		tmp.userID = p->student.general.ID;

		int x = p->student.general.DoB.day;
		for (int i = 0; i < 2; ++i)
			tmp.password = char(x % 10 + 48) + tmp.password,
			x /= 10;
		x = p->student.general.DoB.month;
		for (int i = 0; i < 2; ++i)
			tmp.password = char(x % 10 + 48) + tmp.password,
			x /= 10;
		x = p->student.general.DoB.year;
		for (int i = 0; i < 4; ++i)
			tmp.password = char(x % 10 + 48) + tmp.password,
			x /= 10;

		tmp.position = 2;

		accountList.append(tmp);
	}

	accountList.update();
	accountList._delete();

	cout << "Import " << classID << " data successfully!\n" << endl;
	system("pause");
}