#include "datatype.h"

bool Config::load() {
	ifstream fi;
	fi.open("data/config.gulu");
	if (!fi.is_open()) {
		cout << "Error: Missing config.gulu file\n" << endl;
		return false;
	}

	fi >> login_status; fi.ignore(100, '\n');
	getline(fi, curID);
	fi >> curPosition;
	fi >> keep_login;
	fi >> max_enterpw_turn;

	fi.close();
	return true;
}

void Config::update() {
	ofstream fo;
	fo.open("data/config.gulu");

	fo << login_status << '\n';
	fo << curID << '\n';
	fo << curPosition << '\n';
	fo << keep_login << '\n';
	fo << max_enterpw_turn;

	fo.close();
}

int AccountList::size() {
	int ret = 0;
	for (nodeAccount* iter = head; iter != nullptr; iter = iter->next, ++ret);
	return ret;
}

void AccountList::append(Account account) {
	if (head == nullptr)
		head = tail = new nodeAccount,
		head->prev = nullptr;
	else
		tail->next = new nodeAccount,
		tail->next->prev = tail,
		tail = tail->next;
	tail->account = account;
	tail->next = nullptr;
}

bool AccountList::load() {
	ifstream fi;
	fi.open("data/account.gulu");
	if (!fi.is_open()) {
		cout << "Error: Missing account.gulu file\n" << endl;
		return false;
	}

	int nAccount; fi >> nAccount;
	fi.ignore(100, '\n');

	head = tail = nullptr;
	while (nAccount--) {
		fi.ignore(100, '\n');

		Account tmp;
		getline(fi, tmp.userID);
		getline(fi, tmp.password);
		fi >> tmp.position;
		fi.ignore(100, '\n');

		append(tmp);
	}

	fi.close();
	return true;
}

void AccountList::update() {
	ofstream fo;
	fo.open("data/account.gulu");
	fo << size() << '\n';
	for (nodeAccount* iter = head; iter != nullptr; iter = iter->next) {
		fo << '\n' << iter->account.userID << '\n';
		fo << iter->account.password << '\n';
		fo << iter->account.position << '\n';
	}
	fo.close();
}

void AccountList::_delete() {
	while (head != nullptr) {
		auto tmp = head;
		head = head->next;
		delete tmp;
	}
	tail = nullptr;
}

void AccountList::_delete(nodeAccount* p) {
	if (head == p) head = head->next;
	if (tail == p) tail = tail->prev;
	if (p->next != nullptr)
		p->next->prev = p->prev;
	if (p->prev != nullptr)
		p->prev->next = p->next;
	delete p;
}

bool Date::input() {
	cout << "YYYY: ";
	cin >> year;
	if (year > 2020 || year < 1) return false;
	cout << "MM: ";
	cin >> month;
	if (month > 12 || month < 1) return false;
	cout << "DD: ";
	cin >> day;
	if (day > 31 || day < 1) return false;
	return true;
}

string Date::password() {
	string ret;
	int x = day;
	for (int i = 0; i < 2; ++i)
		ret = char(x % 10 + 48) + ret,
		x /= 10;
	x = month;
	for (int i = 0; i < 2; ++i)
		ret = char(x % 10 + 48) + ret,
		x /= 10;
	x = year;
	for (int i = 0; i < 4; ++i)
		ret = char(x % 10 + 48) + ret,
		x /= 10;
	
	return ret;
}

bool User::get_info() {
	ifstream fi;
	switch (position) {
	case 0: {
		fi.open("data/academic_staff.gulu");
		if (!fi.is_open()) {
			cout << "Error: Missing academic_staff.gulu file\n" << endl;
			return false;
		}

		int numberStaff;
		fi >> numberStaff;
		fi.ignore(100, '\n');

		string tmpID = ID;

		while (numberStaff--) {
			fi.ignore(100, '\n');
			getline(fi, ID);
			getline(fi, fullname);

			fi >> DoB.year;
			fi >> DoB.month;
			fi >> DoB.day;

			fi >> sex;
			fi.ignore(100, '\n');

			if (tmpID == ID) {
				fi.close(); return true;
			}
		}

		fi.close();
		cout << "Error: Missing << " << ID << " in academic_staff.gulu\n" << endl;
		return false;
	}

	case 1: {
		fi.open("data/lecturer.gulu");
		if (!fi.is_open()) {
			cout << "Error: Missing lecturer.gulu file\n" << endl;
			return false;
		}

		int numberLecturer;
		fi >> numberLecturer;
		fi.ignore(100, '\n');

		while (numberLecturer--) {
			fi.ignore(100, '\n');

			string tmpID;
			getline(fi, tmpID);
			getline(fi, fullname);
			fi >> DoB.year >> DoB.month >> DoB.day;
			fi >> sex;
			fi.ignore(100, '\n');
			fi.ignore(100, '\n');

			if (tmpID == ID) {
				fi.close(); return true;
			}
		}

		fi.close();
		cout << "Error: Missing " << ID << " in lecturer.gulu\n" << endl;
		return false;
	}

	case 2: {
		fi.open("data/student.gulu");
		if (!fi.is_open()) {
			cout << "Error: Missing student.gulu file\n" << endl;
			return false;
		}

		int numberStudent;
		fi >> numberStudent;
		fi.ignore(100, '\n');

		string tmpID, tmpClassCode;
		bool found = false;

		while (numberStudent--) {
			fi.ignore(100, '\n');
			getline(fi, tmpID);
			getline(fi, tmpClassCode);
			if (tmpID == ID) {
				found = true;
			}
		}

		fi.close();
		if (!found) {
			cout << "Error: Missing this user in student.gulu\n" << endl;
			return false;
		}

		fi.open("data/class/" + tmpClassCode + "-student.gulu");
		if (!fi.is_open()) {
			cout << "Error: Missing " << tmpClassCode << "-student.gulu file\n" << endl;
			return false;
		}

		fi >> numberStudent;
		fi.ignore(100, '\n');

		tmpID = ID;

		while (numberStudent--) {
			fi.ignore(100, '\n');
			getline(fi, ID);
			getline(fi, fullname);

			fi >> DoB.year;
			fi >> DoB.month;
			fi >> DoB.day;

			fi >> sex;
			fi.ignore(100, '\n');
			fi.ignore(100, '\n');

			if (tmpID == ID) {
				fi.close(); return true;
			}
		}

		fi.close();
		cout << "Error: Missing this user in " << tmpClassCode << "/student.gulu\n" << endl;
		return false;
	}
	}

	cout << "Error: User infomation not found\n" << endl;

	fi.close();
	return false;
}

