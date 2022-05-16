#include<iostream>
#include<fstream>
#include<cstring>
#include<ctime>
using namespace std;
//Cho biet vai tro truoc khi login
void School_role(int &role){
	cout<<"----------Which is your role----------"<<endl;
	cout<<"1.STUDENT"<<endl;
	cout<<"2.LECTURER"<<endl;
	cout<<"3.STAFF"<<endl<<endl;
	cout<<"--Enter your role: ";
	cin>>role;
}

//STUDENT
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

bool login(string account, string password, StudentLogIn* student, int number_of_student) {
	for (int i = 0; i < number_of_student; i++) {
		if (account == student[i].account && password == student[i].password) {
			cout << "Welcome " << student[i].name << " logged to system" << endl;
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
//LECTURER
struct Course
{
	string idclass;
	string mon;
};

struct Lecture
{
	string username;
	string password;
	string fullname;
	string degree;
	string sex;
	int ncourse;
	Course *course;
};
void loadfileLec(ifstream& f, int& n, Lecture*& lec)
{
	f >> n;
	lec = new Lecture[n];
	for (int i = 0; i < n; i++)
	{
		getline(f, lec[i].username);
		getline(f, lec[i].username);       // doc them 1 lan getline o day vi truoc do doc vao con so f >> n

		getline(f, lec[i].password);
		getline(f, lec[i].fullname);
		getline(f, lec[i].degree);
		getline(f, lec[i].sex);
	}
}

bool checkUserPass(string user, string pass, int n, Lecture* lec)
{

	for (int i = 0; i < n; i++)
	{

		if (lec[i].username == user && lec[i].password == pass)
		{
			return true;

		}
	}
	return false;
}





void callFullName(string user, string pass, int n, Lecture* lec)
{

	for (int i = 0; i < n; i++)
	{

		if (lec[i].username == user && lec[i].password == pass)
		{

			cout << lec[i].degree << "  " << lec[i].fullname << endl;
		}
	}
}





void viewProfile(string user, string pass, int n, Lecture* lec)
{
	for (int i = 0; i < n; i++)
	{
		if (lec[i].username == user && lec[i].password == pass)
		{
			cout << "Degree: " << lec[i].degree << endl;
			cout << "Full name: " << lec[i].fullname << endl;
			cout << "Sex: " << lec[i].sex << endl;
		}
	}
}



void showMenuLec()
{
	cout << " 1. View profile info" << endl;
	cout << " 2. Change password" << endl;
	cout << " 3. View list of courses in the current semester" << endl;
	cout << " 4. View list of students of a course" << endl;
	cout << " 5. View attendance list of a course" << endl;
	cout << " 6. Edit an attendance" << endl;
	cout << " 7. Import scoreboard of a course(midterm,final,lab,bonus) from a csv file" << endl;
	cout << " 8. Edit grade of a student" << endl;
	cout << " 9. View a scoreboard" << endl;
	cout << "10. Log out" << endl;
}



void changePass(ifstream& f, string user, string pass, int& n, Lecture*& lec)
{

	string newpass1, newpass2;
	cout << "Please enter your old password: ";
	getline(cin, pass);
	getline(cin, pass);
	cout << "Please enter your new password: ";
	getline(cin, newpass1);
	cout << "Please enter again your new password: ";
	getline(cin, newpass2);
	if (newpass1 == newpass2)
	{
		for (int i = 0; i < n; i++)
		{
			if (lec[i].password == pass)
			{
				lec[i].password.swap(newpass1);
			}
		}
		cout << "change password succesfully" << endl;
	}
	else
	{
		cout << "can not change password" << endl;
	}
}

void readFileCourse(ifstream& ifs, Lecture*& lec, int& n)
{
	ifs.open("MonhocLecturer.txt");
	ifs >> n;
	ifs.ignore(1);
	lec = new Lecture[n];
	for (int i = 0; i < n; i++)
	{
		getline(ifs, lec[i].username);
		getline(ifs, lec[i].password);
		ifs >> lec[i].ncourse;
		ifs.ignore(1);
		lec[i].course = new Course[lec[i].ncourse];
		for (int j = 0; j < lec[i].ncourse; j++) {
			getline(ifs, lec[i].course[j].idclass);
			getline(ifs, lec[i].course[j].mon);
		}
		ifs.ignore(1);
	}
	ifs.close();
}

void showCoursesLec(string username,string password,Lecture* lec, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (lec[i].username == username && lec[i].password == password)
		{
			for (int j = 0; j < lec[i].ncourse; j++)
			{
				cout << lec[i].course[j].idclass << endl;
				cout << lec[i].course[j].mon << endl;
			}
		}
	}
}

void writeLecture(ofstream& f, Lecture* lec, int number_lecture)
{
	f.open("Lecturer.txt");
	if (!f.is_open())
	{
		cout << "can not open file to write";
	}
	else
	{
		f << number_lecture << endl;
		for (int i = 0; i < number_lecture; i++)
		{
			f << lec[i].username << endl;
			f << lec[i].password << endl;
			f << lec[i].fullname << endl;
			f << lec[i].degree << endl;
			f << lec[i].sex << endl;
		}
		f.close();
	}
}

void showOptionClass(string username,string password,Lecture* lec, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (lec[i].username == username && lec[i].password == password)
		{
			for (int j = 0; j < lec[i].ncourse; j++)
			{
				cout << j + 1 << ". " << lec[i].course[j].idclass << "   " << lec[i].course[j].mon << endl;
			}
			int num;
			cout << "Enter your choice: ";
			cin >> num;
			if (num > lec[i].ncourse || num < 0)
			{
				cout << "Enter again your choice";
			}
			else
			{
				ifstream ifs;
				char inputPath[101];
				char base[] = "C:/Users/user/Desktop/";					// ong sua duong dan o day nha!
				strcpy(inputPath,base);
				strcat(inputPath,lec[i].course[num - 1].mon.c_str());
				strcat(inputPath, "_");
				strcat(inputPath,lec[i].course[num - 1].idclass.c_str());
				strcat(inputPath,".txt");
//				cout << inputPath << endl;
				ifs.open(inputPath);
				if (!ifs.is_open())
				{
					cout << "can not open file to read";
				}
				else
				{
					string line;
					while (!ifs.eof())
					{
						getline(ifs, line);
						cout << line << endl;
					}
					ifs.close();
				}
				
			}
		}
	}
	
}



//STAFF
struct Staff{
	string username;//ten dang nhap
	string pass_staff;//mat khau
	string fullname;//ho ten
	string age;//tuoi
};
struct View_Score_Course{
	string coursename;
	string no;
	string fullname;
	string lab;
	string theory;
	string total;
};
void Input_Staff(ifstream &filestaff, Staff*& staff, int & number_staff ){
	filestaff.open("C:\\Users\\user\\Desktop\\STAFF\\LOGIN\\Academic_Staff.txt");
	if(!filestaff.is_open()){
		cout<<"Can not open file";
	}
	else{
	filestaff>>number_staff;//so luong staff.
	staff= new Staff[number_staff];//cap phat bo nho cho staff.
	getline(filestaff,staff[0].username);//test ignored.
	for( int i =0; i<number_staff;i++){
		getline(filestaff,staff[i].username);
		getline(filestaff,staff[i].pass_staff);
		getline(filestaff,staff[i].fullname);
		getline(filestaff,staff[i].age);
	}
	filestaff.close();
	}
}
void Load_Staff(Staff *staff, int number_staff){// ham dung de kiem tra xem doc file dung hay sai.
	for( int i =0; i<number_staff;i++){
	cout<<staff[i].username<<endl;
	cout<<staff[i].pass_staff<<endl;
	cout<<staff[i].fullname<<endl;
	}
}
int Login_Staff(string &account_staff, string &pass, Staff *&staff, int &number_staff, int &staff_position){// kieu int de tranh truong hop "Access denied" ma chuong tirnh van tiep tuc chay.
	cout<<"------Enter your username: ";
	cin>>account_staff;
	cout<<"------Password: ";
	cin>>pass;
	int count_staff=0;
	for( int i =0; i<number_staff;i++){
		//dung string compare de so sanh 2 chuoi voi nhau, them duoi c_str() do strcmp bo tro cho char*.
		if(strcmp(account_staff.c_str(),staff[i].username.c_str())==0 && strcmp(pass.c_str(),staff[i].pass_staff.c_str())== 0){
			cout<<"---------------Access successfully.----------------"<<endl<<endl;
			cout<<"Hello Ms "<<staff[i].fullname<<endl;
			cout<<endl;
			staff_position=i;
			return 1;//dang nhap dung.
		}
		else{
			count_staff++;
			if (count_staff==number_staff){
				cout<<"------------Access denied.---------------------"<<endl;
				return 0; //dang nhap sai.
			}
		}
	}
}
void Option_menu(double option_staff){
	cout << "\t\t\t\t MENU" << endl;
	cout<<"1.1 Show menu."<<endl;
	cout<<"1.2 View your profile info."<<endl;
	cout<<"1.3 Change your password."<<endl;
	cout<<"1.4 Log out."<<endl<<endl<<endl;
	cout<<"---------------Enter your option:";
	cin>>option_staff;
	while(option_staff>1.4 || option_staff<1.1){
		cout<<"1.1 to 1.4, please"<<endl;
		cout<<"Enter your option:";
		cin>>option_staff;
	}
}
//show menu option 2.//course
void Course(){
	cout<<"\t\t\t\tCOURSE"<<endl;
	cout<<" 1.Create / update / delete / view academic years (2018-2019) "<<endl;
	cout<<" 2.From a semester, import courses such as CTT008, CTT010 from a csv file."<<endl;
	cout<<" 3.Manually add a new course."<<endl;
	cout<<" 4.Edit an existing course."<<endl;
	cout<<" 5.Remove a course."<<endl;
	cout<<" 6.Remove a specific student from a course."<<endl;
	cout<<" 7.Add a specific student to a course."<<endl;
	cout<<" 8.View list of courses in the current semester."<<endl;
	cout<<" 9.View list of students of a course."<<endl;
	cout<<"10.View attendance list of a course."<<endl;
	cout<<"11.Create / update / delete / view all lecturers."<<endl;
}
//show menu option 3.//scoreboard
void Score_course(ifstream &f1,View_Score_Course *&score_course,int &number_stud){
	cout<<"1.BAA0005"<<endl;
	cout<<"2.CSC0001"<<endl;
	cout<<"3.PHY0005"<<endl;
	cout<<"4.MTH0009"<<endl;
	
	int course;// lua chon khoa hoc.
	cout<<"Enter course: ";
	cin>>course;
	if(course==1){
		f1.open("C:\\Users\\user\\Desktop\\STAFF\\COURSES\\BAA0005.txt");
		if(!f1.is_open()){
			cout<<"Can not open file.";
		}
		//so luong hoc sinh trong khoa hoc do.
		f1>>number_stud;
		f1.ignore(1);
		score_course= new View_Score_Course [number_stud +1]; //cong 1 do cac tieu de.
		getline(f1,score_course[0].coursename);
		for(int i=0; i< number_stud+1 ;i++){
			getline(f1,score_course[i].no,'-');
			getline(f1,score_course[i].fullname,'-');
			getline(f1,score_course[i].lab,'-');
			getline(f1,score_course[i].theory,'-');
			getline(f1,score_course[i].total);
		}
		f1.close();
	}
	if(course==2){
		f1.open("C:\\Users\\user\\Desktop\\STAFF\\COURSES\\CSC0001.txt");
		if(!f1.is_open()){
			cout<<"Can not open file.";
		}
		//so luong hoc sinh trong khoa hoc do.
		f1>>number_stud;
		f1.ignore(1);
		score_course= new View_Score_Course [number_stud +1]; //cong 1 do cac tieu de.
		getline(f1,score_course[0].coursename);
		for(int i=0; i< number_stud +1 ;i++){
			getline(f1,score_course[i].no,'-');
			getline(f1,score_course[i].fullname,'-');
			getline(f1,score_course[i].lab,'-');
			getline(f1,score_course[i].theory,'-');
			getline(f1,score_course[i].total);
		}
		f1.close();
	}
	if(course==3){
		f1.open("C:\\Users\\user\\Desktop\\STAFF\\COURSES\\PHY0005.txt");
		if(!f1.is_open()){
			cout<<"Can not open file.";
		}
		//so luong hoc sinh trong khoa hoc do.
		f1>>number_stud;
		f1.ignore(1);
		score_course= new View_Score_Course [number_stud +1]; //cong 1 do cac tieu de.
		getline(f1,score_course[0].coursename);
		for(int i=0; i< number_stud +1 ;i++){
			getline(f1,score_course[i].no,'-');
			getline(f1,score_course[i].fullname,'-');
			getline(f1,score_course[i].lab,'-');
			getline(f1,score_course[i].theory,'-');
			getline(f1,score_course[i].total);
		}
		f1.close();
	}
	if(course==4){
		f1.open("C:\\Users\\user\\Desktop\\STAFF\\COURSES\\MTH0009.txt");
		if(!f1.is_open()){
			cout<<"Can not open file."<<endl;
		}
		//so luong hoc sinh trong khoa hoc do.
		f1>>number_stud;
		f1.ignore(1);
		score_course= new View_Score_Course [number_stud +1]; //cong 1 do cac tieu de.
		getline(f1,score_course[0].coursename);
		for(int i=0; i< number_stud+1 ;i++){
			getline(f1,score_course[i].no,'-');
			getline(f1,score_course[i].fullname,'-');
			getline(f1,score_course[i].lab,'-');
			getline(f1,score_course[i].theory,'-');
			getline(f1,score_course[i].total);
		}
		f1.close();
	}
	
}

void Show_menu_staff(int staff_choice){
	cout<<"1. Class"<<endl;
	cout<<"2. Course"<<endl;
	cout<<"3. Scoreboard"<<endl;
	cout<<"4. Attendace List"<<endl<<endl;
	cout<<"Enter your option: ";
	cin>>staff_choice;// lua chon cua staf trong 1.1 show menu
	if(staff_choice==2){
		Course();
		int choice2;
		cout<<endl<<" Enter your option: ";
		cin>>choice2;
		if(choice2==8){
			ifstream fcourse;
			fcourse.open("C:\\Users\\user\\Desktop\\STAFF\\LIST_OF_COURSES\\List_of_courses.txt");
			string courselist;
			getline(fcourse,courselist,'.');
			fcourse.close();
			cout<<"\tCOURSES LIST"<<endl;
			cout<<courselist<<endl;
		}
	}
	if(staff_choice==3){
		int choice3;// lua chon cua staff trong ScoreBoard.
		ifstream f1;
		View_Score_Course *score_course;
		int number_stud;
		cout<<"\t\t\t\tSCOREBOARD"<<endl;
		cout<<"1.View scoreboard of a course."<<endl;
		cout<<"2.EXPORT A SCOREBOARD TO A CSV FILE"<<endl<<endl;
		cout<<"--Enter your option: ";
		cin>>choice3;
		if(choice3==1){
			cout<<"Which course do you want to view score ? "<<endl;
			Score_course(f1,score_course,number_stud);
			//chay bang diem khoa hoc ra console.
			cout<<endl<<endl;
			cout<<score_course[0].coursename<<endl;
			for(int i =0; i<number_stud +1 ;i++){
				cout<<score_course[i].no<<" ";
				cout<<score_course[i].fullname<<" ";
				cout<<score_course[i].lab<<" ";
				cout<<score_course[i].theory<<" ";
				cout<<score_course[i].total<<endl;
			}
		}
		else if(choice3==2){
			cout<<"Which course do you want to export to a CSV file? "<<endl;
			Score_course(f1,score_course,number_stud);
			ofstream f2;
			string temp=score_course[0].coursename +".csv";// gan ten file muon export roif + them duoi csv.
			f2.open(temp.c_str());
			if(!f2.is_open()){
				cout<<"Can not open the file.";
			}
			for(int i =0; i<number_stud +1 ;i++){
				f2<<score_course[i].no<<",";
				f2<<score_course[i].fullname<<",";
				f2<<score_course[i].lab<<",";
				f2<<score_course[i].theory<<",";
				f2<<score_course[i].total<<endl;
			}
			f2.close();
			cout<<"Create CSV file succesfully."<<endl;
		}
		
	}		
}

void View_profile_staff(Staff *staff, int &staff_position){//xem thong tin ca nhan staff.
	cout<<"Here is your information: "<<endl;
	cout<<endl;
	cout<<"Fullname: "<<staff[staff_position].fullname<<endl;
	cout<<"Age: "<<staff[staff_position].age;
}
void Chang_password_staff(Staff *&staff,int staff_position){//doi mat khau cho staff.
	int pass_change_answer;
	string present_pass;
	string new_pass1;
	string new_pass2;
	cout<<staff[staff_position].fullname<<" are you sure you want to change your password? (1:Y)(0:N)"<<endl;
	cin>>pass_change_answer;
	if(pass_change_answer==1){
		cout<<"Enter your present password:"<<endl;
		cin>>present_pass;
		if(strcmp(present_pass.c_str(),staff[staff_position].pass_staff.c_str())==0){
			cout<<"Enter your new password:"<<endl;
			cin>>new_pass1;
			cout<<"Enter your new password again:";
			cin>>new_pass2;
			if(strcmp(new_pass1.c_str(),new_pass2.c_str())==0){
				new_pass2.swap(staff[staff_position].pass_staff);
				cout<<"So, your new pass word is: "<<staff[staff_position].pass_staff<<endl;
				cout<<"Completely changed your password, remember to use your new password to log in next time."<<endl<<endl;
			}
			else{
				cout<<"Error: New password is not the same";
			}
		}
		else{
			cout<<"Your present password is not correct."<<endl<<endl<<endl;
		}
	}
}
void writeStaff(ofstream &staffout,Staff *staff, int number_staff){
	staffout.open("C:\\Users\\user\\Desktop\\STAFF\\LOGIN\\Academic_Staff.txt");
	staffout<<number_staff<<endl;
	for(int i =0;i<number_staff;i++){
		staffout<<staff[i].username<<endl;
		staffout<<staff[i].pass_staff<<endl;
		staffout<<staff[i].fullname<<endl;
		staffout<<staff[i].age<<endl;
	}
	staffout.close();
	
}
void Logout(){
	cout<<"You has been log out.";
	return;
}
void Option_for_staff(double option_staff,Staff *staff, int &staff_position,int number_staff, int staff_choice){
	cout<<"There are 4 options for you to choose: "<<endl<<endl;
	cout<<"1.1 Show menu."<<endl;
	cout<<"1.2 View your profile info."<<endl;
	cout<<"1.3 Change your password."<<endl;
	cout<<"1.4 Log out."<<endl<<endl<<endl;
	cout<<"\t\tEnter yout option: ";
	cin>>option_staff;
	while(option_staff>1.4 || option_staff<1.1){
		cout<<"1.1 to 1.4, please"<<endl;
		cout<<"Enter your option: ";
		cin>>option_staff;
	}
	if(option_staff==1.1){
		Show_menu_staff(staff_choice);
	}
	else if(option_staff==1.2){
		View_profile_staff(staff,staff_position);
		Option_for_staff(option_staff,staff,staff_position,number_staff,staff_choice);
	}
	else if(option_staff==1.3){
		Chang_password_staff(staff,staff_position);
		ofstream staffout;
		writeStaff(staffout,staff,number_staff);
		Option_for_staff(option_staff,staff,staff_position,number_staff,staff_choice);
	}
	else if(option_staff ==1.4){
		Logout();
	} 
}

int main(){
	int role;
	School_role(role);
	if(role==1){
		StudentLogIn* student;
	int number_student, number_staff, number_lecturer, option1;
	ifstream fin;
	ofstream fout;
	string account, password;
	readStudentLogIn(fin, student, number_student);
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
		while (!login(account, password, student, number_student)) {
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
	return 0;
	}
	if(role==2){
	ifstream readLec;
	ofstream fout;
	int n = 0;
	int num;
	string username;
	string password;
	Lecture *lec;

	readLec.open("Lecturer.txt");
	if (!readLec.is_open())
	{
		cout << "Can not open file"<<endl;
	}

	else
	{
		loadfileLec(readLec, n, lec);
		readLec.close();
		cout << "1. LOGIN" << endl;
		cout << "2. LOGOUT" << endl;
		cout << "PLEASE ENTER YOUR CHOICE: ";
		cin >> num;

		if (num == 1)
		{
			cout << "Please enter your username: ";
			getline(cin, username);
			getline(cin, username);						// doc them 1 lan getline nua de lay dung username vi trc do la cin >> num

			cout << "Please enter your password: ";
			getline(cin, password);

			if (checkUserPass(username, password, n, lec) == 1)
			{
				cout << "Hello Mr/Ms ";
				callFullName(username, password, n, lec);
				cout << endl;

				showMenuLec();
				cout << endl;

				cout << "Please enter your choice: ";
				cin >> num;

				switch (num)
				{
				case 1:
					viewProfile(username, password, n, lec);
					break;

				case 2:
					changePass(readLec, username, password, n, lec);
					writeLecture(fout, lec, n);
					break;
				case 3:
					readFileCourse(readLec, lec, n);
					showCoursesLec(username, password, lec, n);
					break;
				case 4:
					readFileCourse(readLec, lec, n);
					showOptionClass(username, password, lec, n);
					break;
				case 10:
					cout << "You have been logout from the system" << endl;
					break;

				default:
					break;
				}
			}

			else
			{
				cout << "Please enter again your username or password" << endl;
			}
		}

		else
		{
			cout << "you have been log out the systems" << endl;
		}
	}
	
	return 0;
	}
	if(role==3){
		Staff *staff;
		int number_staff;
		ifstream filestaff;
		//Doc thong tin tu file Academic_Staff.
		Input_Staff(filestaff,staff,number_staff);
		//
		string account_staff,pass;// khoi tao chuoi ta khoan dang nhap, mat khau.
		cout << "\t\t\t\t WELCOME TO STAFF MANAGEMENT SYSTEM" << endl;
		int option_staff;//lua chon cua staff.
		int staff_position;// vi tri cua staff trong file.
		int staff_choice;//option trong show menu 1.1
		if(Login_Staff(account_staff,pass,staff,number_staff,staff_position)==1){// neu dang nhap thanh cong
		Option_for_staff(option_staff,staff,staff_position,number_staff,staff_choice);
		};
	}
	return 0;
}
