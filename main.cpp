#include "menu.h"

int main() {
	system("cls"); // Clear screen

	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
	cout << "|||                                                   |||\n";
	cout << "|||             Student Management System             |||\n";
	cout << "|||                                                   |||\n";
	cout << "||||||||||||||||||||CS162|||Final|Project|||gulugulu|||||\n";
	cout << endl;

	Config* config = new Config;
	if (!config->load())
		return 0;

	User* user = new User;
	if (!login(*user, *config)) return 0;

	// greeting
	if (user->position < 2) {
		cout << "Welcome, ";
		if (user->sex) cout << "Mr. ";
		else cout << "Ms. ";
	}
	else cout << "Hi, ";
	cout << user->fullname << "!\n" << endl;

	menu(*user, *config);
	return main();
}