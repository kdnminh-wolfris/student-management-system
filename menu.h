#ifndef MENU
#define MENU

#include "datatype.h"
#include "admin.h"
#include "staff_class.h"

void menu(User& user, Config& config);
int menuFunction(int start, int user_position);
void optionFunction(int option, int user_position);

#endif