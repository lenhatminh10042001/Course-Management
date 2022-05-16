#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
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
			cout<<"Your present password is not correct.";
		}
	}
}
void Logout(){
	cout<<"You has been log out.";
	return;
}
void Option_for_staff(double option_staff,Staff *staff, int &staff_position){
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
	}
	else if(option_staff==1.3){
		Chang_password_staff(staff,staff_position);
	}
	else if(option_staff ==1.4){
		Logout();
	} 
}

int main(){
	Staff *staff;
	int number_staff;
	ifstream filestaff;
	//Doc thong tin tu file Academic_Staff.
	Input_Staff(filestaff,staff,number_staff);
	//
	string account_staff,pass;// khoi tao chuoi ta khoan dang nhap, mat khau.
	int option_staff;//lua chon cua staff.
	int staff_position;// vi tri cua staff trong file.
	if(Login_Staff(account_staff,pass,staff,number_staff,staff_position)==1){// neu dang nhap thanh cong
		Option_for_staff(option_staff,staff,staff_position);
	};
	return 0;
}
