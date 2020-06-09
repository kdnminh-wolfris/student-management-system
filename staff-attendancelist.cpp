#include "staff-attendancelist.h"

void export_attendance_list() {
    cout << "Export an attendance list to csv file\n" << endl;

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

    cout << "Please enter the code of the course?\n";
    string courseID; getline(cin, courseID);

    StudentList sl;
    if(!sl.loadCourse(acayear, semester, classID, courseID)) return;
    StudentList::nodeStudent *ns = sl.head;
    ofstream myfile("csv files/"+AcademicYearCode(acayear)+"-"+SemesterCode(semester)+"-"+classID+"-"+courseID+"-attendance-list.csv");
    if(!myfile.is_open()) {
    	sl._delete();
    	cout << "Cannot open file.\n";
        system("pause");
    	return;
    }

    myfile << "SID,";
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
    cout << "\nExport attendance list to csv file sucessfully!\n" << endl;
    system("pause");
}