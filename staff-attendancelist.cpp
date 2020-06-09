#include "staff-attendancelist.h"

void view_attendance_list_course() {
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


void export_attendance_list() {
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
    ofstream myfile("csv files/"+AcademicYearCode(academic_year)+"-"+SemesterCode(semester)+"-"+classID+"-"+courseID+"-attendance-list.csv");
    if(!myfile.is_open()) {
    	sl._delete();
    	cout << "Cannot open file.\n";
    	return;
    }

    myfile << "Student's ID,";
    for(int i=1; i<=10; i++)
        if(i<10) myfile << "W0" << i << ",";
        else myfile << "W" << 10 << '\n';

    while(ns!=nullptr)
    {
        Student sd = ns->student;
        myfile << sd.general.ID << ",";
        for(int i=0; i<10; i++)
        {
        	if(i==9) {
	            if(sd.attended[i]) myfile <<"1\n";
	            else myfile <<"0\n";
	        }
	        else {
	        	if(sd.attended[i]) myfile <<"1,";
	            else myfile <<"0,";
	        }
        };
        ns = ns->next;
    }
    myfile.close();
    sl._delete();
    cout << "Data exported sucessfully.\n";
}



