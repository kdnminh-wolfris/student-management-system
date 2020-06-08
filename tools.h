#ifndef TOOLS
#define TOOLS

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void numtag(int num);
int int_option(int numberChoice = 10); // using getch() for one-click choosing
bool bool_option(string operation); // using getch() for one-click choosing
void month_in_text(int num);
bool valid_date(int year, int month, int day);
string AcademicYearCode(int academic_year);
string SemesterCode(int semester);
int differ_day(Date begin, Date end);
#endif
