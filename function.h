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

// administration
bool login(User& _user);
int verified(User& _user, string& pw);
bool get_info(User& _user);

// tools
int choose_option(int high = 9); // using getch() for one-click choosing

#endif FUNC_H