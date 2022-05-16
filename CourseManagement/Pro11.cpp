#include<iostream>
#include<fstream>
#include<cstring>
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
struct Student {
	string account;
	string password;
	string name;
	Date dob;
	string class1;
	int gender;
};
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
bool Login_Student(string account, string password, Student* student, int number_of_student) {
	for (int i = 0; i < number_of_student; i++) {
		if (account == student[i].account && password == student[i].password) {
			cout << "Welcome " << student[i].name << " logged to system" << endl;
			return true;
		}
	}
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
void ViewProfileStudent(Student s) {
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
void ChangePasswordStudent(Student s, Student*& student, int number_of_student) {
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

//LECTURER
struct Lecture
{
	string username;
	string password;
	string fullname;
	string degree;
	string sex;
};

//void loadLec(ifstream& f, Lecture& lecture)
//{
//	getline(f, lecture.username);
//	getline(f, lecture.username);       // doc them 1 lan getline o day vi truoc do doc vao con so f >> n
//
//	getline(f, lecture.password);
//	getline(f, lecture.fullname);
//	getline(f, lecture.degree);
//	getline(f, lecture.sex);
//
//}


void loadfileLec(ifstream& f,int &n,Lecture *&lec)
{
	f >> n;
	lec= new Lecture[n];
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

bool checkUserPass(string user, string pass, int n, Lecture *lec)
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


void callFullName(string user, string pass, int n, Lecture *lec)
{
	for (int i = 0; i < n; i++)
	{
		if (lec[i].username == user && lec[i].password == pass)
		{
			cout << lec[i].degree << "  " << lec[i].fullname << endl;
		}
	}
}


void viewProfile(string user, string pass, int n, Lecture *lec)
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

void changePass(ifstream& f, string user, string pass, int &n, Lecture *&lec)
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
//		f.open("Lecturer.txt");
//		f >> n;
		for (int i = 0; i < n; i++)
		{
//			loadfileLec(f,n,lec);
			if (lec[i].password == pass)
			{
				lec[i].password.swap(newpass1);
			}
		}
		//cout<<lec[0].password<<endl;
//		f.close();
		cout << "change password succesfully" << endl;
	}
	else
	{
		cout << "can not change password" << endl;
	}
}


void writeLecture(ofstream& f, Lecture *lec, int number_lecture)
{
	//cout << lec[0].password << endl;
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



//STAFF
struct Staff{
	string username;//ten dang nhap
	string pass_staff;//mat khau
	string fullname;//ho ten
	string age;//tuoi
};
void Input_Staff(ifstream &filestaff, Staff*& staff, int & number_staff ){
	filestaff.open("Academic_Staff.txt");
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
	cout<<"---------------Enter yout option:";
	cin>>option_staff;
	while(option_staff>1.4 || option_staff<1.1){
		cout<<"1.1 to 1.4, please"<<endl;
		cout<<"Enter your option:";
		cin>>option_staff;
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
				cout<<"Completely changed your password, remember to use your new password to log in next time.";
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
	staffout.open("Academic_Staff.txt");
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
void Option_for_staff(double option_staff,Staff *staff, int &staff_position,int number_staff){
	cout<<"There are 4 option for you to choose: "<<endl<<endl;
	cout<<"1.1 Show menu."<<endl;
	cout<<"1.2 View your profile info."<<endl;
	cout<<"1.3 Change your password."<<endl;
	cout<<"1.4 Log out."<<endl<<endl<<endl;
	cout<<"---------------Enter yout option:";
	cin>>option_staff;
	while(option_staff>1.4 || option_staff<1.1){
		cout<<"1.1 to 1.4, please"<<endl;
		cout<<"Enter your option:";
		cin>>option_staff;
	}
	if(option_staff==1.2){
		View_profile_staff(staff,staff_position);
		Option_for_staff(option_staff,staff,staff_position,number_staff);
	}
	else if(option_staff==1.3){
		Chang_password_staff(staff,staff_position);
		ofstream staffout;
		writeStaff(staffout,staff,number_staff);
		Option_for_staff(option_staff,staff,staff_position,number_staff);
	}
	else if(option_staff ==1.4){
		Logout();
	} 
}

int main(){
	int role;
	School_role(role);
	if(role==1){
		Student* student;
		int number_of_student, number_of_staff, number_of_lecturer, option1;
		ifstream fin;
		ofstream fout;
		string account, password;
		readStudent(fin, student, number_of_student);
		cout << "\t\t\t\t WELCOME TO STUDENT MANAGEMENT SYSTEM" << endl;
	showMenu();
	cout << "Choose your option (1 or 2): ";
	cin >> option1;
	while (option1 != 2) {
		cout << "Enter your account: ";
		cin >> account;
		cout << "Enter your password: ";
		cin >> password;
		while (!Login_Student(account, password, student, number_of_student)) {
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
				ViewProfileStudent(s);
			else if (option2 == 2) {
				ChangePasswordStudent(s, student, number_of_student);
				writeStudent(fout, student, number_of_student);
				}
			cout << "Choose your option (1-7): ";
			cin >> option2;
			}
		Logout();
		showMenu();
		cout << "Choose your option (1 or 2): ";
		cin >> option1;
		}
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
		cout << "can not open file Lecture to read";
	}
	else
	{
		loadfileLec(readLec,n,lec);
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
					//cout << lec[0].password << endl;
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
		if(Login_Staff(account_staff,pass,staff,number_staff,staff_position)==1){// neu dang nhap thanh cong
		Option_for_staff(option_staff,staff,staff_position,number_staff);
		};
	}
	return 0;
}
