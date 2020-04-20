#include "function.h"

int main() {
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||\n";
	cout << "||| Welcome to the Student Management System! |||\n";
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||\n";
	cout << endl;

	User* _user = new User;
	if (!login(*(_user))) return 0;

	if (_user->position < 2) {
		cout << "Welcome, ";
		if (_user->sex) cout << "Mr. ";
		else cout << "Ms. ";
	}
	else cout << "Hi, ";
	cout << _user->fullname << "!" << endl;
}