#include "tools.h"

void numtag(int num) {
	cout << "[";
	if (num < 10)
		cout << " ";
	cout << num << " ] ";
}

void month_in_text(int num) {
	switch (num) {
		case 1: {
			cout << "January";
			break;
		}
		case 2: {
			cout << "February";
			break;
		}
		case 3: {
			cout << "March";
			break;
		}
		case 4: {
			cout << "April";
			break;
		}
		case 5: {
			cout << "May";
			break;
		}
		case 6: {
			cout << "June";
			break;
		}
		case 7: {
			cout << "July";
			break;
		}
		case 8: {
			cout << "August";
			break;
		}
		case 9: {
			cout << "September";
			break;
		}
		case 10: {
			cout << "October";
			break;
		}
		case 11: {
			cout << "November";
			break;
		}
		case 12: {
			cout << "December";
			break;
		}
	}
}

bool valid_date(int year, int month, int day) {
	if (year % 4 == 0 && month == 2 && day == 29)
		return true;

	if (day < 1) return false;

	switch (month) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: {
			if (day <= 31) return true;
			else return false;
			break;
		}
		case 4:
		case 6:
		case 9:
		case 11: {
			if (day <= 30) return true;
			else return false;
			break;
		}
		case 2: {
			if (day <= 28) return true;
			else return false;
			break;
		}
		default: {
			return false;
		}
	}
}

string AcademicYearCode(int academic_year) {
	string ayearCode = "";
	ayearCode += char(academic_year / 10 % 10 + 48);
	ayearCode += char(academic_year % 10 + 48);
	++academic_year;
	ayearCode += char(academic_year / 10 % 10 + 48);
	ayearCode += char(academic_year % 10 + 48);
	return ayearCode;
}

string SemesterCode(int semester) {
	return semester == 1 ? "HK1" : semester == 2 ? "HK2" : "HK3";
}

string weekdayCode(int day) {
	switch (day) {
		case 2: return "MON";
		case 3: return "TUE";
		case 4: return "WED";
		case 5: return "THU";
		case 6: return "FRI";
		case 7: return "SAT";
	}
}
