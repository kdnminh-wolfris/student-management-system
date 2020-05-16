#include "staff-course.h"

void import_course() {
	cout << "Import courses of a class\n" << endl;

	ifstream fi;

	string classID;
	string termCode;

	const int max_turn = 3;
	int turn = 0;
	do {
		int tturn = 0;
		do {
			cout << "Enter the academic year - the semester (ex. 1920-HK1): ";
			getline(cin, termCode);

			if (termCode.size() == 8 && termCode[4] == '-' && termCode[5] == 'H' && termCode[6] == 'K')
				if ('1' <= termCode[7] && termCode[7] <= '3')
					if (((termCode[0] - 48) * 10 + (termCode[1] - 48) + 1) % 100 == (termCode[2] - 48) * 10 + (termCode[3] - 48))
						break;

			cout << "Invalid code!\n" << endl;
			++tturn;
		} while (tturn < max_turn);
		if (tturn == max_turn) {
			system("pause");
			return;
		}

		cout << "Enter the imported class: ";
		getline(cin, classID);

		fi.open("data/course/" + termCode + "-" + classID + "-schedule.gulu");
		if (fi.is_open()) {
			fi.close();
			cout << termCode << "-" << classID << " schedule has already been imported!\n" << endl;
			++turn;
			continue;
		}

		fi.open("csv files/" + termCode + "-" + classID + "-schedule.csv");
		if (!fi.is_open()) {
			cout << termCode << "-" << classID + "-schedule.csv not found\n" << endl;
			if (++turn == max_turn) break;
		}
	} while (!fi.is_open());
	if (!fi.is_open()) {
		system("pause");
		return;
	}

	CourseList courseList;

	int academic_year = 2000 + ((termCode[0] - 48) * 10 + (termCode[1] - 48));
	int semester = termCode[7] - 48;

	fi.ignore(100, '\n');

	while (!fi.eof()) {
		fi.ignore(100, ',');
		Course tmp;

		do {
			char ch; fi.get(ch);
			if (ch != ',') tmp.ID += ch;
			else break;
		} while (true); // Course ID

		do {
			char ch; fi.get(ch);
			if (ch != ',') tmp.name += ch;
			else break;
		} while (true); // Course name

		do {
			char ch; fi.get(ch);
			if (ch != ',') tmp.lectureID += ch;
			else break;
		} while (true); // Lecture ID

		do {
			char ch; fi.get(ch);
			if (ch != '/')
				tmp.startDate.day = tmp.startDate.day * 10 + (ch - 48);
			else break;
		} while (true); // Start Day

		do {
			char ch; fi.get(ch);
			if (ch != '/')
				tmp.startDate.month = tmp.startDate.month * 10 + (ch - 48);
			else break;
		} while (true); // Start Month

		do {
			char ch; fi.get(ch);
			if (ch != ',')
				tmp.startDate.year = tmp.startDate.year * 10 + (ch - 48);
			else break;
		} while (true); // Start Year

		do {
			char ch; fi.get(ch);
			if (ch != '/')
				tmp.endDate.day = tmp.endDate.day * 10 + (ch - 48);
			else break;
		} while (true); // End Day

		do {
			char ch; fi.get(ch);
			if (ch != '/')
				tmp.endDate.month = tmp.endDate.month * 10 + (ch - 48);
			else break;
		} while (true); // End Month

		do {
			char ch; fi.get(ch);
			if (ch != ',')
				tmp.endDate.year = tmp.endDate.year * 10 + (ch - 48);
			else break;
		} while (true); // End Year

		string tmpstr = "";
		do {
			char ch; fi.get(ch);
			if (ch != ',') tmpstr += ch;
			else break;
		} while (true); // Session Day
		if (tmpstr == "MON") tmp.sessionDay = 2;
		else if (tmpstr == "TUE") tmp.sessionDay = 3;
		else if (tmpstr == "WED") tmp.sessionDay = 4;
		else if (tmpstr == "THU") tmp.sessionDay = 5;
		else if (tmpstr == "FRI") tmp.sessionDay = 6;
		else if (tmpstr == "SAT") tmp.sessionDay = 7;

		do {
			char ch; fi.get(ch);
			if (ch != ':')
				tmp.startTime.hour = tmp.startTime.hour * 10 + (ch - 48);
			else break;
		} while (true); // Start Hour

		do {
			char ch; fi.get(ch);
			if (ch != ',')
				tmp.startTime.minute = tmp.startTime.minute * 10 + (ch - 48);
			else break;
		} while (true); // Start Minute

		do {
			char ch; fi.get(ch);
			if (ch != ':')
				tmp.endTime.hour = tmp.endTime.hour * 10 + (ch - 48);
			else break;
		} while (true); // End Hour

		do {
			char ch; fi.get(ch);
			if (ch != ',')
				tmp.endTime.minute = tmp.endTime.minute * 10 + (ch - 48);
			else break;
		} while (true); // End Minute

		do {
			char ch; fi.get(ch);
			if (ch != '\n') tmp.room += ch;
			else break;
		} while (true); // Course name

		tmp.academic_year = academic_year;
		tmp.semester = semester;
		tmp.classID = classID;
		tmp.studentList.load(classID);

		courseList.append(tmp);
	}

	fi.close();

	courseList._delete(courseList.tail);
	courseList.update(academic_year, semester, classID);
	courseList._delete();

	cout << "\nImport " << termCode << "-" << classID + "schedule successfully!\n" << endl;
	system("pause");
}

void add_new_course() {

}

void edit_course() {

}
void remove_course() {

}

void remove_student_from_course() {
cin.ignore();
string studentID;
string courseID;
int semester;
int acayear;
cout<<"Please type in the academic year, ex:1920 for 2019-2020:"<<endl;
cin>>acayear;
cout<<"Please type in the semester of either 1 ,2 or 3:"<<endl;
cin>>semester;
cin.ignore();
cout<<"Please type in the course code of the student to be removed:"<<endl;
getline(cin,courseID);
cout<<"Please type in the ID of the student to be removed:"<<endl;
getline(cin,studentID);
CourseList listcourse;
bool check=listcourse.load(acayear,semester,courseID);
if (!check) return;
else 
	{
		 CourseList::nodeCourse *cur=listcourse.head;
		 while (cur!=nullptr)
		 {
			 if (cur->course.ID==courseID)
			{
				StudentList::nodeStudent *temp=cur->course.studentList.head;
				while (temp!=nullptr)
				{
					if (temp->next!=nullptr&&temp->next->student.general.ID==studentID)
					{
					StudentList::nodeStudent *todel=temp->next;
					temp->next=todel->next;
					delete todel;
					cout<<"Student removed successfully from course"<<endl;
					break;
					}
				}
				break;
			}
			else cur=cur->next;
		 }

	}
}

void add_student_to_course() {

}

void view_course_list() {

}

void view_student_list_of_course() {

}

void view_attendance_list_of_course() {

}

void view_lecturer_list() {

}