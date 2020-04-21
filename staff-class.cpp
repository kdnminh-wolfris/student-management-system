

#include "function.h"
void import_student_from_csv()
{
    ifstream in;
    ifstream inacc;//in as input for student list, inacc as input for creating student account
    ofstream out;
    ofstream outacc;//out as output for student list, outacc as output for creating student account
    //list of choice:
    //0:19APCS1
    int choice;
    cout<<"Please type in the number of the class you wish to import from the following:"<<endl;
    cout<<"0.19APCS1"<<endl;
    inacc.open("data/account.gulu");
    switch (choice)
    {
        case 0:{
            
            in.open("19APCS1-Student.csv");
            if(!in) cout<<"There is an error trying to open 19APCS1-Student.csv"<<endl;
            else
            {
                nodeStudent*pHead;
                int count=0;
                for (int i=0;i<5;++i)
                {
                    in.ignore(1000,','||'\n');
                }
                nodeStudent*cur=pHead;
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
                    in.ignore (100,',');
                    in>>cur->student.class_;
                    cur->student.status=1;
                    cur->student.general.position=2;
                    count++;
                }

                in.close();
            }
                
        }
    }
    inacc.close();
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
    
    node *cur= _student;
    for (i=0;i<numberStudent;++i){
        if (cur->student.general.ID == tmp_ID) break;
        cur=cur->next;
    }
    if (cur->student.general.ID != tmp_ID){
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
    rewrite_a_class(fo,_student,numberStudent,class_num);
    deleteAll(_student);
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
    fo<<numberStudent<<endl;
    node *cur=_student;
    for (int i=0;i<numberStudent;++i){
        fo<<cur->student.general.ID<<endl
        <<cur->student.general.fullname<<endl
        <<cur->student.general.DoB.year<<" "<<cur->student.general.DoB.month<<                      " "<<cur->student.general.DoB.day<<endl
        <<cur->student.class_<<endl
        <<cur->student.status<<endl<<endl;
        cur=cur->next;
    }
    fo.close();
}

bool remove_a_student(){
    ifstream fi;
    ofstream fo;
    
    fi.open("data/class/class.gulu");
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
    
    node * _student=nullptr;
    int numberStudent=0;
    read_a_class(fi,_student,numberStudent,class_num);
    string tmp_ID;
    cout <<"The ID of the student you want to edit : ";
    getline(cin,tmp_ID,'\n');
    node *cur= _student;
    for (i=0;i<numberStudent;++i){
        if (cur->student.general.ID == tmp_ID) break;
        cur=cur->next;
    }
    if (cur->student.general.ID != tmp_ID){
        cout <<"This student is not exist in this class !!! "
        <<"Please choose again";
        edit_a_student();
    }
    else {
        cout <<"Fullname : "<<cur->student.general.fullname<<endl
        <<"Date of birt : "<<cur->student.general.DoB.year<<"/"<<cur->student.general.DoB.month
        <<"/"<<cur->student.general.DoB.day<<endl;
        if (!bool_option("remove this student ")) return false;
        else {
            cout <<"Please give the reason to remove this student(Choose the number below) : "<<endl
            <<"[1]. Graduated"<<endl<<"[2]. Reserved"<<endl<<endl;
            int choose;
            cin>>choose;
            if (choose ==1) cur->student.status=0;
            else cur->student.status=2;
        }
        rewrite_a_class(fo,_student,numberStudent,class_num);
    }
    deleteAll(_student);
    return true;
}

void deleteAll(node *&pHead){
    node *cur=pHead;
    while (cur!=nullptr){
        cur=cur->next;
        delete pHead;
        pHead= cur;
    }
}


