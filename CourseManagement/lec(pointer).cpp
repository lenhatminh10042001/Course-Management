#include<iostream>
#include<fstream>
#include<cstring>
#include <string>
using namespace std;

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
	cout << "1. View profile info" << endl;
	cout << "2. Change password" << endl;
	cout << "3. View list of courses in the current semester" << endl;
	cout << "4. View list of students of a course" << endl;
	cout << "5. View attendance list of a course" << endl;
	cout << "6 Edit an attendance" << endl;
	cout << "7 Import scoreboard of a course(midterm,final,lab,bonus) from a csv file" << endl;
	cout << "8 Edit grade of a student" << endl;
	cout << "9 View a scoreboard" << endl;
	cout << "10 Log out" << endl;
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
	ifs.open("C:/Users/ASUS/Desktop/MonhocLecturer.txt");
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
			cout << "enter your choice: ";
			cin >> num;
			if (num > lec[i].ncourse || num < 0)
			{
				cout << "enter again your choice";
			}
			else
			{
				ifstream ifs;
				char inputPath[101];
				char base[] = "C:/Users/ASUS/Desktop/";					// ong sua duong dan o day nha!
				strcpy_s(inputPath, strlen(base) + 1, base);
				strcat_s(inputPath, 101, lec[i].course[num - 1].mon.c_str());
				strcat_s(inputPath, 101, "_");
				strcat_s(inputPath, 101, lec[i].course[num - 1].idclass.c_str());
				strcat_s(inputPath, 101, ".txt");
				cout << inputPath << endl;
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




int main()
{
	ifstream readLec;
	ofstream fout;
	int n = 0;
	int num;
	string username;
	string password;
	Lecture *lec;

	readLec.open("C:/Users/ASUS/Desktop/Lecturer.txt");
	if (!readLec.is_open())
	{
		cout << "can not open file Lecture to read";
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
					cout << "you have been logout from the system" << endl;
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