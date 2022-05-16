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
	Course* course;
};

struct Student	// tao them student de doc file csv
{
	string stt;
	string id;
	string name;
	string DoB;
	string lop;
	string midterm;
	string final;
	string total;
};

void loadfileLec(ifstream& f, int& n, Lecture*& lec)
{
	f >> n;
	lec = new Lecture[n];
	f.ignore(1);
	for (int i = 0; i < n; i++)
	{
		getline(f, lec[i].username);
		//getline(f, lec[i].username);       // doc them 1 lan getline o day vi truoc do doc vao con so f >> n

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
	}
	ifs.close();
}

void showCoursesLec(string username, string password, Lecture* lec, int n)
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

void showOptionClass(string username, string password, Lecture* lec, int n)
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

/*void readFileCSV(ifstream& f, Student *& a,int &n)
{
	f.open("C:/Users/ASUS/Desktop/CSC1001_Nhapmonlaptrinh_19CLC3.csv");
	if (!f.is_open())
	{
		cout << "can not open file to read score board";
	}
	else
	{
		f >> n;
		a = new Student[n + 1];
		f.ignore(1);						// doc bo ki tu /n de co the doc dung dong tu stt tro xuong
		for (int i = 0; i < n + 1; i++)
		{
			getline(f, a[i].stt, ',');
			getline(f, a[i].id, ',');
			getline(f, a[i].name, ',');
			getline(f, a[i].DoB, ',');
			getline(f, a[i].lop, ',');
			getline(f, a[i].midterm, ',');
			getline(f, a[i].final, ',');
			getline(f, a[i].total, '\n');
		}
	}
}*/


void readFileCSV(ifstream& ifs, char inputPath[101], Student*& a, int &numberStu)
{
	ifs.open(inputPath);
	if (!ifs.is_open())
	{
		cout << "can not open file to read";
	}
	else
	{
		ifs >> numberStu;
		a = new Student[numberStu + 1];
		ifs.ignore(1);						// doc bo ki tu /n de co the doc dung dong tu stt tro xuong
		for (int i = 0; i < numberStu + 1; i++)
		{
			getline(ifs, a[i].stt, ',');
			getline(ifs, a[i].id, ',');
			getline(ifs, a[i].name, ',');
			getline(ifs, a[i].DoB, ',');
			getline(ifs, a[i].lop, ',');
			getline(ifs, a[i].midterm, ',');
			getline(ifs, a[i].final, ',');
			getline(ifs, a[i].total, '\n');
		}
	}
}

void readFileScoreCSV(string username, string password,Student *&a, Lecture* lec, int n,int &numberStu)
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
				strcat_s(inputPath, 101, ".csv");

				readFileCSV(ifs, inputPath, a,numberStu);
			}
		}
	}

}


void importScore(Student*& a, int numberStu)
{
	int midterm, final, total;
	int num =0;
	string score;
	string name, idStudent;
	cout << "Enter name of student: ";
	cin.ignore(1);							// do o ham main truoc do dung switch case nhap vao number nen phai ignore(1)
	getline(cin, name);
	cout << "Enter id of student: ";
	getline(cin, idStudent);
	
	for (int i = 1; i < numberStu + 1; i++)
	{
		if (a[i].id == idStudent && a[i].name == name)
		{
			cout << "1. Midterm" << endl;
			cout << "2. Final" << endl;
			cout << "3. Total" << endl;
			cout << "4. Exit" << endl;
			do
			{
				cout << "enter your choice: ";
				cin >> num;
				if (num == 1)
				{
					cout << "enter new score: ";
					cin >> score;
					a[i].midterm = score;
					float(midterm) = stoi(a[i].midterm);
					float(final) = stoi(a[i].final);
					float(total) = (midterm + final) / 2;
					
					a[i].total = to_string(total);
					cout << "total: " << total << endl;
					cout << "change score successfully!" << endl;
				}
				else if (num == 2)
				{
					cout << "enter new score: ";
					cin >> score;
					a[i].final = score;
					float(midterm) = stoi(a[i].midterm);	// dung stoi chuyen string ve int va ep kieu ve float de ra so thap phan
					float(final) = stoi(a[i].final);
					float(total) = (midterm + final) / 2;

					a[i].total = to_string(total);						// ham to_string chuyen so float thanh string
					cout << "change score successfully!" << endl;
				}
				else if (num == 3)
				{
					cout << "enter new score: ";
					cin >> score;
					a[i].total = score;
					float(midterm) = stoi(a[i].midterm);	// dung stoi chuyen string ve int va ep kieu ve float de ra so thap phan
					float(final) = stoi(a[i].final);
					float(total) = (midterm + final) / 2;

					a[i].total = to_string(total);
					cout << "change score successfully!" << endl;
				}
			} while (num != 4);
		}
		else
		{
			cout << "can not find the student" << endl;
		}
	}
}

void showFileCSV(Student* a, int numberStu)
{
	for (int i = 1; i < numberStu+1; i++)			// cho i chay tu 1 de doc dung dong ko lay tu 0
	{
		cout << a[i].stt << "-" << a[i].id << "-" << a[i].name << "-" << a[i].DoB;
		cout << "-" << a[i].lop << "-" << a[i].midterm << "-" << a[i].final << "-" << a[i].total;
		cout << endl;
		cout << endl;
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
	Lecture* lec=NULL;

	Student* a=NULL;
	int numberStu;

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
				case 7:
					readFileCourse(readLec, lec, n);
					readFileScoreCSV(username, password, a, lec, n, numberStu);
					showFileCSV(a, numberStu);
					importScore(a, n);
					showFileCSV(a, numberStu);
					break;
				case 8:
					readFileCourse(readLec, lec, n);
					readFileScoreCSV(username, password, a, lec, n, numberStu);
					showFileCSV(a, numberStu);
					importScore(a, n);
					showFileCSV(a, numberStu);
					break;
				case 9:
					readFileCourse(readLec, lec, n);
					readFileScoreCSV(username,password, a,lec, n,numberStu);
					showFileCSV(a, numberStu);
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

	delete[]lec;
	delete[]a;

	return 0;
}