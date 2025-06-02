#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<cmath>
#include<vector>
#include<iterator>
#include<limits>

using namespace std;

//client details 
struct stClient
{
	string AccountNumber = "A1";
	string FullName = "Mostafa Ismaiel Gad";
	string NationalID = "12345678901234";
	string Gender = "Mal";
	string PhoneNumber = "01060341967";
	double Blanc = 50500;

	int index;
	bool DeletFlag = false;
};

enum enGender
{
	Male = 1,
	Female = 2
};

char ReadChois(string Messag)
{
	char x = 'x';
	cout << Messag;
	cin >> x;
	return x;
}

string ReadString(string Messag)
{
	string str = "No String [X]";
	cout << Messag;
	getline(cin >> ws, str);
	return str;
}

int ReadNumber(string Messag)
{
	int Number = 0;
	cout << Messag;
	cin >> Number;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Please Enter Valid Number, " << Messag;
		cin >> Number;
	}
	return Number;
}

//Gender Function
enGender GetGender(string Messag)
{
	short GenderChois;
	cout << Messag;
	cin >> GenderChois;

	while (cin.fail() || GenderChois < 0 || GenderChois>2)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Please Enter Valid Choise ," << Messag;
		cin >> GenderChois;
	}
	return enGender(GenderChois);
}

string ReadGender(enGender Gender)
{

	switch (Gender)
	{
	case enGender::Male:
		return "Male";
		break;

	case enGender::Female:
		return "Female";
		break;

	default:
		break;
	}


}

//Client Function
stClient ReadClient()
{
	stClient Client;

	cout << "=============================================\n";
	cout << "\t\tAdd Client \n";
	cout << "=============================================\n\n";

	Client.AccountNumber = ReadString("Enter Account Number :");
	Client.FullName = ReadString("Enter Full Name :");
	Client.NationalID = ReadString("Enter National ID :");
	Client.Gender = ReadGender(GetGender(" 1- Male\t2- Female\nEnter Chois : "));
	Client.PhoneNumber = ReadString("Enter Phone Number :");
	Client.Blanc = ReadNumber("Enter Blance :");

	return Client;

}

void PrintClient(stClient Client)
{
	cout << "Account Number :" << Client.AccountNumber << endl;
	cout << "Full Name      :" << Client.FullName << endl;
	cout << "National ID    :" << Client.NationalID << endl;
	cout << "Gender         :" << Client.Gender << endl;
	cout << "Phone Number   :" << Client.PhoneNumber << endl;
	cout << "Balance        :" << Client.Blanc << endl;

}

//Convert Record To Line & Add  Function
string ConvertRecordToLine(stClient Client, string Sperator = "#///#")
{
	string line = " ";

	line += Client.AccountNumber + Sperator;
	line += Client.FullName + Sperator;
	line += Client.NationalID + Sperator;
	line += Client.Gender + Sperator;
	line += Client.PhoneNumber + Sperator;
	line += to_string(Client.Blanc) + Sperator;

	return line;
}

void AddNewClient(string FileName, string Sperator = "#///#")
{
	stClient client = ReadClient();
	string line = ConvertRecordToLine(client, Sperator);

	fstream add;
	add.open(FileName, ios::out | ios::app);

	if (add.is_open())
	{
		add << line << endl;
		add.close();
	}
	else
	{
		cout << "File Not Open !!! \n";
	}



}


//Convert Line To Record Function
vector<string> SplitLineToWords(string line, string Sperator = "#///#")
{
	vector<string>vWords;
	string word;
	short pos = 0;

	while ((pos = line.find(Sperator)) != string::npos)
	{
		word = line.substr(0, pos);

		if (!word.empty())
		{
			vWords.push_back(word);
		}
		line.erase(0, pos + Sperator.length());
	}
	if (!line.empty())
	{
		vWords.push_back(line);
	}

	return vWords;
}

