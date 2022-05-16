#include<iostream>
#include<fstream>
#include<string>
using namespace std;
struct student
{
	string no;
	string id;
	string fullname;
	char* dob = new char[20];
	string Class;
	string status;
	string user;
	char *password=new char[20];
	
};
char* removeSpaces(char* str)
{
	int i = 0, j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return str;
}
void inPutClass(ifstream& fi, student& x)
{
	getline(fi, x.no, ',');
	getline(fi, x.id, ',');
	getline(fi, x.fullname, ',');
	fi.getline(x.dob, 20, ',');
	getline(fi, x.Class, ',');
	getline(fi, x.status);
}
void inPutStudent(ifstream& fi, student& x)
{
	getline(fi, x.id);
	fi.getline(x.password, 20);
	getline(fi, x.fullname);
	fi.getline(x.dob, 20);
	getline(fi, x.Class);
	getline(fi, x.status);
}
void readClass(ifstream& fi, string& file, int& number_studentClass, student*& list_studentClass)
{
	fi.open(file);
	if (!fi.is_open()) cout << "Can not open file !";
	fi >> number_studentClass;

	fi.ignore();
	list_studentClass = new student[number_studentClass +2];
	for (int i = 0; i <= number_studentClass; i++)
	{
		inPutClass(fi, list_studentClass[i]);
		
	}
	

}
void WriteToClass(ofstream& fo, student* list_student, int& number_student, string file)
{
	fo.open(file);
	if (!fo.is_open()) cout << "Can not open file ! ";

	fo << number_student << endl;
	for (int i = 0; i <= number_student; i++)
	{
		fo << list_student[i].no << "," << list_student[i].id << "," << list_student[i].fullname << "," << list_student[i].dob << "," << list_student[i].Class<<","<<list_student[i].status << endl;
	}
	fo.close();
}
void readStudent(ifstream& fi, string& file, int& n, student*& list_student)
{

	fi.open(file);
	if (!fi.is_open()) cout << "Can not open file !";

	else
	{
		fi >> n;
		fi.ignore();

		list_student = new student[n +1];
		for (int i = 0; i < n; i++)
		{
			inPutStudent(fi, list_student[i]);
		}
	}

}
void WriteToStudent(ofstream& fo, student* list_student, int& number_student, string file)
{
	fo.open(file);
	if (!fo.is_open()) cout << "Can not open file ";

	fo << number_student + 1 << endl;

	for (int i = 0; i <= number_student; i++)
	{
		fo << list_student[i].id << endl;
		fo << removeSpaces(list_student[i].password)<< endl;
		fo << list_student[i].fullname << endl;
		fo << list_student[i].dob << endl;
		fo << list_student[i].Class << endl;
		fo << list_student[i].status << endl;
	}

}
void option2()
{
	ifstream fi;
	string id, fullname, Class, gender, user;
	char dob[20];
	student* list_studentClass = NULL;
	int number_studentClass = 0;
	cout << "What class you want to add a student ? :";
	cin >> Class;
	string file = Class + ".txt";
	readClass(fi, file, number_studentClass, list_studentClass);
	number_studentClass = number_studentClass + 1;
	cout << "number_studentClass : " << number_studentClass << endl;
	string no = to_string(number_studentClass);
	cout << no << endl;
	cin.ignore();
	list_studentClass[number_studentClass].no = no;
	cout << list_studentClass[number_studentClass].no << endl;
	cout << "Enter id :";
	getline(cin, id);
	list_studentClass[number_studentClass].id = id;
	cout << "Enter fullname :";
	getline(cin, fullname);
	list_studentClass[number_studentClass].fullname = fullname;
	cout << "Enter dob :";
	cin.getline(dob, 20);
	cout << "Enter gender ";
	getline(cin, gender);
	strcpy_s(list_studentClass[number_studentClass].dob, 20, dob);
	list_studentClass[number_studentClass].Class = Class;
	list_studentClass[number_studentClass].status = gender;
	ofstream fo;
	WriteToClass(fo, list_studentClass, number_studentClass, file);
	fo.close();
	////////////////////////////////////////////
	student* list_student = NULL;
	string filestudent = "student.txt";
	int number_student = 0;
	ifstream fa;
	ofstream fb;
	readStudent(fa, filestudent, number_student, list_student);
	list_student[number_student].id = id;
	strcpy_s(list_student[number_student].password, 20, dob);
	strcpy_s(list_student[number_student].dob, 20, dob);
	list_student[number_student].fullname = fullname;
	list_student[number_student].Class = Class;
	list_student[number_student].status = gender;
	WriteToStudent(fb, list_student, number_student, filestudent);
}
void option1()
{
	cout << "Enter path CSV file :";
	string csvFile;
	cin >> csvFile;
	ifstream fi;
	int number_studentClass = 0;
	student* list_studentClass,*base;
	readClass(fi, csvFile, number_studentClass, list_studentClass);
	
	string fileClass = list_studentClass[1].Class + ".txt";
	fi.close();
	ofstream fo;
	WriteToClass(fo, list_studentClass, number_studentClass, fileClass);
	/////////////////////////////////
	student* list_student = NULL;
	string filestudent = "student.txt";
	int number_student = 0;
	ifstream fa;
	ofstream fb;
	ifstream ftest;
	readStudent(fa, filestudent, number_student, list_student);
	base = new student[number_student + number_studentClass];
	int j = 1;
	for (int i = 0; i < number_student + number_studentClass; i++)
	{
		if (i < number_student)
		{
			base[i].id = list_student[i].id;
			strcpy_s(base[i].password, 20, list_student[i].dob);
			base[i].fullname = list_student[i].fullname;
			strcpy_s(base[i].dob, 20, list_student[i].dob);
			base[i].Class = list_student[i].Class;
			base[i].status = list_student[i].status;
		}
		else
		{
			base[i].id = list_studentClass[j].id;
			strcpy_s(base[i].password, 20, list_studentClass[j].dob);
			base[i].fullname = list_studentClass[j].fullname;
			strcpy_s(base[i].dob, 20, list_studentClass[j].dob);
			base[i].Class = list_studentClass[j].Class;
			base[i].status = list_studentClass[j].status;
			j++;
		}
	}
	int temp = number_student + number_studentClass-1;
	WriteToStudent(fb, base,temp , filestudent);
}
void option6()
{
	cout << "View list of classes :";
	ifstream fi;
	fi.open("Class.txt");
	int numberClass;
	fi >> numberClass;
	string* listClass = new string[numberClass ];
	for (int i = 0; i < numberClass; i++)
	{
		fi >> listClass[i];
	}
	cout << numberClass << endl;
	for (int i = 0; i < numberClass; i++)
	{
		cout << listClass[i] << endl;
	}
	
}
void option7()
{
	cout << "Enter Class to View List student :";
	string fileClass;
	cin >> fileClass;
	fileClass = fileClass + ".txt";
	ifstream fi;
	int number_studentClass=0;
	student* list_studentClass=NULL;
	readClass(fi, fileClass, number_studentClass, list_studentClass);
	cout << number_studentClass << endl;
	for (int i = 0; i <= number_studentClass; i++)
	{
		cout << list_studentClass[i].no << "," << list_studentClass[i].id << "," << list_studentClass[i].fullname << "," << list_studentClass[i].dob << "," << list_studentClass[i].Class << "," << list_studentClass[i].status << endl;
	}
}
void option3()
{
	int numberClass;
	ifstream fi;
	fi.open("Class.txt");
	if (!fi.is_open()) cout << "Can not open file !";
	else
	{
		fi >> numberClass;
		string* fclass = new string[numberClass];
		for (int i = 0; i < numberClass; i++)
		{
			fi >> fclass[i];
		}
		cout << "==============Class===================" << endl;
		for (int i = 0; i < numberClass; i++)
		{
			cout<<fclass[i]<<endl;
		}
		fi.close();
		cout << "\nEnter class you want to edit student :";
		string Class;
		cin >> Class;
		Class = Class + ".txt";
		cout << "\n Enter student ID :";
		string studentId;
		cin >> studentId;
		//////////////////////////////////////////////////////////////////////////////////////////////////
		ifstream fii;
		int number_studentClass = 0;
		student* list_studentClass, * base;
		readClass(fii, Class, number_studentClass, list_studentClass);
		int temp=0;
		for (int i = 0; i <= number_studentClass; i++)
		{
			if (list_studentClass[i].id == studentId)
				temp = i;
		}
		cout << "Enter new fullname ";
		string fullname;
		cin.ignore();
		getline(cin, fullname);
		cout << "Enter new dob (password)" << endl;
		char dob[20];
		cin.getline(dob, 20);
		strcpy_s(list_studentClass[temp].dob, 20, dob);
		list_studentClass[temp].fullname= fullname;
		ofstream foo;
		WriteToClass(foo, list_studentClass, number_studentClass, Class);
		foo.close();
	///////////////////////////////////////////////////////////////////
		student* list_student = NULL;
		string filestudent = "student.txt";
		int number_student = 0;
		ifstream fa;
		ofstream fb;
		readStudent(fa, filestudent, number_student, list_student);
		
		int temp2=0;
		for (int i = 0; i < number_student; i++)
		{
			if (studentId==list_student[i].id )
				temp2 = i;

		}
		number_student = number_student - 1;
		strcpy_s(list_student[temp2].password, 20, dob);
		strcpy_s(list_student[temp2].dob, 20, dob);
		list_student[temp2].fullname = fullname;
		WriteToStudent(fb, list_student, number_student, filestudent);
	}
	
}
void option4()
{
	
		cout << "\nEnter class you want to remove student :";
		string Class;
		cin >> Class;
		Class = Class + ".txt";
		cout << "\n Enter student ID :";
		string studentId;
		cin >> studentId;
		//////////////////////////////////////////////////////////////////////////////////////////////////
		ifstream fii;
		int number_studentClass = 0;
		student* list_studentClass, * base;
		readClass(fii, Class, number_studentClass, list_studentClass);
		int temp = 0;
		for (int i = 0; i <= number_studentClass; i++)
		{
			if (list_studentClass[i].id == studentId)
			{
				list_studentClass[i].status = "0";
			}
		}
		ofstream foo;
		WriteToClass(foo, list_studentClass, number_studentClass, Class);
		foo.close();
		///////////////////////////////////////////////////////////////////
		student* list_student = NULL;
		string filestudent = "student.txt";
		int number_student = 0;
		ifstream fa;
		ofstream fb;
		readStudent(fa, filestudent, number_student, list_student);

		int temp2 = 0;
		for (int i = 0; i < number_student; i++)
		{
			if (studentId == list_student[i].id)

			{
				list_student[i].status = "0";
			}

		}
		number_student = number_student - 1;
		WriteToStudent(fb, list_student, number_student, filestudent);
		cout << "Remove successfully !!";

}
void option5()
{
	ifstream fi;
	string id,  Class;
	
	student* list_studentClass = NULL;
	int number_studentClass = 0;
	cout << "What class you want to change a student ? :";
	cin >> Class;
	cout << "Enter student ID ";
	cin >> id;
	string file = Class + ".txt";
	readClass(fi, file, number_studentClass, list_studentClass);
	ofstream fo;
	student x;
	for (int i = 0; i <= number_studentClass; i++)
	{		
		if (id == list_studentClass[i].id)
		{
			
			
			x = list_studentClass[i];
			for (int j = number_studentClass; j >i ; j--)
			{
				list_studentClass[j].no = list_studentClass[j - 1].no;
				
			}
			for (int j = i; j < number_studentClass ; j++)
			{
				list_studentClass[j] = list_studentClass[j + 1];
			}
		}


	}
	number_studentClass = number_studentClass-1 ;
	WriteToClass(fo, list_studentClass, number_studentClass, file);
	fo.close();
	////////////////////////////////////////////
	ifstream fii;
	string idd, Classs;

	student* list_studentClasss = NULL;
	int number_studentClasss = 0;
	cout << "What class you want to move the a student to ? ";
	cin >> Classs;
	string filee = Classs + ".txt";
	readClass(fii, filee, number_studentClasss, list_studentClasss);
	number_studentClasss = number_studentClasss + 1;
	string no = to_string(number_studentClasss);
	list_studentClasss[number_studentClasss] = x;
	list_studentClasss[number_studentClasss].no = no;
	ofstream foo;
	WriteToClass(foo, list_studentClasss, number_studentClasss, filee);
	fo.close();
	
	
}
int main()
{
	
		cout << "1.1 Import students of a class from a csv file " << endl;
		cout << "1.2 Manually add a new student to class " << endl;
		cout << "1.3 Edit an existing student " << endl;
		cout << "1.4 Remove a student " << endl;
		cout << "1.5 Chang student from class A to class B" << endl;
		cout << "1.6 View list of students in class " << endl;
		cout << "------Enter your option-------- " << endl;
		double choice;
		cin >> choice;
		if (choice == 1.1)
		{
			option1();
		}
		else if (choice == 1.2)
		{
			option2();
		}
		else if (choice == 1.3)
		{
			option3();
		}
		
		else if (choice == 1.4)
		{
			option4();
		}
		else if (choice == 1.5)
		{
			option5();
		}
		else if (choice == 1.6)
		{
			option6();
		}
		else if (choice == 1.7)
		{
			option7();
		}
	}

	

