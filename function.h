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

struct Config {
	int login_status = 0;
	string curID;
	int curPosition = -1;
	int keep_login = 1;
	int max_enterpw_turn = 3;
};

struct Account {
	string userID, password;
	int position = -1; // 0: Staff; 1: Lecturer; 2: Student
};

struct nodeAccount {
	Account data;
	nodeAccount* next, * prev;
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

struct nodeStudent {
	Student student;
	nodeStudent* next, * prev;
};

struct nodeClass{
    string name;
    nodeClass *next,*prev;
};

// administration
bool login(User& user, Config& config); // (1/3) Staff done
int verified(User& user, string& pw);
bool get_info(User& user);
bool changePassword(User& user, Config& config);

// menu
void menu(User& user, Config& config);
int menuFunction(int start, int user_position);

/*
//academic staff-class
void import_student_from_csv(node*pHead);
bool edit_a_student();
bool remove_a_student();
void read_a_class(ifstream & fi, nodeStudent *&_student , int& numberStudent, int class_num);
void rewrite_a_class(ofstream & fo, nodeStudent *& _student, int& numberStudent, int class_num);
void deleteNodeStudent(nodeStudent *&pHead);
void deleteNodeClass(nodeClass *&pHead);
*/

// tools
void numtag(int num);
bool load_config(Config& config);
void update_config(Config& config);
int int_option(int numberChoice = 10); // using getch() for one-click choosing
bool bool_option(string operation); // using getch() for one-click choosing
bool load_account(int& numberAccount, nodeAccount*& listAccount);
void update_account(int numberAccount, nodeAccount* listAccount);

#endif FUNC_H
