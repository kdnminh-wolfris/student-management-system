

#include "function.h"
void import_student_from_csv(node*pHead)
{
    ifstream in;
    ofstream out;
    //list of choice:
    //0:19APCS1
    int choice;
    cout<<"Please type in the number of the class you wish to import from the following:"
        <<"0.19APCS1"<<endl;
    switch (choice)
    {
        case 0:{
            in.open("19APCS1-Student.csv");
            if(!in) cout<<"There is an error trying to open 19APCS1-Student.csv"<<endl;
            else
            {
                for (int i=0;i<5;++i)
                {
                    in.ignore(1000,','||'\n');
                }
                node*cur=pHead;
                while (!in.eof())
                {
                    in.ignore(100,',');
                    in>>cur->student.general.ID;
                    in.ignore(100,',');
                    getline(in,cur->student.general.fullname);
                    in.ignore(100,',');
                    in>>cur->student.general.sex;
                    cur->student.general.position=2;
                    in>>cur->student.general.DoB.year;
                    in>>cur->student.general.DoB.month;
                    in>>cur->student.general.DoB.day;
                }
            }
                
        }
    }
}
bool edit_a_student(ifstream &fi, ofstream &fo){
    fi.open("data/Class.txt");
    if (!fi) {
        cout <<"Error! Missing Class.txt file";
        return false;
    }
    int numberClass;
    fi>>numberClass;
    fi.get();
    string Classes[numberClass];
    cout <<"All classes :"<<endl;
    for (int i=0;i<numberClass;++i){
        getline(fi,Classes[i],'\n');
        cout <<Classes[i]<<endl;
    }
    fi.close();
    string tmp_Class;
    cout <<"Enter the student's class :";
    getline(cin,tmp_Class,'\n');
    int i=0,class_num=0;
    while (Classes[class_num] != tmp_Class) ++class_num;
    cout <<class_num;
    student editing_class[10];
    int numberStudent=0;
    read_a_class(fi,editing_class,numberStudent,class_num);
    string tmp_ID;
    cout <<"The ID of the student you want to edit : ";
    getline(cin,tmp_ID,'\n');
    for (i=0;i<numberStudent;++i)
        if (editing_class[i].ID == tmp_ID) break;
    if (editing_class[i].ID != tmp_ID){
        cout <<"This student is not exist in this class !!! "
        <<"Please choose again";
        edit_a_student(fi,fo);
    }
    else {
        cout <<"Fullname : "<<editing_class[i].fullname<<endl
        <<"Date of birt : "<<editing_class[i].DoB.year<<"/"<<editing_class[i].DoB.month
        <<"/"<<editing_class[i].DoB.day<<endl
        <<"You want to edit this student ? "<<endl
        <<"1. Yes"<<endl<<"2.No"<<endl;
        int choose;
        cin>>choose;
        cin.get();
        if (choose == 2) return false;
        cout <<"Full name : ";
        getline(cin,editing_class[i].fullname,'\n');
        date tmp_DoB;
        cout <<"Date of Birth (YYYY/MM/DD) : "<<endl;
        cin>>tmp_DoB.year>>tmp_DoB.month>>tmp_DoB.day;
        if (tmp_DoB.day != editing_class[i].DoB.day || tmp_DoB.month != editing_class[i].DoB.month|| tmp_DoB.year != editing_class[i].DoB.year) {
            cout <<"This student's password has changed ! "<<endl;
            editing_class[i].DoB=tmp_DoB;
        }
    }
    fi.close();
    rewrite_a_class(fo,editing_class,numberStudent,class_num);
    return true;
}

void read_a_class(ifstream &fi, student editing_class[], int &numberStudent, int class_num){
    switch(class_num){
        case 0:{
            fi.open("data/class/Student-19APCS1.txt");
            if (!fi) {
                cout <<"Error! Missing  file";
                return ;
            }
            break;
        }
    }
    fi>>numberStudent;
    fi.get();
    for (int i=0;i<numberStudent;++i){
        getline(fi,editing_class[i].ID,'\n');
        cout <<editing_class[i].ID<<endl;
        getline(fi,editing_class[i].password,'\n');
        getline(fi,editing_class[i].fullname,'\n');
        fi>>editing_class[i].DoB.year>>editing_class[i].DoB.month>>editing_class[i].DoB.day;
        cout <<editing_class[i].DoB.year<<" "<<editing_class[i].DoB.month<<" "
        <<editing_class[i].DoB.day<<endl;
        fi.get();
        getline(fi,editing_class[i].Class,'\n');
        fi>>editing_class[i].status;
        fi.get();
        fi.ignore(1000,'\n');
    }
    fi.close();
}

void rewrite_a_class(ofstream &fo, student editing_class[],int &numberStudent,int class_num){
    switch(class_num){
        case 0:{
            fo.open("data/class/Student-19APCS1.txt");
            break;
        }
    }
    fo<<class_num<<endl<<endl;
    for (int i=0;i<numberStudent;++i){
        fo<<editing_class[i].ID<<endl
        <<editing_class[i].password<<endl
        <<editing_class[i].fullname<<endl
        <<editing_class[i].DoB.year<<" "<<editing_class[i].DoB.month<<                      " "<<editing_class[i].DoB.day<<endl
        <<editing_class[i].Class<<endl
        <<editing_class[i].status<<endl<<endl;
    }
    fo.close();
}
