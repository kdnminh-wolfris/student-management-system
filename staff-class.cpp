

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

bool edit_a_student(){
    ifstream fi;
    ofstream fo;
    
    fi.open("/Users/nguyennguyenkhanh/Documents/GitHub/CS162-19APCS2-gulugulu/data/class/class.gulu");
    if (!fi) {
        cout <<"Error! Missing Class.txt file";
        return false;
    }
    int numberClass;
    fi>>numberClass;
    fi.get();
    nodeClass *Classes=nullptr;
    cout <<"All classes :"<<endl;
    nodeClass *temp=Classes;
    for (int i=0;i<numberClass;++i){
        if (Classes ==nullptr) {
            temp =new nodeClass;
            temp->prev=nullptr;
            Classes = temp;
        }
        getline(fi,temp->name,'\n');
        cout <<temp->name<<endl;
        if (i<numberClass-1){
            temp->next= new nodeClass;
            temp->next->prev= temp;
            temp=temp->next;
        }
        else temp->next= nullptr;
    }
    fi.close();
    string tmp_Class;
    cout <<"Enter the student's class :";
    getline(cin,tmp_Class,'\n');
    int i=0,class_num=0;
    temp=Classes;
    while (temp->name != tmp_Class) {
       ++class_num;
        temp=temp->next;
    }
    
    nodeStudent * _student=nullptr;
    int numberStudent=0;
    read_a_class(fi,_student,numberStudent,class_num);
    string tmp_ID;
    cout <<"The ID of the student you want to edit : ";
    getline(cin,tmp_ID,'\n');
    
    nodeStudent *cur= _student;
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
    deleteNodeStudent(_student);
    deleteNodeClass(Classes);
    return true;
}

void read_a_class(ifstream &fi, nodeStudent *& _student, int &numberStudent, int class_num){
    switch(class_num){
        case 0:{
            fi.open("/Users/nguyennguyenkhanh/Documents/GitHub/CS162-19APCS2-gulugulu/data/class/Student-19APCS1.txt");
            if (!fi) {
                cout <<"Error! Missing  file";
                return ;
            }
            break;
        }
    }
    fi>>numberStudent;
    fi.get();
    nodeStudent *cur=_student;
    for (int i=0;i<numberStudent;++i){
        if (_student == nullptr) {
            cur=new nodeStudent;
            cur->prev=nullptr;
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
            cur->next=new nodeStudent;
            cur->next->prev= cur;
            cur=cur->next;
        }
        else cur->next = nullptr;
    }
    fi.close();
}

void rewrite_a_class(ofstream &fo,nodeStudent *&_student,int &numberStudent,int class_num){
    switch(class_num){
        case 0:{
            fo.open("/Users/nguyennguyenkhanh/Documents/GitHub/CS162-19APCS2-gulugulu/data/class/Student-19APCS1.txt");
            break;
        }
    }
    fo<<numberStudent<<endl;
    nodeStudent *cur=_student;
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
    
    fi.open("/Users/nguyennguyenkhanh/Documents/GitHub/CS162-19APCS2-gulugulu/data/class/class.gulu");
    if (!fi) {
        cout <<"Error! Missing Class.txt file";
        return false;
    }
    int numberClass;
    fi>>numberClass;
    fi.get();
    nodeClass *Classes=nullptr;
    cout <<"All classes :"<<endl;
    nodeClass *temp=Classes;
    for (int i=0;i<numberClass;++i){
        if (Classes ==nullptr) {
            temp =new nodeClass;
            temp->prev=nullptr;
            Classes = temp;
        }
        getline(fi,temp->name,'\n');
        cout <<temp->name<<endl;
        if (i<numberClass-1){
            temp->next= new nodeClass;
            temp->next->prev= temp;
            temp=temp->next;
        }
        else temp->next= nullptr;
    }
    fi.close();
    string tmp_Class;
    cout <<"Enter the student's class :";
    getline(cin,tmp_Class,'\n');
    int i=0,class_num=0;
    while (temp->name != tmp_Class) {
       ++class_num;
        temp=temp->next;
    }
    
    nodeStudent * _student=nullptr;
    int numberStudent=0;
    read_a_class(fi,_student,numberStudent,class_num);
    string tmp_ID;
    cout <<"The ID of the student you want to edit : ";
    getline(cin,tmp_ID,'\n');
    nodeStudent *cur= _student;
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
    deleteNodeStudent(_student);
    deleteNodeClass(Classes);
    return true;
}

void deleteNodeStudent(nodeStudent *&pHead){
    nodeStudent *cur=pHead;
    while (cur!=nullptr){
        cur=cur->next;
        delete pHead;
        pHead= cur;
    }
}

void deleteNodeClass(nodeClass *&pHead){
    nodeClass *cur=pHead;
    while (cur!=nullptr){
        cur=cur->next;
        delete pHead;
        pHead= cur;
    }
}


