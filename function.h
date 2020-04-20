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
};

struct User {
	string ID;
	int position = -1; // 0: Staff; 1: Lecturer; 2: Student
	string fullname;
	struct Date {
		int year = -1, month = -1, day = -1;
	} DoB;
	int sex = -1; // 0: Female; 1: Male
};

// administration
bool login(User& user); // (1/3) Staff done
int verified(User& user, string& pw);
bool get_info(User& user);
void menu(User& user);
int menuFunction(int user_position);

// tools
bool load_config(Config& config);
bool update_config(Config& config);
int int_option(int numberChoice = 10); // using getch() for one-click choosing
bool bool_option(string operation); // using getch() for one-click choosing

#endif FUNC_H