void User::view_profile() {
	cout << "=========================================================\n";

	if (position < 2) {
		if (sex) cout << "Mr. ";
		else cout << "Ms. ";
	}
	cout << fullname << " (ID: " << ID << ")\n";

	cout << endl;

	cout << "D.o.B: ";
	month_in_text(DoB.month);
	cout << " " << DoB.day << ", " << DoB.year;
	cout << "\n";

	cout << "Sex: ";
	if (sex) cout << "Male\n"; else cout << "Female\n";

	cout << endl;

	cout << "Job title: ";
	if (position == 0) profileStaff();
	else if (position == 1) profileLecturer();
	else if (position == 2) profileStudent();

	cout << endl;

	cout << "=========================================================\n";

	system("pause");// Pause the console for reading purpose
}

void User::profileStaff() {
	cout << "Academic Staff\n";
}

void User::profileLecturer() {
	cout << "Lecturer\n";

	Lecturer lecturer;
	lecturer.general = *this;
	lecturer.load();

	cout << "Degree: " << lecturer.degree << '\n';
}

void User::profileStudent() {
	Student student;
	student.general = *this;
	student.load();

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

bool Student::load() {
	ifstream fi;
	fi.open("data/student.gulu");
	if (!fi.is_open()) {
		cout << "Error: Missing student.gulu file\n" << endl;
		return false;
	}

	int numberStudent;
	fi >> numberStudent;
	fi.ignore(100, '\n');

	bool found = false;

	while (numberStudent--) {
		fi.ignore(100, '\n');

		string tmpID;
		getline(fi, tmpID);
		getline(fi, class_);

		if (tmpID == general.ID) {
			found = true; break;
		}
	}

	fi.close();
	if (!found) {
		cout << "Error: Missing " << general.ID << " in student.gulu\n" << endl;
		return false;
	}

	fi.open("data/class/" + class_ + "-student.gulu");
	if (!fi.is_open()) {
		cout << "Error: Missing " << class_ << "-student.gulu file\n" << endl;
		return false;
	}

	fi >> numberStudent;
	fi.ignore(100, '\n');

	while (numberStudent--) {
		fi.ignore(100, '\n');

		string tmpID;
		getline(fi, tmpID);

		fi.ignore(100, '\n');
		fi.ignore(100, '\n');
		fi.ignore(100, '\n');

		fi >> status;
		fi.ignore(100, '\n');

		if (tmpID == general.ID) {
			fi.close(); return true;
		}
	}

	cout << "Error: Missing " << general.ID << " in " << class_ << "/student.gulu\n" << endl;
	return false;
}

int StudentList::size() {
	int ret = 0;
	for (nodeStudent* iter = head; iter != nullptr; iter = iter->next, ++ret);
	return ret;
}

int StudentList::count() {
	int ret = 0;
	for (nodeStudent* iter = head; iter != nullptr; iter = iter->next)
		ret += iter->student.status == 1;
	return ret;
}

void StudentList::append(Student student) {
	if (head == nullptr)
		head = tail = new nodeStudent,
		head->prev = nullptr;
	else
		tail->next = new nodeStudent,
		tail->next->prev = tail,
		tail = tail->next;
	tail->student = student;
	tail->next = nullptr;
}

bool StudentList::load(string classID) {
	ifstream fi;
	fi.open("data/class/" + classID + "-student.gulu");
	if (!fi.is_open()) {
		cout << "Error: Missing " << classID << "-student.gulu file\n" << endl;
		return false;
	}

	int nStudent; fi >> nStudent;
	fi.ignore(100, '\n');

	head = tail = nullptr;
	while (nStudent--) {
		fi.ignore(100, '\n');

		Student tmp;

		getline(fi, tmp.general.ID);
		getline(fi, tmp.general.fullname);
		fi >> tmp.general.DoB.year >> tmp.general.DoB.month >> tmp.general.DoB.day;
		fi >> tmp.general.sex;
		fi >> tmp.status;
		fi.ignore();

		tmp.class_ = classID;
		tmp.general.position = 2;

		append(tmp);
	}

	fi.close();
	return true;
}

void StudentList::update(string classID) {
	ofstream fo;
	fo.open("data/class/" + classID + "-student.gulu");
	fo << size() << '\n';
	for (nodeStudent* iter = head; iter != nullptr; iter = iter->next) {
		fo << '\n' << iter->student.general.ID << '\n';
		fo << iter->student.general.fullname << '\n';
		fo << iter->student.general.DoB.year << ' ';
		fo << iter->student.general.DoB.month << ' ';
		fo << iter->student.general.DoB.day << '\n';
		fo << iter->student.general.sex << '\n';
		fo << iter->student.status << '\n';
	}
	fo.close();
}

bool StudentList::loadAll() {
	ifstream fi;
	fi.open("data/student.gulu");
	if (!fi.is_open()) {
		cout << "Error: Missing student.gulu file\n" << endl;
		return false;
	}

	int nStudent; fi >> nStudent;
	fi.ignore(100, '\n');

	head = tail = nullptr;
	while (nStudent--) {
		fi.ignore(100, '\n');

		Student tmp;

		getline(fi, tmp.general.ID);
		getline(fi, tmp.class_);

		append(tmp);
	}

	fi.close();
	return true;
}

void StudentList::updateAll() {
	ofstream fo;
	fo.open("data/student.gulu");
	fo << size() << '\n';
	for (nodeStudent* iter = head; iter != nullptr; iter = iter->next) {
		fo << '\n' << iter->student.general.ID << '\n';
		fo << iter->student.class_ << '\n';
	}
	fo.close();
}

void StudentList::_delete() {
	while (head != nullptr) {
		auto tmp = head;
		head = head->next;
		delete tmp;
	}
	tail = nullptr;
}

void StudentList::_delete(nodeStudent* p) {
	if (head == p) head = head->next;
	if (tail == p) tail = tail->prev;
	if (p->next != nullptr)
		p->next->prev = p->prev;
	if (p->prev != nullptr)
		p->prev->next = p->next;
	delete p;
}

bool Lecturer::load() {
	ifstream fi;
	fi.open("data/lecturer.gulu");
	if (!fi.is_open()) {
		cout << "Error: Missing lecturer.gulu file\n" << endl;
		return false;
	}

	int numberLecturer;
	fi >> numberLecturer;
	fi.ignore(100, '\n');

	bool found = false;

	while (numberLecturer--) {
		fi.ignore(100, '\n');

		string tmpID;
		getline(fi, tmpID);
		getline(fi, general.fullname);
		fi >> general.DoB.year >> general.DoB.month >> general.DoB.day;
		fi >> general.sex;
		fi.ignore(100, '\n');
		getline(fi, degree);

		if (tmpID == general.ID) {
			found = true; break;
		}
	}

	fi.close();
	if (!found) {
		cout << "Error: Missing " << general.ID << " in lecturer.gulu\n" << endl;
		return false;
	}

	return true;
}

int ClassList::size() {
	int ret = 0;
	for (nodeClass* iter = head; iter != nullptr; iter = iter->next, ++ret);
	return ret;
}

void ClassList::append(string ID) {
	if (head == nullptr)
		head = tail = new nodeClass,
		head->prev = nullptr;
	else
		tail->next = new nodeClass,
		tail->next->prev = tail,
		tail = tail->next;
	tail->ID = ID;
	tail->next = nullptr;
}

bool ClassList::load() {
	ifstream fi;
	fi.open("data/class/class.gulu");
	if (!fi.is_open()) {
		cout << "Error: Missing class.gulu file\n" << endl;
		return false;
	}

	int nClass; fi >> nClass;
	fi.ignore(100, '\n');

	head = tail = nullptr;
	while (nClass--) {
		string tmp;  getline(fi, tmp);
		append(tmp);
	}

	fi.close();
	return true;
}

void ClassList::update() {
	ofstream fo;
	fo.open("data/class/class.gulu");
	fo << size() << '\n';
	for (nodeClass* iter = head; iter != nullptr; iter = iter->next)
		fo << iter->ID << '\n';
	fo.close();
}

void ClassList::_delete() {
	while (head != nullptr) {
		auto tmp = head;
		head = head->next;
		delete tmp;
	}
	tail = nullptr;
}

void ClassList::_delete(nodeClass* p) {
	if (head == p) head = head->next;
	if (tail == p) tail = tail->prev;
	if (p->next != nullptr)
		p->next->prev = p->prev;
	if (p->prev != nullptr)
		p->prev->next = p->next;
	delete p;
}