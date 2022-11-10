#include<fstream>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<cstdio>

using namespace std;

// Creating a class to store question related data
class question
{
	char sub[20];
	int qno;
	char q[100];
	char a[200];

	public:

    // Function to input a new question
	void input()
	{
	    getchar();
		cout<<"Enter subject choice: ";
		gets(sub);
		cout<<"Enter question number: ";
		cin>>qno;
		getchar();
		cout<<"Enter question: ";
		gets(q);
		cout<<"Enter answer: ";
		gets(a);
	}
    
    // Function to output a question
	void output()
	{
		cout<<"Subject: "<<sub<<endl<<endl;
		cout<<"Q"<<qno<<":  "<<q<<endl;
		cout<<"A"<<qno<<":  "<<a<<endl<<endl;
	}
    
    // Function to modify a question
	void inputmod()
	{
		cout<<"Enter new question: ";
		gets(q);
		cout<<"Enter new answer: ";
		gets(a);
	}
    
    // Function to output questions for a particular subject
	void outputmod()
	{
		cout<<"Q"<<qno<<" "<<q<<endl;
		cout<<"A"<<qno<<" "<<a<<endl<<endl;
	}

	char* getsub()
	{
		return sub;
	}

	int getqno()
	{
		return qno;
	}
};

// Creating a class to store data related to users and their login info

class member
{
	char uname[20];
	char pass[20];
	char passconf[20];

	public:
    
    // Function to register a new user
	void input()
	{
	    getchar();
		cout<<"Enter username: ";
		gets(uname);
		cout<<"Enter password: ";
		gets(pass);
		cout<<"Confirm password: ";
		gets(passconf);
		if(strcmp(pass,passconf)==0)
		{
			cout<<"You have been registerd!";
		}
		else
		{
			cout<<"Passwords do not match! Try again!";
		}
		cout<<"\nPress enter to continue";
	}

	char* getuse()
	{
		return uname;
	}

	char* getpass()
	{
		return pass;
	}
};


// Function to add a new question 
void add()
{
	system("clear");
	ofstream f;
	f.open("qb.dat", ios::binary|ios::app);     // Opens qb.dat file which stores all questions
	question s;
	s.input();
	f.write((char*)&s, sizeof(s));              // Writes new question to qb.dat
	f.close();
	cout<<"\nQuestion added! \n\nPress enter to continue";
	cin.get();
	system("clear");
}

// Function to display all questions stored
void display()
{
	system("clear");
	getchar();
	ifstream f;
	f.open("qb.dat", ios::binary);              // Opens qb.dat file
	question s;
	while(f.read((char*)&s, sizeof(s)))
	{
		s.output();                             // Outputs all questions stored
	}
	f.close();
	cout<<"----- End -----";
	cout<<"\nPress enter to return to main menu";
	cin.get();
	system("clear");
}

// Function to search for questions for a particular subject
void search()
{
	system("clear");
	char a[20];
	ifstream f;
	f.open("qb.dat", ios::binary);                  // Opens qb.dat file with all questions
	question s;
	getchar();
	cout<<"Enter subject: ";                        // Inputs the subject from user
	gets(a);
	cout<<endl;
	int ctr = 0;
	while(f.read((char*)&s, sizeof(s)))             // Reads all questions
	{
		if(strcasecmp(s.getsub(),a)==0)             // Compares user input with each question's subject
		{
			s.outputmod();                          // Output only if same subject
			ctr++;
		}
		
		
	}
	if (ctr==0)                                 // If no question from same subject, output None
	{
	    cout<<"No questions for this subject!\n";
	}
	cout<<"Press enter to return to main menu";
	f.close();
	cin.get();
	system("clear");
}

// Function to modify a subject
void modify()
{
	system("clear");
	char a[20];
	int n;
	ofstream f1;
	ifstream f2;
	f1.open("temp.dat", ios::binary|ios::app);              // Create temporary file to store modified quesiton
	f2.open("qb.dat", ios::binary);                         // Read all questions stored
	question s;
	getchar();
	cout<<"Enter subject: ";                                // Input subject and question number from user
	gets(a);
	cout<<"Enter question number: ";
	cin>>n;
	getchar();
	int match = 0;
	while(f2.read((char*)&s, sizeof(s)))                    // Loop through all questions
	{
		if((strcasecmp(s.getsub(),a)==0) && (s.getqno()==n))        // If subject and q. no match then input new question/answer
		{
		    match = 1;
			s.inputmod();
			f1.write((char*)&s, sizeof(s));                         // Write into temporary file
		}
		else
		{
			f1.write((char*)&s, sizeof(s));                         // Write into temporary file directly if not the chosen question
		}
	}
	if (match==0)
	{
	    cout<<"No match found, please check your input!";
	}
	else
	{
	    cout<<"\nQuestion modified!";
	}
	cout<<"\nPress enter to continue";
	f1.close();
	f2.close();
	remove("qb.dat");
	rename("temp.dat","qb.dat");                                // Delete old question file and rename new one
	cin.get();
	system("clear");
}

