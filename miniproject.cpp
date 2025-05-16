#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>
#include <string.h>

using namespace std;
class captcha_generator
	{
	public:
		int captcha;
		int captcha1;
	
		void generate()
		{
			captcha = rand() % 9000 + 1000;
		}
		void displaycaptcha()
		{
			cout << "are you human?" << endl;
			cout << "captcha:" << captcha << endl;
			cin >> captcha1;
	}
};


class registration : public captcha_generator {
public:
	char username[100];
	char password[100];

	void registrations() {
		cout << "Please enter username\n";
		cin >> username;
		cout << "Enter password\n";
		cin >> password;
		generate();
		displaycaptcha();
		if (captcha == captcha1) {
			cout << "Registration successful\n";
		}
		else {
			cout << "!!!!INVALID DETAILS!!!\n";
		}
	}
};

class login : public captcha_generator, public registration {
public:
	char u1[100];
	char p1[100];

	void logins() {
		cout << "\nEnter valid username: ";
		cin >> u1;
		cout << "\nEnter valid password: ";
		cin >> p1;
		captcha_generator::generate();
		captcha_generator::displaycaptcha();
		if (strcmp(u1, username) == 0 && strcmp(p1, password) == 0) {
			if (captcha_generator::captcha1 == captcha_generator::captcha) {
				cout << "Login successful\n";
			}
			else {
				cout << "!!!!INVALID DETAILS!!!\n";
			}
		}
		else {
			cout << "!!!Wrong username/password!!!\n";
		}
	}
};

class change_cred : public login {
public:
	char new_username[100];
	char new_pass[100];
	char check_username[100];
	char check_pass[100];

	void new_cred() {
		cout << "Enter new credentials\n";
		cout << "\nEnter NEW Username: ";
		cin >> new_username;
		cout << "\nEnter NEW password: ";
		cin >> new_pass;
	}

	void check_newcred() {
		cout << "Please enter credentials again\n";
		cout << "Enter username: ";
		cin >> check_username;
		cout << "Enter password: ";
		cin >> check_pass;
		captcha_generator::generate();
		captcha_generator::displaycaptcha();
		if (strcmp(new_username, check_username) == 0 && strcmp(new_pass, check_pass) == 0) {
			if (captcha_generator::captcha == captcha_generator::captcha1) {
				cout << "Credentials changed successfully\n";
			}
			else {
				cout << "!!!!INVALID DETAILS!!!\n";
			}
		}
		else {
			cout << "!!!Wrong username/password!!!\n";
		}
	}
};

class subscription : public login {
public:
	char details[100];
	int count = 0;

		void 	subscriptions() {
		logins();
		cout << "\nYou have subscribed to store up to 100 passwords\n";
		if (count < 100) {
			cout << "\nEnter details to store: ";
			cin >> details;
			count++;
			ofstream out("sample.txt");
			out << details;
			cout << "Details saved successfully\n";
		}
	}

	void read_details() {
		cout << "\nREADING FROM FILE:";
		ifstream in("sample.txt");
		in >> details;
		cout << details;
	}
};
class cost : public subscription {
public:
	inline int inr(int dollar = 99) {
		cout << "\nThe cost of the subscription is: ";
		cout << "\nIn INR = " << dollar * 82 << endl;
		return dollar * 82;
	}
};
class logout {
public:
	logout() {
		cout << " " << endl;
	}

	~logout() {
		cout << "destructor used" << endl;
	}

	void pause() {
		cout << "logging out...";
		system("pause");
	}

	void close() {
		cout << "Exiting the program." << endl;
		exit(0); // Ends the program
	}
	friend void showLogoutDetails(const logout&);
};
void showLogoutDetails(const logout& l) {
	cout << "Logout sequence initialized" << endl;
}


int main() {
	srand(time(0));
	int choice;
	cost s1;
	change_cred c1;
	logout l1;
	cout.fill('-');
	cout.width(30);
	cout << "\nSECURE_SYSTEM";
	cout.fill('-');
	cout.setf(ios::right, ios::adjustfield);
	cout.width(30);

	 
	while (1) {
		cout << "\n1) Registration\n2) Login\n3) Change credentials\n4)write details to the file\nread details from the file\n5)price\n6)log out\n";
		cin >> choice;
		switch (choice) {
		case 1:
			s1.registrations();
			break;
		case 2:
			s1.logins();
			break;
			
			  
		case 3:
			c1.new_cred();
			c1.check_newcred();	 
			break;
		case 4: 
			s1.subscriptions();
			s1.read_details();
			break;
		case 5:
			s1.inr();
			break;
		case 6:
			logout();
			l1.pause();
			l1.close();
			

			break;
		default:
			cout << "Invalid choice\n";
			break;
		}
	}
	return 0;
}