#include "Header.h"

int main() {
	Student* student;
	Staff* staff;
	Lecturer* lecturer;
	int number_of_student, number_of_staff, number_of_lecturer, option1;
	ifstream fin;
	ofstream fout;
	string account, password;
	readStudent(fin, student, number_of_student);
	readStaff(fin, staff, number_of_staff);
	readLecturer(fin, lecturer, number_of_lecturer);
	cout << "\t\t\t\t WELCOME TO STUDENT MANAGEMENT SYSTEM" << endl;
	showMenu();
	cout << "Choose your option (1 or 2): ";
	cin >> option1;
	while (option1 != 2) {
		cout << "Enter your account: ";
		cin >> account;
		cout << "Enter your password: ";
		cin >> password;
		while (!login(account, password, student, number_of_student, staff, number_of_staff, lecturer, number_of_lecturer)) {
			cout << "Wrong acount or password" << endl;
			cout << "Enter your account: ";
			cin >> account;
			cout << "Enter your password: ";
			cin >> password;
		}
		Student s = whoIsLogin(student, number_of_student, account, password);
		showMenuStudent();
		int option2;
		cout << "Choose your option (1-7): ";
		cin >> option2;
		while (option2 != 7) {
			if (option2 == 1)
				viewProfile(s);
			else if (option2 == 2) {
				changePassword(s, student, number_of_student);
				writeStudent(fout, student, number_of_student);
			}
			cout << "Choose your option (1-7): ";
			cin >> option2;
		}
		logout();
		showMenu();
		cout << "Choose your option (1 or 2): ";
		cin >> option1;
	}
	return 0;
}