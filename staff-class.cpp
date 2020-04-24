

#include "function.h"
void import_student_from_csv()
{
    ifstream in;
    ifstream inacc;//in as input for student list, inacc as input for creating student account
    ofstream out;
    ofstream outacc;//out as output for student list, outacc as output for creating student account
    string choice;
    cout<<"Please type in the name of the class you wish to import:"<<endl;
    getline(cin,choice);
    string classname;
    classname=choice;
            in.open(choice+"-Student.csv");
            if(!in) cout<<"There is an error trying to open 19APCS1-Student.csv"<<endl;
            else
            {
                nodeStudent*pHead=nullptr;
                int count=0;
                for (int i=0;i<5;++i)
                {
                    in.ignore(1000,','||'\n');
                }
                nodeStudent*cur=pHead;
                while (!in.eof())
                {
                    if (pHead==nullptr)//input 1st node
                    {
                        pHead=new nodeStudent;
                         in.ignore(100,',');
                        in>>pHead->student.general.ID;
                        in.ignore(100,',');
                        getline(in,pHead->student.general.fullname);
                        in.ignore(100,',');
                        in>>pHead->student.general.sex;
                        pHead->student.general.position=2;
                        in>>pHead->student.general.DoB.year;
                        in>>pHead->student.general.DoB.month;
                        in>>pHead->student.general.DoB.day;
                        in.ignore (100,',');
                        in>>pHead->student.class_;
                        pHead->student.status=1;
                        pHead->student.general.position=2;
                        count++;
                        cur=pHead;
                        pHead->next=nullptr;
                        pHead->prev=nullptr;
                    }

                    else{//input other nodes
                    cur->next=new nodeStudent;
                    nodeStudent*temp=cur;
                    cur=cur->next;
                    cur->prev=temp;
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
                    cur->next=nullptr;
                    }
                }
                in.close();
                inacc.open("data/account.gulu",std::fstream::app);
                cur=pHead;
                nodeAccount*pHeadaccount=nullptr;
                nodeAccount*curacc=pHeadaccount;
                while (cur!=nullptr)
                {
                     if (pHeadaccount==nullptr)
                     {
                     pHeadaccount=new nodeAccount;
                     pHeadaccount->data.userID=cur->student.general.ID;
                     string pass=to_string(cur->student.general.DoB.year);
                     pass.append(to_string(cur->student.general.DoB.month));
                     pass.append(to_string(cur->student.general.DoB.day));
                     pHeadaccount->data.password=pass;
                     pHeadaccount->prev=nullptr;
                     pHeadaccount->next=nullptr;
                     curacc=pHeadaccount;
                     cur=cur->next;                  
                     }
                     else{
                      curacc->next=new nodeAccount;
                      nodeAccount*tempacc=curacc;
                      curacc=curacc->next;
                      curacc->data.userID=cur->student.general.ID;
                     string pass=to_string(cur->student.general.DoB.year);
                     pass.append(to_string(cur->student.general.DoB.month));
                     pass.append(to_string(cur->student.general.DoB.day));
                     curacc->data.password=pass;
                     curacc->prev=tempacc;
                     curacc->next=nullptr;
                     ;  
                     }
                }            
                inacc.close();
                //_mkdir("/data/class/"+classname);
                out.open("/data/class/"+classname+"/"+classname+"-Student.gulu");
                {

                }
            }
    
    if (out.is_open())
    {
        
    }
    else cout<<"The file cannot be created."<<endl;
      
}
void create_account(){//Pls put pHeadacc=nullptr outside function

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
    nodeStudent * _student=nullptr;
    int numberStudent=0;
    read_a_class(fi,_student,numberStudent,tmp_Class);
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
                string new_pw= to_string(tmp_DoB.year*10000+tmp_DoB.month*100+tmp_DoB.day);
                int numberAccount=0;
                nodeAccount *listAccount;
                load_account(numberAccount,listAccount);
                nodeAccount *temp = listAccount;
                for (int i=0;i<numberAccount;++i){
                    if (temp->data.userID==cur->student.general.ID){
                        temp->data.password=new_pw;
                        break;
                    }
                    temp=temp->next;
                }
                update_account(numberAccount,listAccount);
            }
        }
    }
    fi.close();
    rewrite_a_class(fo,_student,numberStudent,tmp_Class);
    deleteNodeStudent(_student);
    deleteNodeClass(Classes);
    return true;
}

void read_a_class(ifstream &fi, nodeStudent *& _student, int &numberStudent, string tmp_class){
    fi.open("data/class/"+tmp_class+"/student.gulu");
    if (!fi) {
        cout <<"Error! Missing  file";
        return ;
    }
    fi>>numberStudent;
    fi.get();
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

void rewrite_a_class(ofstream &fo,nodeStudent *&_student,int &numberStudent,string tmp_class){
    fo.open("data/class/"+tmp_class+"/student.gulu");
    fo<<numberStudent<<endl<<endl;
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
    
    fi.open("data/class/class.gulu");
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
    int i=0;
    nodeStudent * _student=nullptr;
    int numberStudent=0;
    read_a_class(fi,_student,numberStudent,tmp_Class);
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
        rewrite_a_class(fo,_student,numberStudent,tmp_Class);
    }
    deleteNodeStudent(_student);
    deleteNodeClass(Classes);
    return true;
}

void view_class_list()
{
    ifstream in;
    in.open("data/class/class.gulu");
    if(!in.is_open())
    {
        cout << "Cannot open file\n";
        return;
    }
    int x; in>>x;
    cout << "There are " << x << " classes: \n";
    string class_code;
    for(int i=0; i<x; i++)
    {
        in>>class_code;
        cout << class_code << '\n';
    }
    in.close();
}

void view_list_of_student_in_class(string class_code) //Take the code of the class and print out the students in that class
{
    ifstream fi;
    fi.open("data/class/class.gulu");
    if(!fi.is_open())
    {
        cout << "Cannot open file\n";
        return;
    }
    int x; fi>>x;
    bool flag = false;
    for(int i=0; i<x; i++)
    {
        string class_code0;
        fi>>class_code0;
        if(class_code0==class_code) flag = true;
    }
    fi.close();
    if(!flag)
    {
        cout << "The class you enter does not exist\n";
        return;
    }
    string link = "data/class/"+class_code+"/student.gulu";
    fi.open(link);
    if(!fi.is_open())
    {
        cout << "Cannot open file\n";
        return;
    }
    fi>>x;
    cout << "This is the information in class\n";
    cout << "There are "<<x<<" students in this class\n";
    while(!fi.eof())
    {
        string info;
        getline(fi, info, '\n');
        cout << info << '\n';
    }
    fi.close();
}
