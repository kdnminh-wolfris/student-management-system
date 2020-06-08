#include "tools.h"

void numtag(int num) {
	cout << "[";
	if (num < 10)
		cout << " ";
	cout << num << " ] ";
}

int int_option(int numberChoice) {
	int ret;
	string tmp;

	while (true) {
		cout << "\nChoose an option to continue...: ";
		cout.flush();

		getline(cin, tmp);

		ret = 0;

		for (int i = int(tmp.length()) - 1; i >= 0; --i)
			if ('0' <= tmp[i] && tmp[i] <= '9') {
				ret = ret * 10 + (tmp[i] - 48);
			}
			else {
				ret = -1; break;
			}
		
		if (tmp.length() && 0 <= ret && ret < numberChoice)
			break;
		
		cout << "Invalid option! Please type again your option.\n" << endl;
	}

	cout << endl;

	return ret;
}

bool bool_option(string operation) {
	if (operation != "")
		cout << "Are you sure you want to " << operation << "?\n";
	cout << "[Y]ES          [N]O\n\n";

	string tmp;

	while (true) {
		cout << "Enter Y/N to continue... ";
		cout.flush();

		getline(cin, tmp);

		if (tmp == "Y" || tmp == "y" || tmp == "N" || tmp == "n")
			break;

		cout << "Invalid option! Please type again your option.\n" << endl;
	}

	cout << endl;

	return tmp[0] == 'Y' || tmp[0] == 'y';
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

int differ_day(Date begin, Date end){
    int day=0;
    while (begin.year!=end.year){
        if ((begin.year%400==0)||((begin.year%4==0)&&(begin.year%100!=0))){
            day = day +366;
        }
        else day = day +365;
    ++begin.year;
    }
    while (begin.month!=end.month){
        if (begin.month>end.month){
            if (end.month==2) {
                if ((end.year%400==0)||((end.year%4==0)&&(end.year%100!=0))) day = day -29;
                else day = day -28;
                ++end.month;
            }
            else if ((end.month==4)||(end.month==6)||(end.month==9)||(end.month==11)){
                day = day -30;
                ++end.month;
            }
            else {
                day =day -31;
                ++end.month;
            }
        }
        if (begin.month<end.month){
            if (begin.month==2){
                if ((end.year%400==0)||((end.year%4==0)&&(end.year%100!=0))) day = day +29;
                else day = day +28;
                ++begin.month;
            }
            else if  ((begin.month==4)||(begin.month==6)||(begin.month==9)||( begin.month==11)){
                day = day +30;
                ++begin.month;
            }
            else {
                day =day +31;
                ++begin.month;
            }
        }

    }
    day = day -begin.day+end.day;
    return day;
}
