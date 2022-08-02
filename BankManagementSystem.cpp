//Bank(ATM) Management system Project by Soubhagya kumar dash.
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
class atm
{
private:
    char username[30];
    int password;
    int balance;

public:
    char *usernames(void)
    {
        return username;
    }
    int passwords(void)
    {
        return password;
    }
    void getdata(void)
    {
        cout << "\nEnter username: ";
        cin >> username;
        cout << "Enter 4-digit password: ";
        cin >> password;
        cout << "Enter initial balance: ";
        cin >> balance;
    }
    void showdata(void)
    {
        cout << "Username: " << username << endl;
        cout << "Password: " << password << endl;
        cout << "Balance: " << balance << endl;
    }
    int adduser();
    int viewallusers();
    int deleteuser(char *);
    void updateuserasdeposit(char *);
    void updateuseraswithdraw(char *);
    int searchspecificuser(char *, int);
    int searchallusertodisplay(char *);
};

// defining a function that adds a user
int atm::adduser()
{
    atm a;

    ofstream file;

    file.open("aaa.txt", ios::out | ios::app);
    if (!file)
    {
        cout << "Error in creating file..." << endl;
        return 0;
    }

    a.getdata();

    file.write((char *)&a, sizeof(a));

    file.close();

    return 0;
} 

// defining a function that shows all the users
int atm::viewallusers()
{

    atm a;

    ifstream file1;

    file1.open("aaa.txt", ios::in);
    if (!file1)
    {
        cout << "Error in opening file..";
        return 0;
    }

    file1.read((char *)&a, sizeof(a));
    while (!file1.eof())
    {
        a.showdata();
        file1.read((char *)&a, sizeof(a));
    }

    file1.close();
    return 0;
} 

// defining a function that deletes a user account
int atm::deleteuser(char *uname)
{
    atm a;

    fstream original, temp;
    original.open("aaa.txt", ios::in);
    if (!original)
    {
        cout << endl;
        cout << "file not found";
        return 0;
    }
    else
    {
        temp.open("temp.txt", ios::out | ios::app);
        original.read((char *)&a, sizeof(a));

        while (!original.eof())
        {
            if (!strcmp(a.usernames(), uname))
            {
                cout << "data found and deleted \n"
                     << a.username << "\n";
            }
            else
            {
                temp.write((char *)&a, sizeof(a));
            }

            original.read((char *)&a, sizeof(a));
        }

        original.close();
        temp.close();
        remove("aaa.txt");
        rename("temp.txt", "aaa.txt");
        a.viewallusers();
    }
    return 0;
} 

// defining a function that updates the user account when money is deposited
void atm::updateuserasdeposit(char *uname)
{
    atm a;
    fstream file, temp;
    file.open("aaa.txt", ios::in | ios::out | ios::ate);
    temp.open("temp.txt", ios::out | ios::app);
    file.seekg(0);
    file.read((char *)&a, sizeof(a));

    if (!strcmp(a.usernames(), uname))
    {
        int b;

        cout << endl;
        cout << "Enter amount to deposit:";
        cin >> b;
        a.balance = a.balance + b;
        cout << endl;
        cout<<"Amount Successfully deposited!!!\n";
        cout << "Your current balance is: " << a.balance << endl << endl;
        temp.write((char *)&a, sizeof(a));
    }
    else
    {
        temp.write((char *)&a, sizeof(a));
    }
    file.read((char *)&a, sizeof(a));

    file.close();
    temp.close();
    remove("aaa.txt");
    rename("temp.txt", "aaa.txt");
} 

