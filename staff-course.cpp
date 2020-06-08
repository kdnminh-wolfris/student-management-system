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

	cout << "\nImport " << termCode << "-" << classID + " schedule successfully!\n" << endl;
	system("pause");
}

void add_new_course() {
	cout << "Add a new course\n" << endl;

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
		if (!fi.is_open()) {
			cout << termCode << "-" << classID + "-schedule.gulu not found\n" << endl;
			if (++turn == max_turn) break;
		}
	} while (!fi.is_open());
	if (!fi.is_open()) {
		system("pause");
		return;
	}

	Course new_course;

	new_course.academic_year = 2000 + (termCode[0] - 48) * 10 + (termCode[1] - 48);
	new_course.semester = termCode[7] - 48;
	new_course.classID = classID;

	cout << "Please enter the ID of this new course?\n";
	getline(cin, new_course.ID);
	cout << "Please enter the full name of this course?\n";
	getline(cin, new_course.name);
	cout << "Please enter the ID of the lecturer of this course?\n";
	getline(cin, new_course.lectureID);
	cout << "Please enter the starting date of this course?\n";
	new_course.startDate.input();
	cout << "Please enter the finishing date of this course?\n";
	new_course.endDate.input();
	cout << "Please enter the session day in the week?\n";
	cin>>new_course.sessionDay;
	cout << "Please enter the starting time of this course (9 30 means 9h30)?\n";
	cin>>new_course.startTime.hour>>new_course.startTime.minute;
	cout << "Please enter the finishing time of this course (11 30 means 11h30)?\n";
	cin>>new_course.endTime.hour>>new_course.endTime.minute;
	cout << "Please enter the name of the room where the lectures are held?\n";
	cin.ignore(); getline(cin, new_course.room);
	string path_enrolled = "data/course/" + AcademicYearCode(new_course.academic_year)+"-"+SemesterCode(new_course.semester)+"-"+new_course.classID+"-"+new_course.ID+"-enrolled.gulu";
	ofstream out_enrolled;
	out_enrolled.open(path_enrolled.c_str());
	if(!out_enrolled.is_open())
	{
		cout << "Error: Cannot create file enrolled.gulu\n";
		system("pause");
		return;
	}
	CourseList cl; cl.load(new_course.academic_year, new_course.semester, new_course.classID);
    if(!new_course.studentList.load(new_course.classID))
    {
        cl._delete();
        out_enrolled.close();
		system("pause");
        return;
    }
	cl.append(new_course);
	cl.update(new_course.academic_year, new_course.semester, new_course.classID);
	cl._delete();
	out_enrolled.close();

	cout << "Add " << new_course.ID << " successfully!\n" << endl;

	system("pause");
}

void edit_course() {
    cout <<"Edit course information\n "<<endl;

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
		if (!fi.is_open()) {
			cout << termCode << "-" << classID + "-schedule.gulu not found\n" << endl;
			if (++turn == max_turn) break;
		}
	} while (!fi.is_open());
	if (!fi.is_open()) {
		system("pause");
		return;
	}

	Course course;

	course.academic_year = 2000 + (termCode[0] - 48) * 10 + (termCode[1] - 48);
	course.semester = termCode[7] - 48;
	course.classID = classID;

	CourseList courseList;
	courseList.load(course.academic_year, course.semester, course.classID);

	cout << "Course ID : ";
	getline(cin, course.ID);

	for (auto iter = courseList.head; iter != nullptr; iter = iter->next)
		if (iter->course.ID == course.ID) {
			course = iter->course; break;
		}
    
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
    
    cout <<"Start date : \n";
    cout <<course.startDate.year<<"/"<<course.startDate.month<<"/"<<course.startDate.day<<" -> \n";
    course.startDate.input();
    
    cout <<"End date : \n";
    cout <<course.endDate.year<<"/"<<course.endDate.month<<"/"<<course.endDate.day<<" -> \n";
    course.endDate.input();
    
	int temp;
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
    
    cin.ignore();
    cout <<"Room (enter a blank to maintain the current)\n";
    cout <<course.room<<" -> ";
    getline(cin,tmp,'\n');
    if (tmp!="") course.room=tmp;
    
    for (auto iter=courseList.head;iter!=nullptr;iter=iter->next)
    if (iter->course.ID==course.ID) {
        iter->course=course;
        break;
    }
    courseList.update(course.academic_year,course.semester,course.classID);
    cout << "Edit " << course.ID << "'s information successfully!\n" << endl;
    courseList._delete();
	system("pause");
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
string studentID;
string courseID;
string classname;
int semester;
int acayear;
cout<<"Please type in the academic year, ex:2019 for 2019-2020:"<<endl;
cin>>acayear;
cout<<"Please type in the semester of either 1 ,2 or 3:"<<endl;
cin>>semester;
cin.ignore();
cout<<"Please type in the course code of the student to be removed:"<<endl;
getline(cin,courseID);
cout<<"Please type in the class of the course in which the student is to be removed:"<<endl;
getline(cin,classname);
cout<<"Please type in the ID of the student to be removed:"<<endl;
getline(cin,studentID);
StudentList studentlist;
StudentList::nodeStudent *cur;
bool checklist=studentlist.loadCourse(acayear,semester,classname,courseID);
if (checklist){
	cur=studentlist.head;//set pointer cur to the head of student list in course
	while (cur!=nullptr)
	{
		if (cur->student.general.ID == studentID)
		{
			studentlist._delete(cur);//trying to delete the current student from the list
			cout << "The student " << studentID << " was successfully removed from course " << courseID << endl;
			break;
		}
		else cur = cur->next;
	}
	if (cur == nullptr)
	{
		cout << "The student with ID " << studentID << " was not found in the course " << courseID <<"of class"<<classname<< endl;
		studentlist._delete();
		system("pause");
		return;
	}
	studentlist.updateCourse(acayear,semester,classname,courseID);
	//delete all of the list of student previously loaded into function here
	studentlist._delete();
}
else 
{
	cout<<"The course you entered was incorrect. Please try again.";
	system("pause");
	return;
}
system("pause");
}

