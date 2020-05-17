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
    int  acedemic_year, semester;
    string classID, courseID;
    cout <<"Edit course information\n "<<endl;
    CourseList courseList;
    const int max_turn=3;
    int turn=0;
    Course course;
    while (turn<max_turn){
        cout<<"PLease input "<<endl
        <<"Course ID : ";
        getline(cin,courseID,'\n');
        cout <<"Class : ";
        getline(cin,classID,'\n');
        cout <<"Acedemic year : ";
        cin>>acedemic_year;
        cout <<"Semester : ";
        cin>>semester;
        bool found=false;
        courseList.load(acedemic_year,semester,classID);
            for (auto iter=courseList.head;iter!=nullptr;iter=iter->next){
                if (iter->course.ID==courseID) {
                    found= true;
                    course=iter->course;
                    break;
                }
            }
        if (!found) cout <<courseID<<" not exist\n"<<endl;
        else break;
        ++turn;
    }
    if (turn==max_turn){
        return;
    }
    
    cin.get();
    string tmp;
    cout <<"Course ID (enter a blank to maintain the current)\n";
    cout <<course.ID<<" -> ";
    getline(cin,tmp,'\n');
    if (tmp!="") course.ID=tmp;
    
    cout <<"Course name(enter a blank to maintain the current)\n";
    cout <<course.name<<" -> ";
    getline(cin,tmp,'\n');
    if (tmp!="") course.name=tmp;
    
    cout <<"Lecturer ID (enter a blank to maintain the current)\n";
    cout <<course.lectureID<<" -> ";
    getline(cin,tmp,'\n');
    if (tmp!="") course.lectureID=tmp;
    
    cout <<"Class ID (enter a blank to maintain the current)\n";
    cout <<course.classID<<" -> ";
    getline(cin,tmp,'\n');
    if (tmp!="") course.classID=tmp;
    
    cout <<"Start date : \n";
    cout <<course.startDate.year<<"/"<<course.startDate.month<<"/"<<course.startDate.day<<" -> ";
    course.startDate.input();
    
    cout <<"End date : \n";
    cout <<course.endDate.year<<"/"<<course.endDate.month<<"/"<<course.endDate.day<<" -> ";
    course.endDate.input();
    
    int temp;
    cout <<"Acedemic year : \n";
    cout <<course.academic_year<<" -> ";
    cin>>temp;
    if (temp!=0) course.academic_year=temp;
    
    cout <<"Semester : \n";
    cout <<course.semester<<" -> ";
    cin>>temp;
    if (temp>0 && temp <4) course.semester=temp;
    
    cout <<"Session day (day of the week) : \n";
    cout <<course.sessionDay<<" -> ";
    cin>>temp;
    if (temp>1 && temp <8) course.sessionDay=temp;
    
    cout <<"Start time : \n";
    cout <<course.startTime.hour<<" : "<<course.startTime.minute<<" -> ";
    cin>>course.startTime.hour>>course.startTime.minute;
    
    cout <<"End time : \n";
    cout <<course.endTime.hour<<" : "<<course.endTime.minute<<" -> ";
    cin>>course.endTime.hour>>course.endTime.minute;
    
    cin.get();
    cout <<"Room (enter a blank to maintain the current)\n";
    cout <<course.room<<" -> ";
    getline(cin,tmp,'\n');
    if (tmp!="") course.room=tmp;
    
    for (auto iter=courseList.head;iter!=nullptr;iter=iter->next)
    if (iter->course.ID==courseID) {
        iter->course=course;
        break;
    }
    courseList.update(course.academic_year,course.semester,course.classID);
    cout << "Edit " << course.ID << "'s information successfully!\n" << endl;
    courseList._delete();
    
}
void remove_course() {
    cout<<"Remove a course\n"<<endl;
    
    int  acedemic_year, semester;
    string classID, courseID;
    CourseList courseList;
    const int max_turn=3;
    int turn=0;
    while (turn<max_turn){
        cout<<"PLease input "<<endl
        <<"Course ID : ";
        getline(cin,courseID,'\n');
        cout <<"Class : ";
        getline(cin,classID,'\n');
        cout <<"Acedemic year : ";
        cin>>acedemic_year;
        cout <<"Semester : ";
        cin>>semester;
        bool found=false;
        courseList.load(acedemic_year,semester,classID);
        for (auto iter=courseList.head;iter!=nullptr;iter=iter->next){
            if (iter->course.ID==courseID) {
                found= true;
                courseList._delete(iter);
                break;
            }
        }
        if (!found) cout <<courseID<<" not exist\n"<<endl;
        else {
            courseList.update(acedemic_year,semester,classID);
            cout <<"Remove "<<courseID<<" successfully"<<endl;
            break;
        }
        ++turn;
    }
    if (turn==max_turn){
        return;
    }
    courseList._delete();
}

void remove_student_from_course() {

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
