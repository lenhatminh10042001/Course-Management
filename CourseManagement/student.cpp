#ifndef _HEADER_H_
#define _HEADER_H_

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string> 
#include <ctime>

using namespace std;

struct Date {
	int day;
	int month;
	int year;
};

struct Time {
	int hour;
	int minute;
};
struct Day {
	Date date;
	Time start;
	Time end;
};

struct Score {
	float midterm;
	float final1;
	float bonus;
	float total;
};

struct StudentLogIn {
	string account;
	string password;
	string name;
	Date dob;
	string class1;
	int gender;
};

struct StudentInCourse {
	string account;
	string name;
	Date dob;
	string class1;
	int gender;
	Score score;
	Day day[10];
	int check_in[10];
	int status;
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

struct Schedule {
	string course_id;
	string name_course;
	string class1;
	string account_lecturer;
	string name_lecturer;
	int gender;
	Date start_week;
	Date end_week;
	int day_of_week;
	Time start_hour;
	Time end_hour;
	string room;
};

struct Class {
	char** class1;
};

void showMenu() {
	cout << "\t\t\t\t WELCOME TO STUDENT MANAGEMENT SYSTEM" << endl;
	cout << "1.Login" << endl;
	cout << "2.Exit" << endl;
}

void readStudentLogIn(ifstream& fin, StudentLogIn*& student, int& number_of_student) {
	fin.open("Student.txt");
	if (!fin.is_open()) {
		cout << "File does not exist.";
		return;
	}
	fin >> number_of_student;
	student = new StudentLogIn[number_of_student];
	fin.ignore(1);
	for (int i = 0; i < number_of_student; i++) {
		getline(fin, student[i].account);
		getline(fin, student[i].password);
		getline(fin, student[i].name);
		fin >> student[i].dob.year;
		fin >> student[i].dob.month;
		fin >> student[i].dob.day;
		fin.ignore(1);
		getline(fin, student[i].class1);
		fin >> student[i].gender;
		fin.ignore(2);
	}
	fin.close();
}

void readStaff(ifstream& fin, Staff*& staff, int& number_of_staff) {
	fin.open("Staff.txt");
	if (!fin.is_open()) {
		cout << "File does not exist.";
		return;
	}
	fin >> number_of_staff;
	staff = new Staff[number_of_staff];
	fin.ignore(1);
	for (int i = 0; i < number_of_staff; i++) {
		getline(fin, staff[i].account);
		getline(fin, staff[i].password);
		getline(fin, staff[i].name);
		fin >> staff[i].gender;
		fin.ignore(2);
	}
	fin.close();
}

void readLecturer(ifstream& fin, Lecturer*& lecturer, int& number_of_lecturer) {
	fin.open("Lecturer.txt");
	if (!fin.is_open()) {
		cout << "File does not exist";
		return;
	}
	fin >> number_of_lecturer;
	lecturer = new Lecturer[number_of_lecturer];
	fin.ignore(1);
	for (int i = 0; i < number_of_lecturer; i++) {
		getline(fin, lecturer[i].account);
		getline(fin, lecturer[i].password);
		getline(fin, lecturer[i].name);
		fin >> lecturer[i].gender;
		fin.ignore(2);
	}
	fin.close();
}

bool login(string account, string password, StudentLogIn* student, int number_of_student, Staff* staff, int number_of_staff, Lecturer* lecturer, int number_of_lecturer) {
	for (int i = 0; i < number_of_student; i++) {
		if (account == student[i].account && password == student[i].password) {
			cout << "Welcome " << student[i].name << " logged to system" << endl;
			return true;
		}
	}
	for (int i = 0; i < number_of_staff; i++) {
		if (account == staff[i].account && password == staff[i].password) {
			cout << "Welcome " << staff[i].name << " logged to system" << endl;
			return true;
		}
	}
	for (int i = 0; i < number_of_lecturer; i++) {
		if (account == lecturer[i].account && password == lecturer[i].password) {
			cout << "Welcome " << lecturer[i].name << " logged to system" << endl;
			return true;
		}
	}
	return false;
}

void showMenuStudent() {
	cout << "\t\t\t\t MENU" << endl;
	cout << "1.View profile" << endl;
	cout << "2.Change password" << endl;
	cout << "3.Check in" << endl;
	cout << "4.View check in result" << endl;
	cout << "5.View schedules" << endl;
	cout << "6.View scores of a course" << endl;
	cout << "7.Log out" << endl;
}

StudentLogIn whoIsLogin(StudentLogIn* student, int number_of_student, string account, string password) {
	for (int i = 0; i < number_of_student; i++) {
		if (account == student[i].account && password == student[i].password)
			return student[i];
	}
}

void viewProfile(StudentLogIn s) {
	cout << "Id: " << s.account << endl;
	cout << "Full name: " << s.name << endl;
	cout << "Date of birth: " << s.dob.year << "/" << s.dob.month << "/" << s.dob.day << endl;
	cout << "Class: " << s.class1 << endl;
	if (s.gender == 0)
		cout << "Gender: Male" << endl;
	else
		cout << "Gender: Female" << endl;
}

void changePassword(StudentLogIn s, StudentLogIn*& student, int number_of_student) {
	string old_password, new_password, new_password1;
	cout << "Enter your password: ";
	cin >> old_password;
	while (old_password != s.password) {
		cout << "Wrong password!!!" << endl;
		cout << "Enter your password again: ";
		cin >> old_password;
	}
	cout << "Enter new password: ";
	cin >> new_password;
	cout << "Enter new password again: ";
	cin >> new_password1;
	while (new_password != new_password1) {
		cout << "Wrong password" << endl;
		cout << "Enter new password again: ";
		cin >> new_password1;
	}
	s.password = new_password;
	for (int i = 0; i < number_of_student; i++) {
		if (s.account == student[i].account)
			student[i].password = s.password;
	}
	cout << "Your password has been changed successfully" << endl;
}

void logout() {
	cout << "You have been logged out system" << endl;
}

void writeStudent(ofstream& fout, StudentLogIn* student, int number_of_student) {
	fout.open("Student.txt");
	fout << number_of_student << endl;
	for (int i = 0; i < number_of_student; i++) {
		fout << student[i].account << endl;
		fout << student[i].password << endl;
		fout << student[i].name << endl;
		fout << student[i].dob.year << " " << student[i].dob.month << " " << student[i].dob.day << endl;
		fout << student[i].class1 << endl;
		fout << student[i].gender << endl << endl;
	}
}

void readClass(ifstream& fin, Class& class1, int& number_class) {
	fin.open("Class.txt");
	fin >> number_class;
	fin.ignore(1);
	class1.class1 = new char* [number_class];
	for (int i = 0; i < number_class; i++) {
		string temp;
		getline(fin, temp);
		class1.class1[i] = new char[strlen(temp.c_str()) + 1];
		strcpy(class1.class1[i], temp.c_str());
	}
	fin.close();
}

void readSchedule(Schedule*& schedule, ifstream& fin, int& number_of_course, char* class1) {
	char* filename;
	char s[] = "2019-2020-HK2-Schedule-";
	char u[] = ".txt";
	filename = new char[strlen(s) + strlen(class1) + strlen(u) + 1];
	strcpy(filename, s);
	strcat(filename, class1);
	strcat(filename, u);
	fin.open(filename);
	if (!fin.is_open()) {
		cout << "File does not exist";
		return;
	}
	fin >> number_of_course;
	schedule = new Schedule[number_of_course];
	fin.ignore(1);
	for (int i = 0; i < number_of_course; i++) {
		getline(fin, schedule[i].course_id);
		getline(fin, schedule[i].name_course);
		getline(fin, schedule[i].class1);
		getline(fin, schedule[i].account_lecturer);
		getline(fin, schedule[i].name_lecturer);
		fin >> schedule[i].gender;
		fin >> schedule[i].start_week.year;
		fin >> schedule[i].start_week.month;
		fin >> schedule[i].start_week.day;
		fin >> schedule[i].end_week.year;
		fin >> schedule[i].end_week.month;
		fin >> schedule[i].end_week.day;
		fin >> schedule[i].day_of_week;
		fin >> schedule[i].start_hour.hour;
		fin >> schedule[i].start_hour.minute;
		fin >> schedule[i].end_hour.hour;
		fin >> schedule[i].end_hour.minute;
		fin.ignore(1);
		getline(fin, schedule[i].room);
		fin.ignore(1);
	}
	delete[] filename;
	fin.close();
}

void readStudentOfCourse(ifstream& fin, StudentInCourse*& student, int& number_student_of_course, char* class1, string course_id) {
	char* filename;
	char s[] = "2019-2020-HK2-";
	char u[] = "-Student.txt";
	filename = new char[strlen(s) + strlen(u) + strlen(class1) + strlen(course_id.c_str()) + 2];
	strcpy(filename, s);
	strcat(filename, class1);
	strcat(filename, "-");
	strcat(filename, course_id.c_str());
	strcat(filename, u);
	fin.open(filename);
	if (!fin.is_open()) {
		cout << "File does not exist";
		return;
	}
	fin >> number_student_of_course;
	student = new StudentInCourse[number_student_of_course];
	fin.ignore(1);
	for (int i = 0; i < number_student_of_course; i++) {
		getline(fin, student[i].account);
		getline(fin, student[i].name);
		fin >> student[i].dob.year;
		fin >> student[i].dob.month;
		fin >> student[i].dob.day;
		fin.ignore(1);
		getline(fin, student[i].class1);
		fin >> student[i].gender;
		fin >> student[i].score.midterm;
		fin >> student[i].score.final1;
		fin >> student[i].score.bonus;
		fin >> student[i].score.total;
		for (int j = 0; j < 10; j++) {
			fin >> student[i].day[j].date.year;
			fin >> student[i].day[j].date.month;
			fin >> student[i].day[j].date.day;
			fin >> student[i].day[j].start.hour;
			fin >> student[i].day[j].start.minute;
			fin >> student[i].day[j].end.hour;
			fin >> student[i].day[j].end.minute;
			fin >> student[i].check_in[j];
		}
		fin >> student[i].status;
		fin.ignore(2);
	}
	delete[] filename;
	fin.close();
}

void viewSchedule(StudentLogIn s) {
	ifstream fin;
	Class class1;
	int number_class;
	readClass(fin, class1, number_class);
	for (int i = 0; i < number_class; i++) {
		Schedule* schedule;
		int number_course;
		readSchedule(schedule, fin, number_course, class1.class1[i]);
		for (int j = 0; j < number_course; j++) {
			StudentInCourse* student_course;
			int number_student_course;
			readStudentOfCourse(fin, student_course, number_student_course, class1.class1[i], schedule[j].course_id);
			for (int k = 0; k < number_student_course; k++) {
				if (s.name == student_course[k].name) {
					cout << schedule[j].course_id << endl;
					cout << schedule[j].name_course << endl;
					cout << schedule[j].class1 << endl;
					cout << schedule[j].account_lecturer << endl;
					cout << schedule[j].name_lecturer << endl;
					cout << schedule[j].gender << endl;
					cout << schedule[j].start_week.year << " " << schedule[j].start_week.month << " " << schedule[j].start_week.day << endl;
					cout << schedule[j].end_week.year << " " << schedule[j].end_week.month << " " << schedule[j].end_week.day << endl;
					cout << schedule[j].day_of_week << endl;
					cout << schedule[j].start_hour.hour << " " << schedule[j].start_hour.minute << endl;
					cout << schedule[j].end_hour.hour << " " << schedule[j].end_hour.minute << endl;
					cout << schedule[j].room << endl << endl;
				}
			}
			delete[] student_course;
		}
		delete[] schedule;
	}
	for (int i = 0; i < number_class; i++)
		delete[] class1.class1[i];
	delete class1.class1;
}

void viewScore(StudentLogIn s) {
	ifstream fin;
	Class class1;
	int number_class;
	cout << "Choose your course you want to view score: ";
	readClass(fin, class1, number_class);
	for (int i = 0; i < number_class; i++) {
		Schedule* schedule;
		int number_course;
		readSchedule(schedule, fin, number_course, class1.class1[i]);
		for (int j = 0; j < number_course; j++) {
			StudentInCourse* student_course;
			int number_student_course;
			readStudentOfCourse(fin, student_course, number_student_course, class1.class1[i], schedule[j].course_id);
			for (int k = 0; k < number_student_course; k++) {
				if (s.name == student_course[k].name) {
					cout << schedule[j].course_id << " ";
				}
			}
			delete[] student_course;
		}
		delete[] schedule;
	}
	for (int i = 0; i < number_class; i++)
		delete[] class1.class1[i];
	delete class1.class1;
	string course_id;
	cout << endl << "Enter course id: ";
	cin >> course_id;
	readClass(fin, class1, number_class);
	for (int i = 0; i < number_class; i++) {
		Schedule* schedule;
		int number_course;
		readSchedule(schedule, fin, number_course, class1.class1[i]);
		for (int j = 0; j < number_course; j++) {
			StudentInCourse* student_course;
			int number_student_course;
			readStudentOfCourse(fin, student_course, number_student_course, class1.class1[i], schedule[j].course_id);
			for (int k = 0; k < number_student_course; k++) {
				if (s.name == student_course[k].name && course_id == schedule[j].course_id) {
					cout << "Midterm: " << student_course[k].score.midterm << endl;
					cout << "Final: " << student_course[k].score.final1 << endl;
					cout << "Bonus: " << student_course[k].score.bonus << endl;
					cout << "Total: " << student_course[k].score.total << endl;
				}
			}
			delete[] student_course;
		}
		delete[] schedule;
	}
	for (int i = 0; i < number_class; i++)
		delete[] class1.class1[i];
	delete class1.class1;
}

void viewCheckIn(StudentLogIn s) {
	ifstream fin;
	Class class1;
	int number_class;
	cout << "Choose your course you want to view check in: ";
	readClass(fin, class1, number_class);
	for (int i = 0; i < number_class; i++) {
		Schedule* schedule;
		int number_course;
		readSchedule(schedule, fin, number_course, class1.class1[i]);
		for (int j = 0; j < number_course; j++) {
			StudentInCourse* student_course;
			int number_student_course;
			readStudentOfCourse(fin, student_course, number_student_course, class1.class1[i], schedule[j].course_id);
			for (int k = 0; k < number_student_course; k++) {
				if (s.name == student_course[k].name) {
					cout << schedule[j].course_id << " ";
				}
			}
			delete[] student_course;
		}
		delete[] schedule;
	}
	for (int i = 0; i < number_class; i++)
		delete[] class1.class1[i];
	delete class1.class1;
	string course_id;
	cout << endl << "Enter course id: ";
	cin >> course_id;
	readClass(fin, class1, number_class);
	for (int i = 0; i < number_class; i++) {
		Schedule* schedule;
		int number_course;
		readSchedule(schedule, fin, number_course, class1.class1[i]);
		for (int j = 0; j < number_course; j++) {
			StudentInCourse* student_course;
			int number_student_course;
			readStudentOfCourse(fin, student_course, number_student_course, class1.class1[i], schedule[j].course_id);
			for (int k = 0; k < number_student_course; k++) {
				if (s.name == student_course[k].name && course_id == schedule[j].course_id) {
					for (int t = 0; t < 10; t++) {
						cout << student_course[k].day[t].date.year << " " << student_course[k].day[t].date.month << " " << student_course[k].day[t].date.day << " " << student_course[k].day[t].start.hour << " " << student_course[k].day[t].start.minute << " " << student_course[k].day[t].end.hour << " " << student_course[k].day[t].end.minute << " " << student_course[k].check_in[t] << endl;
					}
				}
			}
			delete[] student_course;
		}
		delete[] schedule;
	}
	for (int i = 0; i < number_class; i++)
		delete[] class1.class1[i];
	delete class1.class1;
}

Day currentTime() {
	Day check_in;
	time_t now = time(0);
	tm* t = localtime(&now);
	check_in.date.year = 1900 + t->tm_year;
	check_in.date.month = 1 + t->tm_mon;
	check_in.date.day = t->tm_mday;
	check_in.start.hour = t->tm_hour;
	check_in.start.minute = t->tm_min;
	return check_in;
}

void writeCheckIn(ofstream& fout, StudentInCourse* student, int number_student_course, char* class1, string course_id) {
	char* filename;
	char s[] = "2019-2020-HK2-";
	char u[] = "-Student.txt";
	filename = new char[strlen(s) + strlen(u) + strlen(class1) + strlen(course_id.c_str()) + 2];
	strcpy(filename, s);
	strcat(filename, class1);
	strcat(filename, "-");
	strcat(filename, course_id.c_str());
	strcat(filename, u);
	fout.open(filename);
	fout << number_student_course << endl;
	for (int i = 0; i < number_student_course; i++) {
		fout << student[i].account << endl;
		fout << student[i].name << endl;
		fout << student[i].dob.year << " " << student[i].dob.month << " " << student[i].dob.day << endl;
		fout << student[i].class1 << endl;
		fout << student[i].gender << endl;
		fout << student[i].score.midterm << endl;
		fout << student[i].score.final1 << endl;
		fout << student[i].score.bonus << endl;
		fout << student[i].score.total << endl;
		for (int j = 0; j < 10; j++) {
			fout << student[i].day[j].date.year << " " << student[i].day[j].date.month << " " << student[i].day[j].date.day << " " << student[i].day[j].start.hour << " " << student[i].day[j].start.minute << " " << student[i].day[j].end.hour << " " << student[i].day[j].end.minute << " " << student[i].check_in[j] << endl;
		}
		fout << student[i].status << endl << endl;
	}
	delete[] filename;
	fout.close();
}

void checkIn(StudentLogIn s) {
	Day check_in = currentTime();
	ifstream fin;
	ofstream fout;
	Class class1;
	int number_class;
	readClass(fin, class1, number_class);
	for (int i = 0; i < number_class; i++) {
		Schedule* schedule;
		int number_course;
		readSchedule(schedule, fin, number_course, class1.class1[i]);
		for (int j = 0; j < number_course; j++) {
			StudentInCourse* student_course;
			int number_student_course;
			readStudentOfCourse(fin, student_course, number_student_course, class1.class1[i], schedule[j].course_id);
			for (int k = 0; k < number_student_course; k++) {
				if (s.name == student_course[k].name) {
					for (int t = 0; t < 10; t++) {
						if (student_course[k].day[t].date.year == check_in.date.year && student_course[k].day[t].date.month == check_in.date.month && student_course[k].day[t].date.day == check_in.date.day) {
							if (student_course[k].day[t].start.hour < check_in.start.hour && check_in.start.hour < student_course[k].day[t].end.hour) {
								student_course[k].check_in[t] = 1;
								writeCheckIn(fout, student_course, number_student_course, class1.class1[i], schedule[j].course_id);
								cout << "You have been checked in " << schedule[j].course_id << endl;
							}
							else if (student_course[k].day[t].start.hour == check_in.start.hour && student_course[k].day[t].start.minute <= check_in.start.minute) {
								student_course[k].check_in[t] = 1;
								writeCheckIn(fout, student_course, number_student_course, class1.class1[i], schedule[j].course_id);
								cout << "You have been checked in " << schedule[j].course_id << endl;
							}
							else if (student_course[k].day[t].end.hour == check_in.end.hour && student_course[k].day[t].end.minute >= check_in.end.minute) {
								student_course[k].check_in[t] = 1;
								writeCheckIn(fout, student_course, number_student_course, class1.class1[i], schedule[j].course_id);
								cout << "You have been checked in " << schedule[j].course_id << endl;
							}
						}
					}
				}
			}
			delete[] student_course;
		}
		delete[] schedule;
	}
	for (int i = 0; i < number_class; i++)
		delete[] class1.class1[i];
	delete class1.class1;
}

int main() {
	StudentLogIn* student;
	Staff* staff;
	Lecturer* lecturer;
	int number_student, number_staff, number_lecturer, option1;
	ifstream fin;
	ofstream fout;
	string account, password;
	readStudentLogIn(fin, student, number_student);
	readStaff(fin, staff, number_staff);
	readLecturer(fin, lecturer, number_lecturer);
	showMenu();
	cout << "Choose your option (1 or 2): ";
	cin >> option1;
	while (option1 < 1 || option1 > 2) {
		cout << "Enter 1 or 2" << endl;
		cout << "Choose your option (1 or 2): ";
		cin >> option1;
	}
	while (option1 != 2) {
		cout << "Enter your account: ";
		cin >> account;
		cout << "Enter your password: ";
		cin >> password;
		while (!login(account, password, student, number_student, staff, number_staff, lecturer, number_lecturer)) {
			cout << "Wrong acount or password" << endl;
			cout << "Enter your account: ";
			cin >> account;
			cout << "Enter your password: ";
			cin >> password;
		}
		StudentLogIn s = whoIsLogin(student, number_student, account, password);
		showMenuStudent();
		int option2;
		cout << "Choose your option (1-7): ";
		cin >> option2;
		while (option2 != 7) {
			if (option2 == 1)
				viewProfile(s);
			else if (option2 == 2) {
				changePassword(s, student, number_student);
				writeStudent(fout, student, number_student);
			}
			else if (option2 == 3)
				checkIn(s);
			else if (option2 == 4)
				viewCheckIn(s);
			else if (option2 == 5)
				viewSchedule(s);
			else if (option2 == 6)
				viewScore(s);
			else
				cout << "Enter from 1 to 7" << endl;
			cout << "Choose your option (1-7): ";
			cin >> option2;
		}
		logout();
		showMenu();
		cout << "Choose your option (1 or 2): ";
		cin >> option1;
	}
	delete[] student;
	delete[] staff;
	delete[] lecturer;
	return 0;
}