void add_student_to_course() {//WARNING: UNEXPECTED ERROR WHEN ADDING STUDENT: CREATE ANOTHER EMPTY STUDENT FIRST
	string studentID;
	string courseID;
	string classname;
	int semester;
	int acayear;
	cout << "Please type in the academic year, ex:2019 for 2019-2020:" << endl;
	cin >> acayear;
	cout << "Please type in the semester of either 1 ,2 or 3:" << endl;
	cin >> semester;
	cin.ignore();
	cout << "Please type in the course code of the student to be added:" << endl;
	getline(cin, courseID);
	cout<<"Please type in the class of the course in which the student is to be added:"<<endl;
	getline(cin,classname);
	cout << "Please type in the ID of the student to be added:" << endl;
	getline(cin, studentID);
	StudentList studentlist;
	StudentList::nodeStudent* cur;
	bool checklist=studentlist.loadCourse(acayear, semester, classname, courseID);
	if (checklist){
	cur = studentlist.tail;//set pointer cur to the last of student list in course
	cur->next = new StudentList::nodeStudent;
	StudentList::nodeStudent* temp = cur;
	cur = cur->next;
	cur->next = nullptr;
	cur->prev = temp;
	cur->student.classID = classname;
	cur->student.general.ID = studentID;
	//input score for the student, 0 is default
	cur->student.bonusGrade = 0;
	cur->student.finalGrade = 0;
	cur->student.midtermGrade = 0;
	cur->student.totalGrade = 0;
	//update the list of student in course
	studentlist.updateCourse(acayear, semester, classname, courseID);
	
	//delete all of the list of student previously loaded into function here
	studentlist._delete();
	}
	else {
		cout<<"Cannot find the specified course. Please try again"<<endl;
		system("pause");
		return;
	}
	system("pause");
}


void view_course_list() {
	//There are still some problems here, when calling cl.load() 
	//it prints out missing erolled.gulu
	//it should have looked for the file schedule.gulu instead
	cout << "Please enter the academic year.\n";
	int academic_year; cin>>academic_year;
	cout <<"Please enter the semester (1,2 or 3)?\n";
	int semester; cin>>semester;
	cout <<"Please enter the code of the class?\n";
	string classID; cin>>classID;

	CourseList cl;
	if(!cl.load(academic_year, semester, classID)) return;

	CourseList::nodeCourse *nc = cl.head;
	cout << "There are " << cl.size() << " courses in this list:\n";
	while(nc!=nullptr)
	{
		cout << nc->course.ID << " - " << nc->course.name << '\n';
		nc = nc->next;
	}
	cl._delete();
}

void view_student_list_of_course() {
    cout << "Please enter the academic year.\n";
    int academic_year; cin>>academic_year;
    cout <<"Please enter the semester (1,2 or 3)?\n";
    int semester; cin>>semester;
    cout <<"Please enter the code of the class?\n";
    string classID; cin>>classID;
    cout << "Please enter the code of the course?\n";
    string courseID; cin>>courseID;
    StudentList sl;
    if(!sl.loadCourse(academic_year, semester, classID, courseID)) return;

    StudentList::nodeStudent *ns = sl.head;
    cout << "There are " << sl.size() << " students in this course:\n";
    while(ns!=nullptr)
    {
        User cur_student = ns->student.general;
        cur_student.view_profile();
        ns = ns->next;
    }
    sl._delete();
}


void view_attendance_list_of_course() {
    cout << "Please enter the academic year.\n";
    int academic_year; cin>>academic_year;
    cout <<"Please enter the semester (1,2 or 3)?\n";
    int semester; cin>>semester;
    cout <<"Please enter the code of the class?\n";
    string classID; cin>>classID;
    cout << "Please enter the code of the course?\n";
    string courseID; cin>>courseID;
    StudentList sl;
    if(!sl.loadCourse(academic_year, semester, classID, courseID)) return;
    StudentList::nodeStudent *ns = sl.head;
    cout << "          This is the attendance list of the course " << courseID << '\n';
    cout << "(Note that * means that student attends that class while - otherwise)"<<'\n';
    cout << "              There are 10 weeks in this course" << '\n';
    cout << "Student's ID  ";
    for(int i=1; i<=10; i++)
        if(i<10) cout << "W0" << i << " ";
        else cout << "W" << 10 << '\n';

    while(ns!=nullptr)
    {
        Student sd = ns->student;
        cout << "   "<<sd.general.ID << " ";
        for(int i=0; i<10; i++)
        {
            if(sd.attended[i]) cout <<"   "<< "*";
            else cout <<"   "<< "-";
        }
        cout << "\n\n";
        ns = ns->next;
    }

    sl._delete();
}

void view_lecturer_list() {
    LecturerList lecturer_list;
    if(!lecturer_list.load()) return;

    LecturerList::nodeLecturer *nl = lecturer_list.head;
    while(nl!=nullptr)
    {
        Lecturer cur = nl->lecturer;
        cur.general.view_profile();
        nl = nl->next;
    }
    lecturer_list._delete();
}
