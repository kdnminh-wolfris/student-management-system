

#include "function.h"
void import_student_from_csv()
{
	ifstream in;
	ifstream inacc;//in as input for student list, inacc as input for creating student account
	ofstream out;
	ofstream outacc;//out as output for student list, outacc as output for creating student account
	string choice;
	cout << "Please type in the name of the class you wish to import:" << endl;
	getline(cin, choice);
	string classname;
	classname = choice;
	nodeStudent* pHead = nullptr;
	nodeStudent* cur = pHead;
	in.open(choice + "-Student.csv");
	if (!in) cout << "There is an error trying to open " << classname << "-Student.csv" << endl;
	else
	{
		int count = 0;
		for (int i = 0; i < 4; ++i)
		{
			in.ignore(1000, ',');
		}
		nodeStudent* cur = pHead;
		while (!in.eof())
		{
			if (pHead == nullptr)//input 1st node
			{
				pHead = new nodeStudent;
				in.ignore(100, '\n');
				getline(in, pHead->student.general.ID, ',');
				getline(in, pHead->student.general.fullname,',');
				in >> pHead->student.general.sex;
				in.ignore(10, ',');
				pHead->student.general.position = 2;
				in >> pHead->student.general.DoB.year;
				in.ignore(10, '-');
				in >> pHead->student.general.DoB.month;
				in.ignore(10, '-');
				in >> pHead->student.general.DoB.day;
				pHead->student.class_=classname;
				pHead->student.status = 1;
				count++;
				cur = pHead;
				pHead->next = nullptr;
				pHead->prev = nullptr;
			}

			else {//input other nodes
				cur->next = new nodeStudent;
				nodeStudent* temp = cur;
				cur = cur->next;
				cur->prev = temp;
				in.ignore(100, '\n');
				getline(in, cur->student.general.ID, ',');
				getline(in, cur->student.general.fullname,',');
				in >> cur->student.general.sex;
				in.ignore(10, ',');
				cur->student.general.position = 2;
				in >> cur->student.general.DoB.year;
				in.ignore(10, '-');
				in >> cur->student.general.DoB.month;
				in.ignore(10, '-');
				in >> cur->student.general.DoB.day;
				in.ignore(100, ',');
				cur->student.class_=classname;
				cur->student.status = 1;
				count++;
				cur->next = nullptr;
			}
		}
		in.close();
		outacc.open("data/account.gulu", std::fstream::app);
		cur = pHead;
		nodeAccount* pHeadaccount = nullptr;
		nodeAccount* curacc = pHeadaccount;
		while (cur != nullptr)
		{
			if (pHeadaccount == nullptr)
			{
				pHeadaccount = new nodeAccount;
				pHeadaccount->data.userID = cur->student.general.ID;
				string pass = to_string(cur->student.general.DoB.year);
				if (cur->student.general.DoB.month < 10) pass.append("0");
				pass.append(to_string(cur->student.general.DoB.month));
				if (cur->student.general.DoB.day < 10) pass.append("0");
				pass.append(to_string(cur->student.general.DoB.day));
				pHeadaccount->data.password = pass;
				outacc << pHeadaccount->data.userID << endl;
				outacc << pHeadaccount->data.password << endl << endl;
				pHeadaccount->prev = nullptr;
				pHeadaccount->next = nullptr;
				curacc = pHeadaccount;
				cur = cur->next;
			}
			else {
				curacc->next = new nodeAccount;
				nodeAccount* tempacc = curacc;
				curacc = curacc->next;
				curacc->data.userID = cur->student.general.ID;
				string pass = to_string(cur->student.general.DoB.year);
				if (cur->student.general.DoB.month < 10) pass.append("0");
				pass.append(to_string(cur->student.general.DoB.month));
				if (cur->student.general.DoB.day < 10) pass.append("0");
				pass.append(to_string(cur->student.general.DoB.day));
				curacc->data.password = pass;
				outacc << curacc->data.userID << endl;
				outacc << curacc->data.password << endl << endl;
				curacc->prev = tempacc;
				cur = cur->next;
				curacc->next = nullptr;
				;
			}
		}
		inacc.close();
		string destination = "data/class/" + classname + "/";
		const char* cstr = destination.c_str();
		_mkdir(cstr);
		out.open("data/class/" + classname + "/student.gulu");
		if (out.is_open())
		{
			int n = 0;
			cur = pHead;
			while (cur != nullptr)
			{
				cur = cur->next;
				n++;
			}
			out << n << endl << endl;//print the number of students in the gulu file
			cur = pHead;//reset current pointer to the first student
			while (cur != nullptr)
			{
				out << cur->student.general.ID << endl;
				out << cur->student.general.fullname << endl;
				out << cur->student.general.DoB.year << " " << cur->student.general.DoB.month << " " << cur->student.general.DoB.day << endl;
				out << cur->student.general.sex << endl;
				out << cur->student.status << endl << endl;
				cur = cur->next;
			}
			out.close();
		}
		else cout << "The file cannot be created." << endl;//end of creating folder and write to classname-Student.gulu
		out.open("data/student.gulu", std::fstream::app);
		if (!out) {
			cout << "File student.gulu cannot be opened." << endl;
		}
		else
		{
			cur = pHead;
			while (cur != nullptr)
			{
				out << cur->student.general.ID << endl;
				out << classname << endl << endl;
				cur = cur->next;
			}
			out.close();
		}

		//begin to delete all nodes from student account node
		curacc = pHeadaccount;
		while (curacc != nullptr)
		{
			nodeAccount* temp = curacc;
			curacc = curacc->next;
			delete temp;
		}
		delete curacc;
		//end of delete all nodes from student account node

		//begin to delete all nodes from student node 
		cur = pHead;
		while (curacc != nullptr)
		{
			nodeStudent* temp = cur;
			cur = cur->next;
			delete temp;
		}
		delete curacc;
	}
}
void add_a_student(){
	string classname;
	cout << "Please type in the class of the student you want to add:" << endl;
	getline(cin, classname);
	ofstream out;
	out.open("data/class/" + classname + "/student.gulu", std::fstream::app);
	nodeStudent* newstudent = nullptr;
	if (!out.is_open()) { cout << "Cannot open " << classname << "-Student.gulu" << endl; }
	else {
		newstudent = new nodeStudent;
		cout << "Please type in ID of new student:" << endl;
		getline(cin, newstudent->student.general.ID);
		cout << "Please type in the full name of new student:" << endl;
		getline(cin, newstudent->student.general.fullname);
		cout << "Please type in the gender of student with 0 for female, 1 for male:" << endl;
		cin >> newstudent->student.general.sex;
		cout << "Date of birth:YYYY MM DD:" << endl;
		cin >> newstudent->student.general.DoB.year;
		cin >> newstudent->student.general.DoB.month;
		cin >> newstudent->student.general.DoB.day;
		newstudent->student.status = 1;
		newstudent->student.class_ = classname;
		newstudent->student.general.position = 2;

		out << newstudent->student.general.ID << endl;
		out << newstudent->student.general.fullname << endl;
		out << newstudent->student.general.DoB.year << " " << newstudent->student.general.DoB.month << " " << newstudent->student.general.DoB.day << endl;
		out << newstudent->student.general.sex << endl;
		out << 1 << endl << endl;
		out.close();
	}
	if (newstudent == nullptr) return;
	else {
		ofstream out;
		out.open("data/student.gulu", std::fstream::app);
		if (!out) cout << "The file student.gulu containing list of all students cannot be opened" << endl;
		else {
			out << newstudent->student.general.ID << endl;
			out << classname << endl << endl;
			out.close();
		}
		out.open("data/account.gulu", std::fstream::app);
		if (!out) cout << "The account.gulu file cannot be opened" << endl;
		else
		{
			out << newstudent->student.general.ID << endl;
			string pass = to_string(newstudent->student.general.DoB.year);
			if (newstudent->student.general.DoB.month < 10) pass.append("0");
			pass.append(to_string(newstudent->student.general.DoB.month));
			if (newstudent->student.general.DoB.day < 10) pass.append("0");
			pass.append(to_string(newstudent->student.general.DoB.day));
			out << pass << endl << endl;
		}
	}
}
bool edit_a_student(){
    ifstream fi;
        ofstream fo;
        
        string tmp_Class;
        cout <<"Enter the student's class :";
        getline(cin,tmp_Class,'\n');
        nodeStudent * _student=nullptr;
        int numberStudent=0;
        read_a_class(fi,_student,numberStudent,tmp_Class);
        string tmp_ID;
        cout <<"The ID of the student you want to edit : ";
        getline(cin,tmp_ID,'\n');
        
        nodeStudent *cur= _student;
        for (int i=0;i<numberStudent;++i){
            if (cur->student.general.ID == tmp_ID) break;
            cur=cur->next;
        }
        if (cur==nullptr){
            cout <<"This student is not exist in this class !!! "
            <<"Please choose again"<<endl;
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
                cout <<"Edit successfully ! "<<endl;
            }
        }
        fi.close();
        rewrite_a_class(fo,_student,numberStudent,tmp_Class);
        return true;
    }


