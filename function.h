#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <string>

using namespace std;
struct node{
	Student student;
	node*next,*prev;
};
struct Config {
	int login_status = 0;
	string curID;
	int curPosition = -1;
	int keep_login = 1;
};

struct Date {
	int year = -1, month = -1, day = -1;
};

struct User {
	string ID;
	int position = -1; // 0: Staff; 1: Lecturer; 2: Student
	string fullname;
	Date DoB;
	int sex = -1; // 0: Female; 1: Male
};

struct Student {
	User general;
	string class_;
	int status; // 0: graduted; 1: studying; 2: reserved
};

// administration
bool login(User& user); // (1/3) Staff done
int verified(User& user, string& pw);
bool get_info(User& user);
void menu(User& user);
int menuFunction(int user_position);

//academic staff-class
void import_student_from_csv(node*pHead);
bool edit_a_student(ifstream& fi, ofstream& fo);
void read_a_class(ifstream& fi, student editing_class[], int& numberStudent, int class_num);
void rewrite_a_class(ofstream& fo, student editing_class[], int& numberStudent, int class_num);


// tools
bool load_config(Config& config);
bool update_config(Config& config);
int int_option(int numberChoice = 10); // using getch() for one-click choosing
bool bool_option(string operation); // using getch() for one-click choosing

#endif FUNC_H
