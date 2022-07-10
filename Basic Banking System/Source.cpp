#include <iostream>
#include <string>
#include <vector>

using namespace std; 



class customer
{
public:

	//Attributes
	string name; 
	int accountId, accountType, phoneNumber; 
	float balance;

	//Behaviours

	void withdraw (int value)
	{
		cout << "Amount: ";
		cin >> value;
		cout << endl;
		if (balance >= value)
		{
			balance -= value;
			displayInfo();
		}
		else
		{
			cout << "You don't have enough money" << endl; 
		}
	}

	void deposit(int value)
	{
		cout << "Amount: ";
		cin >> value; 
		cout << endl;
		balance += value;
		displayInfo();

	}

	void displayInfo()
	{
		cout << "Name: " << name << endl;
		cout << "AccountId: " << accountId << endl;
		cout << "Balance: " << balance << endl;
		cout << "Phone number:" << phoneNumber<< endl; 
		if (accountType == 1)
		{
			cout << "Account type: Current Account" << endl;
		}
		else if (accountType == 2 )
		{
			cout << "Account type: Savings Account" << endl;
		}
	}

	void update(int phoneNum, string Name, int account, int value )
	{
		cout << "Which property you want to update: " << endl;
		cout << "1- Phone number   |";
		cout << "    2- Name    |";
		cout << "    3- Account type" << endl;

		cin >> value; 
		if (value == 1)
		{
			cout << "Write the new phone number: ";
			cin >> phoneNum;
			cout << endl;
			phoneNumber = phoneNum;
			displayInfo();
		}

		else if (value == 2)
		{
			cout << "Write the new name: " << endl;
			cin >> Name;
			name = Name;
			cout << endl;
			displayInfo();
		}
		
		else if (value == 3)
		{
			int acctype;
			cout << "Choose the account type: " << endl;
			cout << "1- Current Account" << endl;
			cout << "2- Saving Account" << endl;
			cin >> acctype;
			if (acctype == 1)
			{
				accountType = acctype;
			}

			else if (acctype == 2)
			{
				accountType = acctype;
			}
			cout << endl;
			displayInfo();
		}
	}

	customer(string Name, int accountTypee, float Balance, int AccountId, int PhoneNumber)
		:name{ Name }, 
		accountType{ accountTypee }, 
		balance{ Balance }, 
		accountId{ AccountId }, 
		phoneNumber{ PhoneNumber }
	{
	
	}

};

vector<customer> customersData;
class admin
{
public:
	void createAccount()
	{
		string name;
		int accountId, accountType , phoneNumber;
		float balance;

		cout << "Name: ";
		cin >> name;
		cout << "Phone number : " ;
		cin >> phoneNumber;
		cout << "Account ID: ";
		cin >> accountId;
		cout << "Account Type:  " << endl;
		cout << "1- Current Account" << endl;
		cout << "2- Saving Account" << endl;
		cin >> accountType;
		while (accountType != 1 )
		{
			if (accountType == 2)
			{
				break;
			}
			cout << "Please enter a valid account type!" << endl;
			cout << "1- Current Account" << endl;
			cout << "2- Saving Account" << endl;
			cin >> accountType;
		}
		cout << "Balance: " ;
		cin >> balance;

		customer customers(name, accountType,balance,accountId,phoneNumber);
		customersData.push_back(customers);
	}

	int deleteAccount(int accountId)
	{
		cout << "Please enter the accound ID: ";
		cin >> accountId;
		for (int i = 0; i < customersData.size(); i++)
		{
			if (customersData[i].accountId == accountId)
			{
				customersData.erase(customersData.begin()+i);
				return 1;
			}
		}
		return 0;
	}

	int transfer(int value, int from, int to)
	{
		cout << "Sender account ID: ";
		cin >> from;
		cout << "Reciever account ID: ";
		cin >> to; 
		if (from == to)
		{
			cout << "You can't transfer to money to yourself, Sorry." << endl;
			return 4;
		}
		cout << "Amount to transfer:  ";
		cin >> value; 

		bool fromFound = false; 
		int fromIdx = -1;
		bool toFound = false;
		int toIdx = -1;

		for (int i = 0; i < customersData.size(); i++)
		if (customersData[i].accountId == from )
		{
			fromFound = true;
			fromIdx = i;
		}
		else if (customersData[i].accountId == to )
		{
			toFound = true;
			toIdx = i;
		}

		if (fromFound == true && toFound == true)
		{
			if (customersData[fromIdx].balance >= value)
			{
				customersData[fromIdx].balance -= value;
				customersData[toIdx].balance += value;
				cout << "The money has been transfered successfully!" << endl;
				return 1;
			}
			else
			{
				cout << "There is not enough money in the Sender's account!" << endl;
				return 5;
			}

		}
		else if (fromFound == false && toFound == true)
		{
			cout << "Sender's account ID is wrong!" << endl;
			return 2;
		}
		else if (fromFound == true && toFound == false)
		{
			cout << "Reciever's account ID is wrong!" << endl;
			return 3;
		}
		else if (fromFound == false && toFound == false)
		{
			cout << "Sender and reciever accounts are wrong!" << endl;
			return 0;
		}
	}
};

