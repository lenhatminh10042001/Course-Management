#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
using namespace std;

struct Lecture
{
	string username;
	string password;
	string fullname;
	string degree;
	string sex;
};

void loadLec(ifstream& f, Lecture& lec)
{
	getline(f, lec.username);
	getline(f, lec.username);       // doc them 1 lan getline o day vi truoc do doc vao con so f >> n

	getline(f, lec.password);
	getline(f, lec.fullname);
	getline(f, lec.degree);
	getline(f, lec.sex);

}


void loadfileLec(ifstream& f, int& n, Lecture lec[])
{
	f >> n;
	for (int i = 0; i < n; i++)
	{
		loadLec(f, lec[i]);
	}
}

bool checkUserPass(string user, string pass, int n, Lecture lec[])
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


void callFullName(string user, string pass, int n, Lecture lec[])
{
	for (int i = 0; i < n; i++)
	{
		if (lec[i].username == user && lec[i].password == pass)
		{
			cout << lec[i].degree << "  " << lec[i].fullname << endl;
		}
	}
}


void viewProfile(string user, string pass, int n, Lecture lec[])
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

void changePass(ifstream& f, string user, string& pass, int n, Lecture lec[])
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
		f.open("C:/Users/ASUS/Desktop/Lecturer.txt");
		f >> n;
		for (int i = 0; i < n; i++)
		{
			loadfileLec(f, n, lec);
			if (lec[i].password == pass)
			{
				pass = newpass1;
				lec[i].password = pass;
			}
		}
		f.close();
		cout << "change password succesfully" << endl;
	}
	else
	{
		cout << "can not change password" << endl;
	}
}


void writeLecture(ofstream& f, Lecture lec[], int number_lecture)
{
	cout << lec[0].password << endl;
	f.open("C:/Users/ASUS/Desktop/Lecturer.txt");
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




int main()
{
	ifstream readLec;
	ofstream fout;
	int n = 0;
	int num;
	string username;
	string password;
	Lecture lec[100];

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
					cout << lec[0].password << endl;
					writeLecture(fout, lec, n);
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