stClient ConvertLineToRecord(string line, string Sperator = "#///#")
{
	stClient client;
	vector<string>vWords = SplitLineToWords(line, Sperator);

	client.AccountNumber = vWords[0];
	client.FullName = vWords[1];
	client.NationalID = vWords[2];
	client.Gender = vWords[3];
	client.PhoneNumber = vWords[4];
	client.Blanc = stod(vWords[5]);

	return client;

}

vector<stClient> LoadClientsFromFile(string FileName, string Sperator = "#///#")
{
	vector<stClient>vClients;
	stClient client;
	string line;

	fstream load;

	load.open(FileName, ios::in);
	if (load.is_open())
	{
		while (getline(load >> ws, line))
		{
			if (!line.empty())
			{
				client = ConvertLineToRecord(line, Sperator);
				vClients.push_back(client);
			}
		}
		load.close();
	}

	return vClients;
}


//Print Clients Function 
void HeaderClientTable()
{
	// Account Number    FullName     National ID     Gender    Phone Number      Balance 

	cout << "\n____________________________________________________";
	cout << "____________________________________________________\n";
	cout << left << setw(15) << "|Account Number ";
	cout << left << setw(40) << "|Full Name ";
	cout << left << setw(16) << "|National ID ";
	cout << left << setw(10) << "|Gender ";
	cout << left << setw(15) << "|Phone Number ";
	cout << left << setw(10) << "|Balance |";
	cout << "\n____________________________________________________";
	cout << "____________________________________________________\n";
}

void PrintOneClient(stClient client)
{
	cout << "|" << left << setw(15) << client.AccountNumber;
	cout << "|" << left << setw(39) << client.FullName;
	cout << "|" << left << setw(15) << client.NationalID;
	cout << "|" << left << setw(9) << client.Gender;
	cout << "|0" << left << setw(14) << client.PhoneNumber;
	cout << "|" << left << setw(10) << client.Blanc;

	cout << "\n----------------------------------------------------";
	cout << "----------------------------------------------------\n";

}

void PrintClientsData(string FileName, string Sperator = "#///#")
{
	vector<stClient>vClients = LoadClientsFromFile(FileName, Sperator);

	cout << "\n\t\t\t\t\tWe Have(" << vClients.size() << ") Clients\n";

	HeaderClientTable();

	for (stClient& i : vClients)
	{
		PrintOneClient(i);
	}

}


//Delete Function

int GetIndexByAccountName(vector<stClient>vClients, stClient& client, string accountNumber)
{
	for (size_t i = 0; i < vClients.size(); i++)
	{
		if (vClients[i].AccountNumber == accountNumber)
		{
			client = vClients[i];
			client.DeletFlag = true;
			return i;
		}
	}
	return -1;
}

void DeleteClientFromFile(string FileName, string Sperator = "#///#")
{
	cout << "=============================================\n";
	cout << "\t\tDelete Client By Account Number  \n";
	cout << "=============================================\n\n";
	vector<stClient>vClients = LoadClientsFromFile(FileName, Sperator);
	vector<stClient>::iterator ite;

	string line;
	stClient client;
	char Delete = 'n';

	int index = GetIndexByAccountName(vClients, client, ReadString("\nEnter Account Number To Delet It :"));
	PrintClient(vClients[index]);
	Delete = ReadChois("\n\tWARNNING --->  Are you sure for delete this client ? [ Y / N ] :");

	if (Delete == 'y' || Delete == 'Y')
	{
		ite = vClients.begin() + index;
		vClients.erase(ite);

		fstream Add;
		Add.open(FileName, ios::out);
		if (Add.is_open())
		{
			for (stClient& Client : vClients)
			{
				line = ConvertRecordToLine(Client, Sperator);
				Add << line << endl;
			}
		}
		else
		{
			cout << "\n\tWARNING ---> File Not Working !!!\n";
		}


	}
	else
	{
		cout << "\n\tNo Action On This Account Number ( " << vClients[index].AccountNumber << " )\n";
	}

}



//Update Function

