#ifndef DATATYPE
#define DATATYPE

#include "tools.h"

struct Config {
	int login_status = 0;
	string curID;
	int curPosition = -1;
	int keep_login = 1;
	int max_enterpw_turn = 3;

	bool load();
	void update();
};

struct Account {
	string userID, password;
	int position = -1; // 0: Staff; 1: Lecturer; 2: Student
};

struct AccountList {
	struct nodeAccount {
		Account account;
		nodeAccount* next, * prev;
	} * head, * tail;

	int size();
	void append(Account account);
	bool load();
	void update();
	void _delete();
	void _delete(nodeAccount* p);
};

struct Date {
	int year = -1, month = -1, day = -1;

	bool input();
	string password();
};

struct User {
	string ID;
	int position = -1; // 0: Staff; 1: Lecturer; 2: Student
	string fullname;
	Date DoB;
	int sex = -1; // 0: Female; 1: Male

	bool get_info();
	void view_profile();
	void profileStaff();
	void profileLecturer();
	void profileStudent();
};

struct Student {
	User general;
	string class_;
	int status; // 0: graduted; 1: studying; 2: reserved

	bool load();
};

struct StudentList {
	struct nodeStudent {
		Student student;
		nodeStudent* next, * prev;
	} * head = nullptr, * tail = nullptr;

	int size();
	int count();
	void append(Student student);
	bool load(string classID);
	void update(string classID);
	bool loadAll();
	void updateAll();
	void _delete();
	void _delete(nodeStudent* p);
};

struct Lecturer {
	User general;
	string degree;

	bool load();
};

struct nodeLecturer {
	Lecturer lecturer;
	nodeLecturer* next, * prev;
};

struct ClassList {
	struct nodeClass {
		string ID;
		nodeClass* next, * prev;
	} * head = nullptr, * tail = nullptr;

	int size();
	void append(string ID);
	bool load();
	void update();
	void _delete();
	void _delete(nodeClass* p);
};

#endif