// defining a function that updates the user account when money is withdrawn
void atm::updateuseraswithdraw(char *uname)
{

    atm a;
    fstream file, temp;
    file.open("aaa.txt", ios::in | ios::out | ios::ate);
    temp.open("temp.txt", ios::out | ios::app);
    file.seekg(0);
    file.read((char *)&a, sizeof(a));

    while (!file.eof())
    {
        if (!strcmp(a.usernames(), uname))
        {
            int b;
            cout << endl;
            cout << "Enter amount to withdraw:";
            cin >> b;
            if (a.balance < b)
            {
                cout << "Insufficient balance to withdraw" << endl;
            }
            else
            {
                a.balance = a.balance - b;
                temp.write((char *)&a, sizeof(a));
                cout<<"\nMoney withdrawn successfully\n";
                cout << "\nYour current balance is:" << a.balance << endl << endl;
            }
        }
        else
        {
            temp.write((char *)&a, sizeof(a));
        }
        file.read((char *)&a, sizeof(a));
    }

    file.close();
    temp.close();
    remove("aaa.txt");
    rename("temp.txt", "aaa.txt");
} 

// defining a function that search for a specific user whose username and password are known
int atm::searchspecificuser(char *uname, int pass)
{
    atm a;
    fstream f;

    f.open("aaa.txt", ios::in);
    if (!f)
    {
        cout << "Error in opening file..";
        return 0;
    }

    f.read((char *)&a, sizeof(a));
    while (!f.eof())
    {

        if (!strcmp(a.usernames(), uname))
        {
            if (a.passwords() == pass)
            {
                return 1;
            }
        }
        f.read((char *)&a, sizeof(a));
    }

    f.close();
    return 0;
} 

int atm::searchallusertodisplay(char *uname)
{
    atm a;
    fstream file1;

    file1.open("aaa.txt", ios::in);
    if (!file1)
    {
        cout << "Error in opening file..";
        return 0;
    }

    file1.read((char *)&a, sizeof(a));
    while (!file1.eof())
    {
        if (!strcmp(a.usernames(), uname))
        {
            cout<<endl;
            a.showdata();
            cout<<endl;
            return 0;
        }
        file1.read((char *)&a, sizeof(a));
    }

    file1.close();
    return 0;
}

void atmUser()
{
    atm a;

    char uname[30];
    int pass, ch, ch1, found = 0;

mainmenu:

    system("clear");
    cout << "***********************************************************************\n\t\t\tSoubhagya's Bank Application\n***********************************************************************" << endl;
    cout << "1.New Account\n"
         << "2.Login\n"
         << "3.Quit\n"
         << "4.Delete an Account\n";
    cout << "\nEnter Your Option: ";
    cin >> ch;

    switch (ch)
    {
    case 1:
        a.adduser();
        goto mainmenu; // adding a user

    case 2:
        cout << endl;
        cout << "Enter username:";
        cin >> uname;
        cout << "Enter password:";
        cin >> pass;
        found = a.searchspecificuser(uname, pass); // searching for a user

        if (found)
        {
        user:
            cout << "\nWelcome " << uname << "!!!" << endl;
            cout << "User Menu\n";
            cout << "1.Withdraw money\n"
                 << "2.Deposit money\n"
                 << "3.Balance Enquiry\n"
                 << "Enter a digit between 10 and 99 to exit\n";
            cout << "\nEnter Your Option: ";
            cin >> ch1;
            switch (ch1)
            {
            case 1:
                a.updateuseraswithdraw(uname); // withdrawing money
                goto user;

            case 2:
                a.updateuserasdeposit(uname); // depositing money
                goto user;

            case 3:
                a.searchallusertodisplay(uname); // seeing the information of the account
                goto user;

                break;
            }
        }
        else
        {
            cout << "No account found with given username and password\n";
            cin.get();
        } //
        goto mainmenu;

    case 3:
        cout << "******************************************************************\n\t\t\tThank you\n\t\t\tVisit Again!!\n******************************************************************"; // quiting the session
        cin.get();
        break;

    case 4:
        cout << "Enter the username to be deleted: \n";
        cin >> uname;
        a.deleteuser(uname); // deleting the account
        goto user;
    }
}

int main()
{
    atmUser();
    return 0;
}