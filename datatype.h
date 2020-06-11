#ifndef DATATYPE
#define DATATYPE

#define _CRT_SECURE_NO_WARNINGS
#include "tools.h"
#include <time.h>

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
	} * head = nullptr, * tail = nullptr;

	int size();
	void append(Account account);
	bool load();
	void update();
	void _delete();
	void _delete(nodeAccount* p);
};

struct Date {
	int year = 0, month = 0, day = 0;

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
	string classID;
	int status; // 0: graduted; 1: studying; 2: reserved

	double midtermGrade = 0, finalGrade = 0, bonusGrade = 0, totalGrade = 0;
	int* attended = nullptr;

	bool load();

	void check_in();
	void view_check_in();
	void view_schedule();
	void view_course_score();
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
	bool loadCourse(int academic_year, int semester, string classID, string courseID);
	void updateCourse(int academic_year, int semester, string classID, string courseID);
};

struct Lecturer {
	User general;
	string degree;

	bool load();

	void view_course_list();
	void edit_attendance();
	void import_scoreboard();
	void edit_student_grade();
	void view_scoreboard();
};

struct LecturerList {
	struct nodeLecturer {
		Lecturer lecturer;
		nodeLecturer* next, * prev;
	} * head = nullptr, * tail = nullptr;

	int size();
	void append(Lecturer lecturer);
	bool load();
	void update();
	void _delete();
	void _delete(nodeLecturer* p);
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

struct Time {
	int hour = 0, minute = 0;
};

struct Course {
	string ID, name;
	string lectureID;
	string classID;
	Date startDate, endDate;

	int academic_year;
	int semester; // 1 to 3

	int sessionDay; // day of week
	Time startTime, endTime;
	string room;
	
	StudentList studentList;
};

struct CourseList {
	struct nodeCourse {
		Course course;
		nodeCourse* prev, * next;
	} * head = nullptr, * tail = nullptr;

	int size();
	void append(Course course);
	bool load(int academic_year, int semester, string classID);
	void update(int academic_year, int semester, string classID);
	void _delete();
	void _delete(nodeCourse* p);
};

int differ_day(Date begin, Date end);

#endif
