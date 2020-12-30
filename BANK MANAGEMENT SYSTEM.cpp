#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
using namespace std;
class account
{
protected:
	int ac_no;
	string password;
	double amount;
	char name[40];
	int choice;
public:
	account()
	{
		ac_no = 0;
		password = "";
		amount = 0.0;
		name[40] = ' ';
	}
	/*account(int a, int p, double am,char n)
	{
		ac_no = a;
		password = p;
		amount = am;
		name[40] = n;
	}*/

	void newaccount()
	{
		cout << "Enter Account No: " << endl;
		cin >> ac_no;
		cout << "Enter Password: " << endl;
		cin >> password;
		cout << "Enter Account Holder Name:  " << endl;
		cin.ignore();
		cin.getline(name, 40);
		cout << "Deposite Initial Amount:  " << endl;
		cin >> amount;


	}
	void User_all_list()
	{

		cout << "\t" << ac_no << " \t" << name << "\t " << amount << endl;
		//cout << endl;

	}
	void withdraw(double draw)
	{
		amount -= draw;
	}
	void add_amount(double add)
	{
		amount += add;
	}
	string getname()
	{
		return name;
	}
	int getac_no()
	{
		return ac_no;
	}
	string getpassword()
	{
		return password;
	}
	double getamount()
	{
		return amount;
	}
	void display()
	{
		cout << "Account No:           " << ac_no << endl;
		cout << "Account Holder Name:  " << name << endl;
		cout << "Avaliable Balance:         " << amount << endl;
	}
	void Modifyaccount()
	{
		cout << "Account No: " << ac_no << endl;
		cout << "Account Holder Name:  " << endl;
		cin >> name;
		cout << "Deposited Amount:  " << endl;
		cin >> amount;
	}
};
//CREATE ACCOUNT===================================================
void addrecord()
{
	account a;
	ofstream fout;
	fout.open("Userlist", ios::binary | ios::app);
	a.newaccount();
	fout.write(reinterpret_cast<char*>(&a), sizeof(account));
	fout.close();
}
//DISPLAY ACCOUNT===================================================
void showrecord(int n)
{
	account a;
	bool flag = false;
	ifstream fin;
	if (!fin)
	{
		cout << "File not found\n";
	}
	fin.open("Userlist", ios::binary);
	cout << "\t\t\tACCOUNT DETAIL\n";
	while (fin.read(reinterpret_cast<char*>(&a), sizeof(account)))
	{
		if (a.getac_no() == n)
		{
			a.display();
			flag = true;
		}
	}
	fin.close();
	if (flag == false)
	{
		cout << "Invalid Account Number\n";
	}

}
//MODIFY ACCOUNT===================================================
void modifyrecord(int r)
{
	account a;
	bool flag = false;
	fstream f;
	f.open("Userlist", ios::in | ios::out);
	if (!f)
	{
		cout << "File Not Found\n";
	}
	while (!f.eof() && flag == false)
	{
		f.read(reinterpret_cast<char*>(&a), sizeof(account));
		if (a.getac_no() == r)
		{
			cout << "Enter new detail and update your account\n";
			a.Modifyaccount();
			int modify = (-1) * static_cast<int>(sizeof(account));
			f.seekp(modify, ios::cur);
			f.write(reinterpret_cast<char*>(&a), sizeof(account));
			cout << "Record Updated\n";
			flag = true;
		}
	}
	f.close();
	if (flag == false)
	{
		cout << "Record not found\n";

	}
}
//delete account================================================
void deleteaccount(int d)
{
	account a;
	ifstream fin;
	ofstream fout;
	fin.open("Userlist", ios::binary);
	if (!fin)
	{
		cout << "File not found\n";
	}
	fout.open("delete_userlist", ios::binary);
	fin.seekg(0, ios::beg);
	while (fin.read(reinterpret_cast<char*>(&a), sizeof(account)))
	{
		if (a.getac_no() != d)
		{
			fout.write(reinterpret_cast<char*>(&a), sizeof(account));
		}
	}
	fin.close();
	fout.close();
	remove("Userlist");
	rename("delete_userlist", "Userlist");
	cout << "Record Deleted\n";
}
//display all account record lists=========================================