stClient ReadClientForUpdat(string accountNumber)
{
	stClient Client;

	cout << "=============================================\n";
	cout << "\t\tUpdate Client \n";
	cout << "=============================================\n\n";
	Client.AccountNumber = accountNumber;
	Client.FullName = ReadString("Enter Full Name :");
	Client.NationalID = ReadString("Enter National ID :");
	Client.Gender = ReadGender(GetGender(" 1- Male\t2- Female\nEnter Chois : "));
	Client.PhoneNumber = ReadString("Enter Phone Number :");
	Client.Blanc = ReadNumber("Enter Blance :");

	return Client;

}

void UpdateClientInFile(string FileName, string Sperator = "#///#")
{
	cout << "=============================================\n";
	cout << "\t\tUpdate Client By Account Number  \n";
	cout << "=============================================\n\n";
	vector<stClient>vClients = LoadClientsFromFile(FileName, Sperator);
	stClient client;
	string line;
	char updat = 'n';

	int index = GetIndexByAccountName(vClients, client, ReadString("Enter Account Number To Updat it :"));
	PrintClient(client);
	client = ReadClientForUpdat(vClients[index].AccountNumber);
	updat = ReadChois("\n\tWARNING  ---> Are you sure for updat this Client [ Y / N ]  :");
	if (updat == 'y' || updat == 'Y')
	{
		vClients[index] = client;

		fstream Add;
		Add.open(FileName, ios::out);
		if (Add.is_open())
		{
			for (auto& client : vClients)
			{
				line = ConvertRecordToLine(client, Sperator);
				Add << line << endl;
			}

			Add.close();
			cout << "\n\tYour client has been successfully updated\n";
		}
		else
		{
			cout << "\n\tWARNING ---> File Not Working !!!\n";
		}



	}
	else
	{
		cout << "\n\tNo Action On This Account Number ( " << vClients[index].AccountNumber << " )\n";
	}

}

// Find Client 
void FindClientInFile(string FileName, string Sperator = "#///#")
{
	cout << "=============================================\n";
	cout << "\t\tFind Client By Account Number  \n";
	cout << "=============================================\n\n";
	vector<stClient>vClients = LoadClientsFromFile(FileName, Sperator);
	stClient client;
	int index = GetIndexByAccountName(vClients, client, ReadString("Enter Account Number To Show Client Data :"));

	if (index >= 0)
	{
		PrintClient(client);
	}
	else
	{
		cout << "\n Client Not Found ERORE 404 !!!\n";
	}
}


// transaction 


void DepositFunction(string FileName, string Sperator = "#///#")
{
	cout << "=============================================\n";
	cout << "\t\tDeposit Balance  \n";
	cout << "=============================================\n\n";

	vector<stClient>vClients = LoadClientsFromFile(FileName, Sperator);
	stClient client;
	char deposit = 'n';

	int index = GetIndexByAccountName(vClients, client, ReadString("Enter Account Number For Deposite :"));
	PrintClient(client);

	double Depo = ReadNumber("\n Enter The Dposit :");
	client.Blanc += Depo;


	deposit = ReadChois(" WARNNING  ---> Are you sure about this deposte ? [ Y / N ] :");

	if (deposit == 'Y' || deposit == 'y')
	{
		vClients[index] = client;
		fstream Add;
		string line;
		Add.open(FileName, ios::out);

		if (Add.is_open())
		{
			for (stClient& Client : vClients)
			{
				line = ConvertRecordToLine(Client, Sperator);
				Add << line << endl;
			}

			Add.close();
		}
		else
		{
			cout << "\n WARNNING --->  File Not Work !!!!\n";
		}

	}
	else
	{
		cout << "\nNo Action about this operation \n";
	}

}

