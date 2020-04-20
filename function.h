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

struct User {
	string ID;
	int position; // 0: Staff; 1: Lecturer; 2: Student
	string fullname;
	struct Date {
		int year, month, day;
	} DoB;
	int sex; // 0: Female; 1: Male
};
struct date{
    int year, month,day;
};

struct student{
    string ID;
    string password;
    string fullname;
    date DoB;
    string Class;
    int status;
};

// administration
bool login(User& _user);
int verified(User& _user, string& pw);
bool get_info(User& _user);

bool edit_a_student(ifstream &fi, ofstream &fo);
void read_a_class(ifstream &fi, student editing_class[], int &numberStudent,int class_num);
void rewrite_a_class(ofstream &fo,student editing_class[],int &numberStudent,int class_num);
// tools
int choose_option(int high = 9); // using getch() for one-click choosing

#endif FUNC_H