bool remove_a_student(){
    ifstream fi;
        ofstream fo;
        
        string tmp_Class;
        cout <<"Enter the student's class :";
        getline(cin,tmp_Class,'\n');
        int i=0;
        nodeStudent * _student=nullptr;
        int numberStudent=0;
        read_a_class(fi,_student,numberStudent,tmp_Class);
        string tmp_ID;
        cout <<"The ID of the student you want to remove : ";
        getline(cin,tmp_ID,'\n');
        nodeStudent *cur= _student;
        for (i=0;i<numberStudent;++i){
            if (cur->student.general.ID == tmp_ID) break;
            cur=cur->next;
        }
        if (cur==nullptr){
            cout <<"This student is not exist in this class !!! "
            <<"Please choose again"<<endl;
            remove_a_student();
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
            cout <<"Remove successfully ! "<<endl;
        }
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

void move_a_student_from_classA_to_classB(string codeA, string codeB, string Student_id)
{
    //Editing the file student.gulu in data
    ifstream ifs;
    ifs.open("data/student.gulu");
    if(!ifs.is_open())
    {
        cout << "Cannot open file\n";
        return;
    }
    int x; ifs>>x;
    bool flag = false;
    while(x--)
    {
        string sid, cc;
        ifs>>sid>>cc;
        if(sid==Student_id and cc==codeB)
        {
            cout << "This student has already been in class " << codeB << '\n';
            ifs.close();
            return;
        }
        if(sid==Student_id and cc==codeA) flag = true;
    }
    if(!flag)
    {
        cout << "This student is not in class A\n";
        ifs.close();
        return;
    }
    ifs.close();
    ifs.open("data/student.gulu");
    ofstream ofs;
    ofs.open("tmp.gulu");
    int cnt_block; ifs>>cnt_block;
    ofs<<cnt_block<<"\n\n";
    while(cnt_block--)
    {
        string sid, cc;
        ifs>>sid>>cc;
        if(sid!=Student_id or codeA!=cc)
        {
            ofs<<sid<<'\n'<<cc<<"\n\n";
        }
        else
        {
            ofs<<sid<<'\n'<<codeB<<"\n\n";
        }
    }
    ofs.close();
    ifs.close();
    remove("data/student.gulu");
    rename("tmp.gulu", "data/student.gulu");
    //Now editing the student list in classA - delete the student from this class
    string link = "data/class/"+codeA+"/student.gulu";

    ifs.open(link.c_str());
    if(!ifs.is_open())
    {
        cout << "Cannot open file\n";
        cout << 2 <<'\n';
        return;
    }
    ofs.open("tmp.gulu");
    string cnt;
    ifs>>cnt_block;
    ofs<<cnt_block-1<<'\n'<<'\n';
    ifs.ignore(1);
    string info_block;
    while(cnt_block--)
    {
        ifs.ignore(1);
        string sid, name, dob, sex, status;
        getline(ifs, sid, '\n');
        getline(ifs, name, '\n');
        getline(ifs, dob, '\n');
        getline(ifs, sex, '\n');
        getline(ifs, status, '\n');
        if(sid!=Student_id)
        {
            ofs<<sid<<'\n'<<name<<'\n'<<dob<<'\n'<<sex<<'\n'<<status<<"\n\n";        }
        else
        {
            info_block =sid+'\n'+name+'\n'+dob+'\n'+sex+'\n'+status+"\n\n";
        }
    }

    ifs.close();
    ofs.close();
    remove(link.c_str());
    rename("tmp.gulu", link.c_str());

    //Now move to class B and add the student to the student list of class B
    link = "data/class/"+codeB+"/student.gulu";
    ifs.open(link);
    if(!ifs.is_open())
    {
        cout << "Cannot open file\n";
        cout << 3 << '\n';
        return;
    }
    ofs.open("tmp.gulu");
    ifs>>cnt_block;
    ofs<<cnt_block+1<<'\n'<<'\n';
    ifs.ignore(1);
    while(cnt_block--)
    {
        ifs.ignore(1);
        string sid, name, dob, sex, status;
        getline(ifs, sid, '\n');
        getline(ifs, name, '\n');
        getline(ifs, dob, '\n');
        getline(ifs, sex, '\n');
        getline(ifs, status, '\n');
        ofs<<sid<<'\n'<<name<<'\n'<<dob<<'\n'<<sex<<'\n'<<status<<"\n\n";
    }
    ofs<< info_block;
    ifs.close();
    ofs.close();
    remove(link.c_str());
    rename("tmp.gulu", link.c_str());
}