void WithdrawFunction(string FileName, string Sperator = "#///#")
{
	cout << "=============================================\n";
	cout << "\t\tWithdraw Balance  \n";
	cout << "=============================================\n\n";

	vector<stClient>vClients = LoadClientsFromFile(FileName, Sperator);
	stClient client;
	char withdraw = 'n';

	int index = GetIndexByAccountName(vClients, client, ReadString("Enter Account Number For Withdraw :"));
	PrintClient(client);

	double Withdr = ReadNumber("\n Enter The Withdraw :");

	client.Blanc -= Withdr;

	withdraw = ReadChois(" WARNNING  ---> Are you sure about this Withdraw ? [ Y / N ] :");

	if (withdraw == 'Y' || withdraw == 'y')
	{
		vClients[index] = client;
		fstream Add;
		string line;
		Add.open(FileName, ios::out);

		if (Add.is_open())
		{
			for (stClient& Client : vClients)
			{
				line = ConvertRecordToLine(Client, Sperator);
				Add << line << endl;
			}

			Add.close();
		}
		else
		{
			cout << "\n WARNNING --->  File Not Work !!!!\n";
		}

	}
	else
	{
		cout << "\nNo Action about this operation \n";
	}
}

void TotalBalance(string FileName, string Sperator = "#///#")
{
	vector<stClient>vClients = LoadClientsFromFile(FileName, Sperator);
	double total = 0;

	for (stClient& i : vClients)
	{
		total += i.Blanc;
	}

	cout << "\n\t\t\t\t\tTotal Balance = " << total << "\n";

}

void TransactionMenu(string FileName, string Sperator);

void MainMenu(string FileName, string Sperator = "#///#")
{

	cout << "=============================================\n";
	cout << "\t\t Main Menu Table  \n";
	cout << "=============================================\n\n";

	cout << " [1] Add Client \n";
	cout << " [2] Show Clients List\n";
	cout << " [3] Delete Client \n";
	cout << " [4] Update Client \n";
	cout << " [5] Find Client\n";
	cout << " [6] Transaction\n";
	cout << " [7] Exit\n";

	short index = ReadNumber("\n Enter Choise :");

	switch (index)
	{
	case 1:
		system("cls");
		AddNewClient(FileName, Sperator);
		cout << " \n";
		system("Pause");
		system("cls");
		MainMenu(FileName, Sperator);
		break;
	case 2:
		system("cls");
		PrintClientsData(FileName, Sperator);
		cout << " \n";
		system("Pause");
		system("cls");
		MainMenu(FileName, Sperator);
		break;
	case 3:
		system("cls");
		DeleteClientFromFile(FileName, Sperator);
		cout << " \n";
		system("Pause");
		system("cls");
		MainMenu(FileName, Sperator);
		break;
	case 4:
		system("cls");
		UpdateClientInFile(FileName, Sperator);
		cout << " \n";
		system("Pause");
		system("cls");
		MainMenu(FileName, Sperator);
		break;
	case 5:
		system("cls");
		FindClientInFile(FileName, Sperator);
		cout << " \n";
		system("Pause");
		system("cls");
		MainMenu(FileName, Sperator);
		break;
	case 6:
		system("cls");
		TransactionMenu(FileName, Sperator);
		break;
		system("cls");
	case 7:
		break;
	default:
		break;
	}




}

int main()
{


	MainMenu("User1");


	return 0;
}
void TransactionMenu(string FileName, string Sperator = "#///#")
{
	cout << "=============================================\n";
	cout << "\t\t Transsaction Menu  \n";
	cout << "=============================================\n\n";

	cout << " [1] Deposite Balance \n";
	cout << " [2] Withdraw Balance \n";
	cout << " [3] Tottal Balance \n";
	cout << " [4] Go To Main Menu Table \n";

	short Choise = ReadNumber(" \nEnter Choise :");

	switch (Choise)
	{
	case 1:
		system("cls");
		DepositFunction(FileName, Sperator);
		cout << " \n";
		system("Pause");
		system("cls");
		TransactionMenu(FileName, Sperator);
		break;
	case 2:
		system("cls");
		WithdrawFunction(FileName, Sperator);
		cout << " \n";
		system("Pause");
		system("cls");
		TransactionMenu(FileName, Sperator);
		break;
	case 3:
		system("cls");
		PrintClientsData(FileName, Sperator);
		TotalBalance(FileName, Sperator);
		cout << "\n";
		system("Pause");
		system("cls");
		TransactionMenu(FileName, Sperator);
		break;
	case 4:
		system("cls");
		MainMenu(FileName, Sperator);
	default:
		break;
	}


}