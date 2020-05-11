#include "function.h"

void numtag(int num) {
	cout << "[";
	if (num < 10)
		cout << " ";
	cout << num << " ] ";
}

bool load_config(Config& config) {
	ifstream fi;
	fi.open("data/config.gulu");
	if (!fi.is_open()) {
		cout << "Error: Missing config.gulu file\n" << endl;
		return false;
	}

	fi >> config.login_status; fi.ignore(100, '\n');
	getline(fi, config.curID);
	fi >> config.curPosition;
	fi >> config.keep_login;
	fi >> config.max_enterpw_turn;

	fi.close();
	return true;
}

void update_config(Config& config) {
	ofstream fo;
	fo.open("data/config.gulu");

	fo << config.login_status << '\n';
	fo << config.curID << '\n';
	fo << config.curPosition << '\n';
	fo << config.keep_login << '\n';
	fo << config.max_enterpw_turn;

	fo.close();
}

bool load_account(int& numberAccount, nodeAccount*& listAccount) {
	ifstream fi;
	fi.open("data/account.gulu");
	if (!fi.is_open()) {
		cout << "Error: Missing account.gulu file\n" << endl;
		return false;
	}

	fi >> numberAccount;

	nodeAccount* cur;
	listAccount = cur = nullptr;

	fi.ignore(100, '\n');

	for (int i = 0; i < numberAccount; ++i) {
		if (i == 0)
			listAccount = cur = new nodeAccount,
			cur->next = nullptr;
		else
			cur->next = new nodeAccount,
			cur = cur->next,
			cur->next = nullptr;

		fi.ignore(100, '\n');
		getline(fi, cur->data.userID);
		getline(fi, cur->data.password);
		fi >> cur->data.position;
		fi.ignore(100, '\n');
	}

	fi.close();
	return true;
}

void update_account(int numberAccount, nodeAccount* listAccount) {
	ofstream fo;
	fo.open("data/account.gulu");

	fo << numberAccount << "\n";
	while (listAccount != nullptr) {
		fo << "\n" << listAccount->data.userID;
		fo << "\n" << listAccount->data.password;
		fo << "\n" << listAccount->data.position;
		fo << '\n';
		nodeAccount* tmp = listAccount;
		listAccount = listAccount->next;
		delete tmp;
	}

	fo.close();
}

int int_option(int numberChoice) {
	int ret;
	string tmp;

	while (true) {
		cout << "\nChoose an option to continue...: ";
		cout.flush();

		cin >> tmp;

		ret = 0;

		for (int i = int(tmp.length()) - 1; i >= 0; --i)
			if ('0' <= tmp[i] && tmp[i] <= '9') {
				ret = ret * 10 + (tmp[i] - 48);
			}
			else {
				ret = -1; break;
			}
		
		if (tmp.length() && 0 <= ret && ret < numberChoice)
			break;
		
		cout << "Invalid option! Please type again your option.\n" << endl;
	}

	cout << endl;

	return ret;
}

bool bool_option(string operation) {
	if (operation != "")
		cout << "Are you sure you want to " << operation << "?\n";
	cout << "[Y]ES          [N]O\n\n";

	string tmp;

	while (true) {
		cout << "Enter Y/N to continue... ";
		cout.flush();

		cin >> tmp;

		if (tmp == "Y" || tmp == "y" || tmp == "N" || tmp == "n")
			break;

		cout << "Invalid option! Please type again your option.\n" << endl;
	}

	cout << endl;

	return tmp[0] == 'Y' || tmp[0] == 'y';
}

