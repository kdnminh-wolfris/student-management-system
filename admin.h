#ifndef ADMIN
#define ADMIN

#include "datatype.h"

bool login(User& user, Config& config);
int verified(User& user, string& pw);
bool changePassword(User& user, Config& config);

#endif