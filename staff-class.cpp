

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
                    in.getline(cur->student.general.fullname,100);
                }
            }
                
        }
    }
}

bool edit_a_student(){
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
        if (!bool_option("edit this student ")) return false;
        else{
            cin.get();
            cout <<"Full name : ";
            getline(cin,cur->student.general.fullname,'\n');
            Date tmp_DoB;
            cout <<"Date of Birth (YYYY/MM/DD) : "<<endl;
            cin>>tmp_DoB.year>>tmp_DoB.month>>tmp_DoB.day;
            if (tmp_DoB.day != cur->student.general.DoB.day || tmp_DoB.month != cur->student.general.DoB.month|| tmp_DoB.year != cur->student.general.DoB.year) {
                cout <<"This student's password has changed ! "<<endl;
                cur->student.general.DoB=tmp_DoB;
            }
        }
    }
    fi.close();
    rewrite_a_class(fo,_student,numberStudent,class_num);
    deleteAll(_student);
    return true;
}

void read_a_class(ifstream &fi, node *& _student, int &numberStudent, int class_num){
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
    node *cur=_student;
    for (int i=0;i<numberStudent;++i){
        if (_student == nullptr) {
            cur=new node;
            _student = cur;
        }
        getline(fi,cur->student.general.ID,'\n');
        getline(fi,cur->student.general.fullname,'\n');
        fi>>cur->student.general.DoB.year>>cur->student.general           .DoB.month>>cur->student.general.DoB.day;
        fi.get();
        getline(fi,cur->student.class_,'\n');
        fi>>cur->student.status;
        fi.get();
        fi.ignore(1000,'\n');
        if (i<numberStudent-1) {
            cur->next=new node;
            cur->next->prev= cur;
            cur=cur->next;
        }
        else cur->next = nullptr;
    }
    fi.close();
}

void rewrite_a_class(ofstream &fo,node *&_student,int &numberStudent,int class_num){
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