bool get_info(User& user) {
	ifstream fi;
	switch (user.position) {
		case 0: {
			fi.open("data/academic_staff.gulu");
			if (!fi.is_open()) {
				cout << "Error: Missing academic_staff.gulu file\n" << endl;
				return false;
			}

			int numberStaff;
			fi >> numberStaff;
			fi.ignore(100, '\n');

			string tmpID = user.ID;

			while (numberStaff--) {
				fi.ignore(100, '\n');
				getline(fi, user.ID);
				getline(fi, user.fullname);

				fi >> user.DoB.year;
				fi >> user.DoB.month;
				fi >> user.DoB.day;

				fi >> user.sex;
				fi.ignore(100, '\n');

				if (tmpID == user.ID) {
					fi.close(); return true;
				}
			}

			fi.close();
			cout << "Error: Missing << " << user.ID << " in academic_staff.gulu\n" << endl;
			return false;
		}

		case 1: {
			fi.open("data/lecturer.gulu");
			if (!fi.is_open()) {
				cout << "Error: Missing lecturer.gulu file\n" << endl;
				return false;
			}

			int numberLecturer;
			fi >> numberLecturer;
			fi.ignore(100, '\n');

			while (numberLecturer--) {
				fi.ignore(100, '\n');

				string tmpID;
				getline(fi, tmpID);
				getline(fi, user.fullname);
				fi >> user.DoB.year >> user.DoB.month >> user.DoB.day;
				fi >> user.sex;
				fi.ignore(100, '\n');
				fi.ignore(100, '\n');

				if (tmpID == user.ID) {
					fi.close(); return true;
				}
			}

			fi.close();
			cout << "Error: Missing " << user.ID << " in lecturer.gulu\n" << endl;
			return false;
		}

		case 2: {
			fi.open("data/student.gulu");
			if (!fi.is_open()) {
				cout << "Error: Missing student.gulu file\n" << endl;
				return false;
			}

			int numberStudent;
			fi >> numberStudent;
			fi.ignore(100, '\n');

			string tmpID, tmpClassCode;
			bool found = false;

			while (numberStudent--) {
				fi.ignore(100, '\n');
				getline(fi, tmpID);
				getline(fi, tmpClassCode);
				if (tmpID == user.ID) {
					found = true;
				}
			}

			fi.close();
			if (!found) {
				cout << "Error: Missing this user in student.gulu\n" << endl;
				return false;
			}

			fi.open("data/class/" + tmpClassCode + "/student.gulu");
			if (!fi.is_open()) {
				cout << "Error: Missing " << tmpClassCode << "/student.gulu file\n" << endl;
				return false;
			}

			fi >> numberStudent;
			fi.ignore(100, '\n');

			tmpID = user.ID;

			while (numberStudent--) {
				fi.ignore(100, '\n');
				getline(fi, user.ID);
				getline(fi, user.fullname);

				fi >> user.DoB.year;
				fi >> user.DoB.month;
				fi >> user.DoB.day;

				fi >> user.sex;
				fi.ignore(100, '\n');
				fi.ignore(100, '\n');

				if (tmpID == user.ID) {
					fi.close(); return true;
				}
			}

			fi.close();
			cout << "Error: Missing this user in " << tmpClassCode << "/student.gulu\n" << endl;
			return false;
		}
	}

	cout << "Error: User infomation not found\n" << endl;

	fi.close();
	return false;
}

void month_in_text(int num) {
	switch (num) {
		case 1: {
			cout << "January";
			break;
		}
		case 2: {
			cout << "February";
			break;
		}
		case 3: {
			cout << "March";
			break;
		}
		case 4: {
			cout << "April";
			break;
		}
		case 5: {
			cout << "May";
			break;
		}
		case 6: {
			cout << "June";
			break;
		}
		case 7: {
			cout << "July";
			break;
		}
		case 8: {
			cout << "August";
			break;
		}
		case 9: {
			cout << "September";
			break;
		}
		case 10: {
			cout << "October";
			break;
		}
		case 11: {
			cout << "November";
			break;
		}
		case 12: {
			cout << "December";
			break;
		}
	}
}

bool valid_date(int year, int month, int day) {
	if (year % 4 == 0 && month == 2 && day == 29)
		return true;

	if (day < 1) return false;

	switch (month) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: {
			if (day <= 31) return true;
			else return false;
			break;
		}
		case 4:
		case 6:
		case 9:
		case 11: {
			if (day <= 30) return true;
			else return false;
			break;
		}
		case 2: {
			if (day <= 28) return true;
			else return false;
			break;
		}
		default: {
			return false;
		}
	}
}

