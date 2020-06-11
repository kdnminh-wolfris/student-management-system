#include "staff-scoreboard.h"

void view_scoreboard_course()
{
    cout << "View scoreboard of a course\n" << endl;

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

    int acayear = 2000 + (termCode[0] - 48) * 10 + (termCode[1] - 48);
    int semester = termCode[7] - 48;

    string courseID;
cout<<"Please type in the course ID:"<<endl;
getline(cin,courseID);
StudentList studentlist;
bool check=studentlist.loadCourse(acayear,semester,classID,courseID);
if (check)
{
StudentList::nodeStudent *cur=studentlist.head;
cout<<"\n          This is the scoreboard of course "<<courseID<<" for class "<<classID<<endl;
cout<<"  SID     Midterm     Final     Bonus     Total"<<endl;
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
}
else
{
    cout << "Cannot load the specified course with the data you entered." << endl;
}

cout << endl;
system("pause");
}

void export_scoreboard() // to csv
{
cout << "Export a scoreboard to csv file\n" << endl;

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

int acayear = 2000 + (termCode[0] - 48) * 10 + (termCode[1] - 48);
int semester = termCode[7] - 48;

ofstream output;
string courseID;

cout<<"Please type in the course ID:"<<endl;
getline(cin,courseID);

string academic=AcademicYearCode(acayear);
string semestercode=SemesterCode(semester);
string path="csv files/"+academic+"-"+semestercode+"-"+classID+"-"+courseID+"-scoreboard.csv";
StudentList studentlist;
bool check=studentlist.loadCourse(acayear,semester,classID,courseID);
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
        output<<"SID,Midterm,Final,Bonus,Total"<<endl;
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
        cur = nullptr;
    }

    cout << "\nExport scoreboard to csv file successfully!\n" << endl;
    system("pause");
}
else
{
    cout << "Cannot load the specified course with the information you entered." << endl;
    system("pause");
    return;
}
}