void all_accountlist()
{
	account a;
	ifstream fin;
	fin.open("Userlist", ios::binary);
	if (!fin)
	{
		cout << "File could not be open";

	}
	cout << endl << endl;
	cout << endl;
	cout << "------------------------------------------------------\n";
	cout << "\t\tACCOUNT HOLDER LIST\n";
	cout << "------------------------------------------------------\n";
	cout << "\tAccount no.\t NAME \t  Avaliable Balance\n";
	cout << "------------------------------------------------------\n\n";
	while (fin.read(reinterpret_cast<char*> (&a), sizeof(account)))
	{

		a.User_all_list();

	}
	cout << "------------------------------------------------------\n";
	fin.close();
}
//depositamount============================================
void depositamount(int d)
{
	account a;
	int amount;
	bool flag = false;
	fstream f;
	f.open("Userlist", ios::binary | ios::in | ios::out);
	if (!f)
	{
		cout << "File could not be open,";

	}
	while (!f.eof() && flag == false)
	{
		f.read(reinterpret_cast<char*> (&a), sizeof(account));
		if (a.getac_no() == d)
		{
			a.display();
			cout << "-------------------------------------------------\n";
			cout << "\t\t DEPOSITE AMOUNT \n";
			cout << "-------------------------------------------------\n\n";
			cout << "\tEnter The amount to be deposited";
			cin >> amount;
			a.add_amount(amount);
		}
		int pos = (-1) * static_cast<int>(sizeof(a));
		f.seekp(pos, ios::cur);
		f.write(reinterpret_cast<char*> (&a), sizeof(account));
		cout << endl << endl;
		cout << "\t Record Updated!\n";
		flag = true;

	}

	f.close();
	if (flag == false)
		cout << "\n\n Record Not Found! ";
}

