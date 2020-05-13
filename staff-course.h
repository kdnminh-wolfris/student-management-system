#ifndef STAFF_COURSE
#define STAFF_COURSE

#include "datatype.h"

void import_course(); // from csv
void add_new_course(); // manually

void edit_course();
void remove_course();

void remove_student_from_course();
void add_student_to_course();

void view_course_list();
void view_student_list_of_course();
void view_attendance_list_of_course(); // check-in list

void view_lecturer_list();

#endif