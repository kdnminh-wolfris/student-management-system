#ifndef MENU
#define MENU

#include "datatype.h"
#include "admin.h"
#include "staff-class.h"
#include "staff-course.h"

void menu(User& user, Config& config);
int menuFunction(int start, User& user);
void optionFunction(int option, User& user);

#endif