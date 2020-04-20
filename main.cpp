#include "function.h"

int main() {
	cout << "|||||||||||||||||||||||||||||||||\n";
	cout << "||| Student Management System |||\n";
	cout << "|||||||||||||||||||||||||||||||||\n";
	cout << endl;

	User* user = new User;
	if (!login(*user)) return 0;

	// greeting
	if (user->position < 2) {
		cout << "Welcome, ";
		if (user->sex) cout << "Mr. ";
		else cout << "Ms. ";
	}
	else cout << "Hi, ";
	cout << user->fullname << "!\n" << endl;

	menu(*user);
	return main();
}