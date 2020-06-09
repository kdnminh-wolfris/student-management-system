#include "staff-scoreboard.h"

void view_scoreboard_course()
{
string courseID;
string classname;
int semester;
int acayear;
cout<<"Please type in the starting academic year:"<<endl;
cin>>acayear;
cout<<"Please type in the semester:"<<endl;
cin>>semester;
cin.ignore();
cout<<"Please type in the course ID:"<<endl;
getline(cin,courseID);
cout<<"Please type in the class ID of course"<<endl;
getline(cin,classname);
StudentList studentlist;
bool check=studentlist.loadCourse(acayear,semester,classname,courseID);
if (check)
{
StudentList::nodeStudent *cur=studentlist.head;
cout<<"          This is the scoreboard of course "<<courseID<<" for class "<<classname<<endl;
cout<<"   ID     Midterm     Final     Bonus     Total"<<endl;
while (cur!=nullptr)
    {
        cout<<cur->student.general.ID<<"    ";
        cout<<cur->student.midtermGrade<<"          ";
        cout<<cur->student.finalGrade<<"          ";
        cout<<cur->student.bonusGrade<<"        ";
        cout<<cur->student.totalGrade<<endl;
        cur=cur->next;
    }
studentlist._delete();
cur = nullptr;
system("pause");
}
else
{
    cout << "Cannot load the specified course with the data you entered." << endl;
    system("pause");
}
}
void export_scoreboard() // to csv
{
ofstream output;
string courseID;
string classname;
int semester;
int acayear;
cout<<"Please type in the starting academic year:"<<endl;
cin>>acayear;
cout<<"Please type in the semester:"<<endl;
cin>>semester;
cin.ignore();
cout<<"Please type in the course ID:"<<endl;
getline(cin,courseID);
cout<<"Please type in the class ID of course"<<endl;
getline(cin,classname);
string academic=AcademicYearCode(acayear);
string semestercode=SemesterCode(semester);
string path="csv files/"+academic+"-"+semestercode+"-"+classname+"-"+courseID+"-Scoreboard.csv";
StudentList studentlist;
bool check=studentlist.loadCourse(acayear,semester,classname,courseID);
if (check)
{
    StudentList::nodeStudent *cur=studentlist.head;
    output.open(path);
    if (!output.is_open())
    {
        cout<<"Cannot open file to export"<<endl;
        system("pause");
        return;
    }
    else
    {
        //output<< output the title if necessary
        output<<"ID,Midterm,Final,Bonus,Total"<<endl;
        while (cur!=nullptr)
        {
            output<<cur->student.general.ID<<",";
            output<<cur->student.midtermGrade<<",";
            output<<cur->student.finalGrade<<",";
            output<<cur->student.bonusGrade<<",";
            output<<cur->student.totalGrade<<","<<endl;
            cur=cur->next;
        }
        studentlist._delete();
        system("pause");
        cur = nullptr;
    }
}
else
{
    cout << "Cannot load the specified course with the information you entered." << endl;
    system("pause");
    return;
}
}