// Function to delete a question
void del()
{
	system("clear");
	char a[20];
	int n;
	ofstream f1;
	ifstream f2;
	f1.open("temp.dat", ios::binary|ios::app);                  // Temporary file to store questions
	f2.open("qb.dat", ios::binary);                             // Existing file with all questions
	question s;
	getchar();
	cout<<"Enter subject: ";                                    // Input subject and q. no from user to delete
	gets(a);
	cout<<"Enter question number: ";
	cin>>n;
	getchar(); 
	int match = 0;
	while(f2.read((char*)&s, sizeof(s)))                        // Loop through all questions
	{
		if((strcasecmp(s.getsub(),a)==0) && (s.getqno()==n))    // If subject and q.no match then do nothing
		{
            match = 1;
            cout<<"Deleted following question"<<endl<<endl;
            s.output();

		}
		else
		{
			f1.write((char*)&s, sizeof(s));                     // All other questions are written to temp file
		}
	}
	f1.close();
	f2.close();
	remove("qb.dat");
	rename("temp.dat","qb.dat");                                // Delete existing file and rename temp file
	if (match==0)
	{
	    cout<<"\nNo match found, please try again";
	}
	cout<<"\nPress enter to continue";
	cin.get();
	system("clear");
}

// Function to register a new user
void reg()
{
	system("clear");
	ofstream f;
	f.open("user.dat",ios::binary|ios::app);                // user.dat stores data about usernames/passwords
	member s;
	s.input();
	f.write((char*)&s, sizeof(s));                          // Store data after taking input from user
	f.close();
	cin.get();
	system("clear");
}

// Function to login a new user
int login()
{
	system("clear");
	ifstream f;
	f.open("user.dat",ios::binary);                         // user.dat stores all usernames/passwords
	char usern[20];
	char passw[20];
	getchar();
	cout<<"Enter username: ";                               // Input username and password from user
	gets(usern);
	cout<<"Enter password: ";
	gets(passw);
	member s;
	int login_success = 0;
	while(f.read((char*)&s, sizeof(s)))                     // Loop through all users
	{
	    
		if(strcmp(s.getuse(),usern)==0)
		{
			if(strcmp(s.getpass(),passw)==0)                // Check to see if both username and password match, return 1 if match
			{
				cout<<"Welcome "<<usern<<endl<<endl;
				cout<<"Press enter to proceed";
				login_success = 1;
				break;
			}
		}
		
	}
	f.close();
	if (login_success==0)
	{
	    cout<<"INVALID USERNAME OR PASSWORD!"<<endl;        // If not, return 0 
	    cout<<"\nPress enter to continue";
    	return 0;
	}
    else
    {
        return 1;
    }
	cin.get();
	system("clear");

}


// MAIN FUNCTION

int main()
{
	system("clear");
	int i,j, k;                 // Main menu for users
	b :
	cout<<"**** 		WELCOME TO QUESTION BANK		****"<<endl;
	cout<<"Enter 1 to register"<<endl;
	cout<<"Enter 2 to login"<<endl;
	cout<<"Enter 0 to exit"<<endl;
	cin>>j;

	switch(j)                       // Switch statement to determine user's input
	{
		case 1: reg();
			goto b;
			break;

		case 2: k=login();
			if(k==1)                // If login returned 1 (successful), then go to next menu
			{
				cin.get();
				system("clear");
				goto a;
			}
			else if(k==0)           // If login returned 0 (failed), go back to main menu
			{
				cin.get();
				system("clear");
				goto b;
			}
			break;

		case 0: exit(0);
			break;

		default: cout<<"Enter valid option!"<<endl;         // If invalid input, go to main menu
			 cin.get();
			 system("clear");
			 goto b;
			 break;

	}
	
	// Menu for logged in users
	
	a :
	cout<<"****		QUESTION BANK		****"<<endl;
	cout<<endl<<"****		   MENU		    ****"<<endl;
	cout<<"1. ADD A QUESTION"<<endl;
	cout<<"2. DISPLAY ALL QUESTIONS"<<endl;
	cout<<"3. DISPLAY QUESTIONS OF A PARTICULAR SUBJECT"<<endl;
	cout<<"4. MODIFY A QUESTION"<<endl;
	cout<<"5. DELETE A QUESTION"<<endl;
	cout<<"0. Exit"<<endl;

	cin>>i;

	switch(i)                               // Switch statement for logged in users
	{
		case 1: add();                      
			system("clear");
			break;

		case 2: display();
			system("clear");
			break;

		case 3: search();
			system("clear");
			break;

		case 4: modify();
			system("clear");
			break;

		case 5: del();
			system("clear");
			break;

		case 0: exit(0);

		default: cout<<"Please enter a valid option";
	}
	goto a ;        // Show menu again after all operations
	cin.get();
}