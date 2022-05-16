#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <fstream>
#include <string> 
using namespace std;

struct Date {
	int day;
	int month;
	int year;
};

struct Student {
	string account;
	string password;
	string name;
	Date dob;
	string class1;
	int gender;
};

struct Staff {
	string account;
	string password;
	string name;
	int gender;
};

struct Lecturer {
	string account;
	string password;
	string name;
	int gender;
};

void showMenu();
void readStudent(ifstream& fin, Student*& student, int& number_of_student);
void readStaff(ifstream& fin, Staff*& staff, int& number_of_staff);
void readLecturer(ifstream& fin, Lecturer*& lecturer, int& number_of_lecturer);
bool login(string account, string password, Student* student, int number_of_student, Staff* staff, int number_of_staff, Lecturer* lecturer, int number_of_lecturer);
void showMenuStudent();
Student whoIsLogin(Student* student, int number_of_student, string account,string password);
void viewProfile(Student s);
void changePassword(Student s, Student*& student, int number_of_student);
void logout();
void writeStudent(ofstream& fout, Student* student, int number_of_student);

#endif 

