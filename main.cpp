#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
using namespace std;
void addEmployee();
bool logIn(string &username);
void DisplayNotLoggedInMenu();
void LoggedInMenu();
void retirement();
void viewall();
void generate();
void displayid(string &usernames);
void search();
void updatedetails(string &usernames);
void deleteAcc(string &usernames);
int main() {
    bool IsLoggedIn=false;
    int choice;
    string username;
    do {

        if (!IsLoggedIn) {
            DisplayNotLoggedInMenu();
            cout << "Enter your choice : " << endl;
            cin >> choice;
            switch (choice) {

                case 1: {
                    addEmployee();
                    break;
                }
                case 2: {
                    IsLoggedIn = logIn(username);
                    if (IsLoggedIn) {
                        cout << "Welcome " << username << " to your Employee Management System! " << endl;
                    } else {
                        cout << "Invalid username OR password!" << endl;
                    }
                    break;
                }
                case 3:{
                    generate();
                    break;

                }
                case 4:{
                    viewall();
                    break;

                }
                case 5:{
                    search();
                    break;

                }
                case 6:{
                    retirement();
                    break;
                }
                case -1: {
                    break;
                }
                default:
                    cout << "You have Entered Wrong Value! Try Again" << endl;
            }
        }
        else {
            LoggedInMenu();
            cout << "Enter your choice : " << endl;
            cin >> choice;
            switch (choice) {

                case 1: {
                    IsLoggedIn = false;
                    break;
                }
                case 2:{
                    displayid(username);
                    break;
                }
                case 3:{
                    updatedetails(username);
                    IsLoggedIn = false;
                    break;
                }
                case 4:{
                    deleteAcc(username);
                    break;
                }
                case -1: {
                    break;
                }
                default: {
                    cout << "You have Entered Wrong Value! Try Again" << endl;
                }
            }
        }

    }while(choice!=-1);
    return 0;
}
void DisplayNotLoggedInMenu(){

    cout << "1. Add Employee : " << endl;
    cout << "2. Employee Login : " << endl;
    cout<<"3. Generate Employee ID Cards : "<<endl;
    cout<<"4. View All Employees : "<<endl;
    cout<<"5. Search Employee By ID : "<<endl;
    cout << "6. List Employees Near Retirement : " << endl;
    cout<<"-1. Exit"<<endl;
}
void LoggedInMenu(){
    cout<<"1: Logout"<<endl;
    cout << "2. Display ID card : " << endl;
    cout << "3. Update Details : " << endl;
    cout << "4. Delete Employee Account : " << endl;
    cout<<"-1: Exit"<<endl;
}
void addEmployee() {
    string usernames, passwords,job;
    int age;
    cout << "Enter username: "<<endl;
    cin >> usernames;
    cout << "Enter password: "<<endl;
    cin >> passwords;
    cout<<"Enter age : "<<endl;
    cin>>age;
    cout<<"Enter your job title : "<<endl;
    cin>>job;
    fstream my_file("../DataFile/users.txt", ios::app);

    my_file<<usernames<<" "<<passwords<<" "<<age<<" "<<job<<endl;
    my_file.close();
    cout<<"Signup Successful!"<<endl;
}
bool logIn(string &usernames){
    string password;
    bool LoginSuccessfull=false;

    cout<<"Enter username : "<<endl;
    cin>>usernames;
    cout<<"Enter password : "<<endl;
    cin>>password;


    string temp_username;
    string temp_password;

    fstream inFile("../DataFile/users.txt",ios::in);

    while(inFile>>temp_username>>temp_password){

        if(usernames==temp_username && temp_password==password) {
            LoginSuccessfull = true;
            return LoginSuccessfull;
        }
    }
    inFile.close();
    return LoginSuccessfull;
}
void retirement() {
    cout<<"The normal retirement age is 60 years old"<<endl;


    fstream my_file("../DataFile/users.txt", ios::in);
    string temp_username;
    string temp_password;
    int temp_age;
    string temp_job;
    int count=0;
    while (my_file >> temp_username >> temp_password>>temp_age>>temp_job) {

        if (temp_age <60 &&temp_age>=55){
            cout<<"The employee "<<temp_username<<" is at age "<<temp_age<<" which is close to retirement."<<endl;
            count++;
        }

    }
    my_file.close();
    if (count==0){
        cout<<"No employee is near the retirement age!"<<endl;
    }
}
void viewall(){
    fstream my_file("../DataFile/users.txt", ios::in);
    string temp_username;
    string temp_password;
    int temp_age;
    string temp_job;
    while (my_file >> temp_username >> temp_password>>temp_age>>temp_job) {

        cout<<"Employee : "<<temp_username<<" Age : "<<temp_age<<" Job : "<<temp_job<<endl;

    }
    my_file.close();
}
void generate(){
    string username;
    cout<<"Enter the name of the employee : "<<endl;
    cin>>username;
    fstream my_file("../DataFile/users.txt", ios::in);
    string temp_username;
    string temp_password;
    int temp_age;
    string temp_job;
    while (my_file >> temp_username >> temp_password>>temp_age>>temp_job){
        if (temp_username==username){
            int randomID = rand() % 100000;
            fstream f1("../DataFile/id.txt", ios::app);
            f1<<temp_username<<" "<<temp_age<<" "<<temp_job<<" "<<randomID<<endl;
            f1.close();
            cout<<"Generated Successfully"<<endl;
        }
    }
    my_file.close();
}
void displayid(string &usernames){
    fstream my_file("../DataFile/id.txt", ios::in);
    string temp_username;
    string temp_password;
    int temp_age;
    string temp_job;
    int temp_id;
    string emp_name,emp_profession;
    int emp_age,emp_id;
    while (my_file >> temp_username >> temp_age>>temp_job>>temp_id){
        if (usernames==temp_username){
            emp_name=temp_username;
            emp_profession=temp_job;
            emp_age=temp_age;
            emp_id=temp_id;
            cout << "\n==============================" << endl;
            cout << "          Employee ID Card          " << endl;
            cout << "==============================" << endl;
            cout << "Name      : " << emp_name << endl;
            cout << "ID        : " << emp_id << endl;
            cout << "Age       : " << emp_age << endl;
            cout << "Profession: " << emp_profession << endl;
            cout << "==============================" << endl;

        }
    }

    my_file.close();
}
void search(){
    int id;
    cout<<"Enter the employee ID : "<<endl;
    cin>>id;
    fstream my_file("../DataFile/id.txt", ios::in);
    string temp_username;
    string temp_password;
    int temp_age;
    string temp_job;
    int temp_id;
    while (my_file >> temp_username >> temp_age>>temp_job>>temp_id){
        if (id==temp_id){
            cout << "==============================" << endl;
            cout << "          Employee ID Card          " << endl;
            cout << "==============================" << endl;
            cout << "Name      : " << temp_username << endl;
            cout << "ID        : " << temp_id << endl;
            cout << "Age       : " << temp_age << endl;
            cout << "Profession: " << temp_job << endl;
            cout << "==============================" << endl;

        }
    }

    my_file.close();
}
void updatedetails(string &usernames){
    int choice;
    cout<<"What details do you want to change?"<<endl<<"1. Name "<<endl<<"2. Password "<<endl<<"3.Age"<<endl<<"4. Profession "<<endl;
    cin>>choice;
    if (choice==1){
        string name;
        cout<<"Enter a new name : "<<endl;
        cin>>name;
        fstream f1;
        fstream f2;

        string ch;
        f1.open("../DataFile/users.txt", ios::in);

        f2.open("../DataFile/newusers.txt", ios::out);
        while (!f1.eof()) {

            while (getline(f1, ch)) {
                istringstream iss(ch);
                string temp_user, temp_pass,temp_job;
                int temp_age;

                iss >> temp_user;
                iss >> temp_pass;
                iss>>temp_age;
                iss>>temp_job;

                if (temp_user == usernames ) {
                    f2 << name << " " << temp_pass << " "<<temp_age<<" "<<temp_job<<endl;
                } else {
                    f2 << ch << endl;
                }

            }

        }

        f1.close();
        f2.close();
        remove("../DataFile/users.txt");
        rename("../DataFile/newusers.txt", "../DataFile/users.txt");
        cout<<"Updated Successfully!"<<endl;
    }
    else{
        if (choice==2){
            string pass;
            cout<<"Enter a new password : "<<endl;
            cin>>pass;
            fstream f1;
            fstream f2;

            string ch;
            f1.open("../DataFile/users.txt", ios::in);

            f2.open("../DataFile/newusers.txt", ios::out);
            while (!f1.eof()) {

                while (getline(f1, ch)) {
                    istringstream iss(ch);
                    string temp_user, temp_pass,temp_job;
                    int temp_age;

                    iss >> temp_user;
                    iss >> temp_pass;
                    iss>>temp_age;
                    iss>>temp_job;

                    if (temp_user == usernames ) {
                        f2 << temp_user << " " << pass << " "<<temp_age<<" "<<temp_job<<endl;
                    } else {
                        f2 << ch << endl;
                    }

                }

            }

            f1.close();
            f2.close();
            remove("../DataFile/users.txt");
            rename("../DataFile/newusers.txt", "../DataFile/users.txt");
            cout<<"Updated Successfully!"<<endl;
        }
        else{
            if (choice==3){
                int age;
                cout<<"Enter a new age : "<<endl;
                cin>>age;
                fstream f1;
                fstream f2;

                string ch;
                f1.open("../DataFile/users.txt", ios::in);

                f2.open("../DataFile/newusers.txt", ios::out);
                while (!f1.eof()) {

                    while (getline(f1, ch)) {
                        istringstream iss(ch);
                        string temp_user, temp_pass,temp_job;
                        int temp_age;

                        iss >> temp_user;
                        iss >> temp_pass;
                        iss>>temp_age;
                        iss>>temp_job;

                        if (temp_user == usernames ) {
                            f2 << temp_user << " " << temp_pass << " "<<age<<" "<<temp_job<<endl;
                        } else {
                            f2 << ch << endl;
                        }

                    }

                }

                f1.close();
                f2.close();
                remove("../DataFile/users.txt");
                rename("../DataFile/newusers.txt", "../DataFile/users.txt");
                cout<<"Updated Successfully!"<<endl;
            }
            else{
                if (choice==4){
                    string profession;
                    cout<<"Enter a new profession : "<<endl;
                    cin>>profession;
                    fstream f1;
                    fstream f2;

                    string ch;
                    f1.open("../DataFile/users.txt", ios::in);

                    f2.open("../DataFile/newusers.txt", ios::out);
                    while (!f1.eof()) {

                        while (getline(f1, ch)) {
                            istringstream iss(ch);
                            string temp_user, temp_pass,temp_job;
                            int temp_age;

                            iss >> temp_user;
                            iss >> temp_pass;
                            iss>>temp_age;
                            iss>>temp_job;

                            if (temp_user == usernames ) {
                                f2 << temp_user << " " << temp_pass << " "<<temp_age<<" "<<profession<<endl;
                            } else {
                                f2 << ch << endl;
                            }

                        }

                    }

                    f1.close();
                    f2.close();
                    remove("../DataFile/users.txt");
                    rename("../DataFile/newusers.txt", "../DataFile/users.txt");
                    cout<<"Updated Successfully!"<<endl;
                }
                else{
                    cout<<"Wrong choice selected!"<<endl;
                }
            }
        }
    }
    generate();
}
void deleteAcc(string &usernames){
    string password;


    cout<<"Enter your password to delete your account : "<<endl;
    cin>>password;

    fstream f1;
    fstream f2;

    string ch;

    f1.open("../DataFile/users.txt", ios::in);

    f2.open("../DataFile/new.txt", ios::out);
    bool flag=false;
    while (!f1.eof()) {

        while (getline(f1, ch)) {
            istringstream iss(ch);
            string firstWord, secondWord;

            iss >> firstWord;

            iss >> secondWord;

            if (!(firstWord==usernames&&secondWord==password)){
                f2 << ch << endl;
            }
            if (firstWord==usernames&&secondWord==password){
                cout<<"Your Account was Found and Deleted Successfully!"<<endl;
                flag=true;
            }

        }

    }
    if (!flag){
        cout<<"Wrong Password !"<<endl;
    }

    f1.close();
    f2.close();


    remove("../DataFile/users.txt");
    rename("../DataFile/new.txt","../DataFile/users.txt");

}