bool loadStudent(Student& student) {
	ifstream fi;
	fi.open("data/student.gulu");
	if (!fi.is_open()) {
		cout << "Error: Missing student.gulu file\n" << endl;
		return false;
	}

	int numberStudent;
	fi >> numberStudent;
	fi.ignore(100, '\n');

	bool found = false;

	while (numberStudent--) {
		fi.ignore(100, '\n');

		string tmpID;
		getline(fi, tmpID);
		getline(fi, student.class_);

		if (tmpID == student.general.ID) {
			found = true; break;
		}
	}

	fi.close();
	if (!found) {
		cout << "Error: Missing " << student.general.ID << " in student.gulu\n" << endl;
		return false;
	}

	fi.open("data/class/" + student.class_ + "/student.gulu");
	if (!fi.is_open()) {
		cout << "Error: Missing " << student.class_ << "/student.gulu file\n" << endl;
		return false;
	}

	fi >> numberStudent;
	fi.ignore(100, '\n');

	while (numberStudent--) {
		fi.ignore(100, '\n');

		string tmpID;
		getline(fi, tmpID);

		fi.ignore(100, '\n');
		fi.ignore(100, '\n');
		fi.ignore(100, '\n');

		fi >> student.status;
		fi.ignore(100, '\n');

		if (tmpID == student.general.ID) {
			fi.close(); return true;
		}
	}

	cout << "Error: Missing " << student.general.ID << " in " << student.class_ << "/student.gulu\n" << endl;
	return false;
}

bool loadLecturer(Lecturer& lecturer) {
	ifstream fi;
	fi.open("data/lecturer.gulu");
	if (!fi.is_open()) {
		cout << "Error: Missing lecturer.gulu file\n" << endl;
		return false;
	}

	int numberLecturer;
	fi >> numberLecturer;
	fi.ignore(100, '\n');

	bool found = false;

	while (numberLecturer--) {
		fi.ignore(100, '\n');

		string tmpID;
		getline(fi, tmpID);
		getline(fi, lecturer.general.fullname);
		fi >> lecturer.general.DoB.year >> lecturer.general.DoB.month >> lecturer.general.DoB.day;
		fi >> lecturer.general.sex;
		fi.ignore(100, '\n');		
		getline(fi, lecturer.degree);

		if (tmpID == lecturer.general.ID) {
			found = true; break;
		}
	}

	fi.close();
	if (!found) {
		cout << "Error: Missing " << lecturer.general.ID << " in lecturer.gulu\n" << endl;
		return false;
	}

	return true;
}

/*
bool read_a_class(ifstream &fi, nodeStudent *& _student, int &numberStudent, string tmp_class){
    fi.open("data/class/"+tmp_class+"/student.gulu");
    if (!fi) {
        cout <<"Error! The class doesn't exist !"<<endl;
        return false;
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
        fi>>cur->student.general.sex;
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
    return true;
}

void rewrite_a_class(ofstream &fo,nodeStudent *&_student,int &numberStudent,string tmp_class){
    fo.open("data/class/"+tmp_class+"/student.gulu");
    fo<<numberStudent<<endl<<endl;
    nodeStudent *cur=_student;
    for (int i=0;i<numberStudent;++i){
        fo<<cur->student.general.ID<<endl
        <<cur->student.general.fullname<<endl
        <<cur->student.general.DoB.year<<" "<<cur->student.general.DoB.month<<                      " "<<cur->student.general.DoB.day<<endl
        <<cur->student.general.sex<<endl
        <<cur->student.status<<endl<<endl;
        cur=cur->next;
    }
    fo.close();
}
*/
bool input_date(Date &date){
    cout <<"YYYY: ";
    cin>>date.year;
    if (date.year>2020 ||date.year<1) return false;
    cout <<"MM: ";
    cin>>date.month;
    if( date.month>12||date.month<1) return false;
    cout <<"DD: ";
    cin>>date.day;
    if ( date.day>31||date.day<1) return false;
    return true;
}