//drawamount========================================================
void drawamount(int n)
{
	int amount;
	bool found = false;
	account a;
	fstream f;
	f.open("Userlist", ios::binary | ios::in | ios::out);
	if (!f)
	{
		cout << "File not found\n";
	}
	while (!f.eof() && found == false)
	{
		f.read(reinterpret_cast<char*> (&a), sizeof(account));
		if (a.getac_no() == n)
		{
			a.display();



			cout << endl << endl;
			cout << "-------------------------------------------------------\n";
			cout << "\t\t WITHDRAW AMOUNT\n ";
			cout << "-------------------------------------------------------\n\n";
			cout << "\tEnter The Amount to  Withdraw: \n";
			cin >> amount;
			double draw = a.getamount() - amount;
			if ((draw < 500))
				cout << "Insufficience balance!";
			else
				a.withdraw(amount);

			int pos = (-1) * static_cast<int>(sizeof(a));
			f.seekp(pos, ios::cur);
			f.write(reinterpret_cast<char*> (&a), sizeof(account));
			cout << endl << endl;
			cout << "\t Record Updated!";
			found = true;
		}
	}
	f.close();
	cout << endl << endl;
	if (found == false)
		cout << "\t Record Not Found! ";
}
void start()
{
	cout << endl << endl;
	cout << "------------------------------------------------------\n";
	cout << "------------------------------------------------------\n";
	cout << "\t\t\t  BANK\n";
	cout << "\t\t\tMANAGEMENT\n";
	cout << "\t\t\t  SYSTEM\n";
	cout << "------------------------------------------------------\n";
	cout << "------------------------------------------------------\n";
	cout << endl << endl;
	cout << " KHADIJA NAZ\n 3333\n Bank Manager";
}
//login again===================================================
void showlogin(int n)
{
	account a;
	int choice, ac_no;
	bool flag = false;
	ifstream fin;
	if (!fin)
	{
		cout << "File not found\n";
	}
	fin.open("Userlist", ios::binary);
	cout << "\t\t\tACCOUNT DETAIL\n";
	while (fin.read(reinterpret_cast<char*>(&a), sizeof(account)))
	{
		if (a.getac_no() == n)
		{
			cout << "You have logedin successfully\n";
			a.display();
			flag = true;
			cout << endl << endl;

			cout << "----------------------------------------------------\n";
			cout << "\t\t\tMain Menu\n";
			cout << "----------------------------------------------------\n\n";
			cout << "\t\t1. Create New Account.\n";
			cout << "\t\t2.Account Detail\n";
			cout << "\t\t3. WithDraw Amount.\n";
			cout << "\t\t4. Deposit Amount.\n";
			cout << "\t\t5. Modify Account.\n";
			cout << "\t\t6. Account Holder List.\n";
			cout << "\t\t7. Delete Account.\n";
			cout << "\t\t8. Logout.\n";
			cin >> choice;
			system("cls");
			if (choice == 1)//cout << "1. Create New Account.\n";
			{
				addrecord();
			}
			else if (choice == 2)//cout << "2. Show Account Detail.\n";
			{
				cout << "\t\tEnter Account Number\n";
				cin >> ac_no;
				showrecord(ac_no);
			}
			else if (choice == 3)//cout << "3. WithDraw Amount.\n";
			{
				cout << "\t\tEnter Account Number\n";
				cin >> ac_no;
				drawamount(ac_no);
			}
			else if (choice == 4)//cout << "4. Deposit Amount.\n";
			{
				cout << "\t\tEnter Account Number\n";
				cin >> ac_no;
				depositamount(ac_no);
			}

			else if (choice == 5)//cout<<"5. Modify Account.\n";
			{
				cout << "\t\tEnter Account Number\n";
				cin >> ac_no;
				modifyrecord(ac_no);
			}
			else if (choice == 6)//cout << "6. Account Holder List.\n";
			{
				all_accountlist();
			}
			else if (choice == 7)//cout<<"7. Delete Account.\n";
			{
				cout << "\t\tEnter Account Number\n";
				cin >> ac_no;
				deleteaccount(ac_no);
			}
			else if (choice == 8)//cout<<"8. Delete Account.\n";
			{
				cout << "\t\tThanks For Using Bank Manegment System\n";
			}
		}
	}
	fin.close();
	if (flag == false)
	{
		cout << "Invalid Account Number or a Password\n";
	}

}
int main()
{
	int choice, press, ac_no;
	string pass;
	start();
	cout << endl << endl;
	cout << "\t\t1. Sign Up\n";
	cout << "\t\t2. Login\n";
	cin >> choice;
	if (choice == 1)
	{
		addrecord();
		cout << "Press 4 For Menu\n";
		cin >> press;
		system("cls");
		if (press == 4)
		{


			do {
				cout << endl << endl;
				cout << "----------------------------------------------------\n";
				cout << "\t\t\tMain Menu\n";
				cout << "----------------------------------------------------\n\n";
				cout << "\t\t1. Create New Account.\n";
				cout << "\t\t2. Account Detail\n";
				cout << "\t\t3. WithDraw Amount.\n";
				cout << "\t\t4. Deposit Amount.\n";
				cout << "\t\t5. Modify Account.\n";
				cout << "\t\t6. Account Holder List.\n";
				cout << "\t\t7. Delete Account.\n";
				cout << "\t\t8. Logout.\n";
				cin >> choice;
				system("cls");
				if (choice == 1)//cout << "1. Create New Account.\n";
				{
					addrecord();
				}
				else if (choice == 2)//cout << "2. Show Account Detail.\n";
				{
					cout << "\t\tEnter Account Number\n";
					cin >> ac_no;
					showrecord(ac_no);
				}
				else if (choice == 3)//cout << "3. WithDraw Amount.\n";
				{
					cout << "\t\tEnter Account Number\n";
					cin >> ac_no;
					drawamount(ac_no);
				}
				else if (choice == 4)//cout << "4. Deposit Amount.\n";
				{
					cout << "\t\tEnter Account Number\n";
					cin >> ac_no;
					depositamount(ac_no);
				}

				else if (choice == 5)//cout<<"5. Modify Account.\n";
				{
					cout << "\t\tEnter Account Number\n";
					cin >> ac_no;
					modifyrecord(ac_no);
				}
				else if (choice == 6)//cout << "6. Account Holder List.\n";
				{
					all_accountlist();
				}
				else if (choice == 7)//cout<<"7. Delete Account.\n";
				{
					cout << "\t\tEnter Account Number\n";
					cin >> ac_no;
					deleteaccount(ac_no);
				}
				else if (choice == 8)//cout<<"8. Delete Account.\n";
				{
					cout << "\t\tThanks For Using Bank Manegment System\n";
				}
			} while (choice != 8);
		}
		else
		{
			cout << "\t\tThanks For Using Bank Manegment System\n";
			cout << "\t\tPress any key to logout\n";
		}
	}


	if (choice == 2)
	{
		cout << "\t\tEnter Account Number\n";
		cin >> ac_no;
		cout << "\t\tEnter Password\n";
		cin >> pass;
		showlogin(ac_no);


	}
	system("pause");
}





