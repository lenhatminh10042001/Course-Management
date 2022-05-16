#include "Header.h"

void showMenu() {
	cout << "1.Login" << endl;
	cout << "2.Exit" << endl;
}

void readStudent(ifstream& fin, Student*& student, int& number_of_student) {
	fin.open("Student.txt");
	if (!fin.is_open()) {
		cout << "File does not exist.";
		return;
	}
	fin >> number_of_student;
	student = new Student[number_of_student];
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

bool login(string account, string password, Student* student, int number_of_student, Staff* staff, int number_of_staff, Lecturer* lecturer, int number_of_lecturer) {
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

Student whoIsLogin(Student* student, int number_of_student, string account, string password) {
	for (int i = 0; i < number_of_student; i++) {
		if (account == student[i].account && password == student[i].password)
			return student[i];
	}
}

void viewProfile(Student s) {
	cout << "Id: " << s.account << endl;
	cout << "Full name: " << s.name << endl;
	cout << "Date of birth: " << s.dob.year << "/" << s.dob.month << "/" << s.dob.day << endl;
	cout << "Class: " << s.class1 << endl;
	if (s.gender == 0)
		cout << "Gender: Male" << endl;
	else
		cout << "Gender: Female" << endl;
}

void writeStudent(ofstream& fout, Student* student, int number_of_student) {
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

void changePassword(Student s, Student*& student, int number_of_student) {
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