class menu 
{
public:
	int menuAns;
	admin ad;
	int adminAns;
	int custAns;
	int custIdx;
	bool custFound = false;


void menuLoop()
{

	cout << "Role: \n 1- Customer                2- Admin" << endl;
	cin >> menuAns;
	if (menuAns == 1 && customersData.empty() == true)
	{
		cout << "There are no customers attached to the system yet, please enter as an admin and create an account." << endl;
		cout << "========================================================================" << endl;
		menuLoop();
	}
	else if (menuAns == 1 && customersData.empty() == false)
	{
		cout << "========================================================================" << endl;
		customerLoop();
	}
	else if (menuAns == 2)
	{
		adminLoop();
	}
	else
	{
		cout << "Please enter a valid code!" << endl;
		menuLoop();
	}

}

void adminLoop()
{
	
	cout << "========================================================================" << endl;
	cout << "Choose the proccess: \n \n";
	cout << "1-Create Account   |  2-Delete Account  |   3-Transfer money from account to account  |   4-Back to role selection menu \n";
	cin >> adminAns;
	if (adminAns == 1)
	{
		cout << "========================================================================" << endl;
		ad.createAccount();
		adminLoop();
	}

	else if (adminAns == 2)
	{
		cout << "========================================================================" << endl;
		int res = ad.deleteAccount(1);
		if (res == 1)
		{
			cout << "Account deleted successfully!" << endl;
		}
		else
		{
			cout << "There is no account with this ID!" << endl;
		}
		adminLoop();
	}
	else if (adminAns == 3)
	{
		cout << "========================================================================" << endl;
		int res = ad.transfer(1,2,3);
		adminLoop();
	}
	else if (adminAns == 4)
	{
		cout << "========================================================================" << endl;
		menuLoop();
	}
	else
	{
		cout << "========================================================================" << endl;
		cout << "Please, enter a valid number" << endl; 
		adminLoop();
	}
}

void customerLoop()
{
	
	cout << "========================================================================" << endl;
	cout << "Please enter your account ID: ";
	cin >> custAns;
	for (int i = 0; i < customersData.size(); i++)
	{
		if (customersData[i].accountId == custAns)
		{
			custIdx = i;
			custFound = true;
			break;
		}
	}
	if (custFound == false)
	{
		cout << "========================================================================" << endl;
		cout << "This account ID isn't on our system, please enter a valid ID" << endl;
		customerLoop();
	}
	else
	{
		cout << "========================================================================" << endl;
		int process;
		cout << "What process you want to procced:" << endl;
		cout << "1- Withdraw   |   2- Deposit   |   3- Update info   |  4- Display account info   | 5- Back to role selection menu" << endl;
		cin >> process;
		if (process == 1)
		{
			cout << "========================================================================" << endl;
			customersData[custIdx].withdraw(1);
			cout << endl;
			custAns = -1;
			custIdx = -1;
			custFound = false;
			customerLoop();
		}
		else if (process == 2)
		{
			cout << "========================================================================" << endl;
			customersData[custIdx].deposit(1);
			cout << endl;
			custAns = -1;
			custIdx = -1;
			custFound = false;
			customerLoop();
		}
		else if (process == 3)
		{
			cout << "========================================================================" << endl;
			customersData[custIdx].update(1,"a",1,1);
			cout << endl;
			custAns = -1;
			custIdx = -1;
			custFound = false;
			customerLoop();
		}
		else if (process == 4)
		{
			cout << "========================================================================" << endl;
			customersData[custIdx].displayInfo();
			cout << endl;
			custAns = -1;
			custIdx = -1;
			custFound = false;
			customerLoop();
		}
		else if (process == 5)
		{
			cout << "========================================================================" << endl;
			custAns = -1;
			custIdx = -1;
			custFound = false;
			menuLoop();
		}
		else
		{
			cout << "========================================================================" << endl;
			cout << "Please enter a valid code!" << endl;
			customerLoop();
		}

	}
}
};


void main ()
{
	menu men;
	men.menuLoop();
	system("pause");
}