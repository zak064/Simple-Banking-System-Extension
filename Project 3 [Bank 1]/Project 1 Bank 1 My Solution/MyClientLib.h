
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

const string ClientsFileName = "Clients.txt";


namespace MyClientLib
{

	struct sClientInfo
	{
		string AccountNumber;
		string PIN;
		string Name;
		string PhoneNumber;
		double AccountBalance = 0.0;
		bool MarkForDelete = false;
	};

	// Read a full line string from user input
	string ReadString(string Message)
	{
		string str = "";

		cout << Message ;
		getline(cin >> ws, str);

		return str;
	}

	// Reads new client data from user input and returns it as a struct
	bool FindClientAccountNumber(string AccountNumber, vector<sClientInfo>& vClients, sClientInfo& Client);
	sClientInfo ReadNewClientInfo(sClientInfo& Client, vector<sClientInfo>& vClients)
	{
		Client.AccountNumber = ReadString("Enter Account Number? ");

		while (FindClientAccountNumber(Client.AccountNumber, vClients, Client))
		{
			cout << "Client with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
			Client.AccountNumber = ReadString("");
		}
		cout << "\nEnter PinCode? ";
		getline(cin, Client.PIN);

		cout << "\nEnter Name? ";		getline(cin, Client.Name);

		cout << "\nEnter Phone? ";
		getline(cin, Client.PhoneNumber);

		cout << "\nEnter AccountBalance? ";
		cin >> Client.AccountBalance;

		return Client;
	}
	
	// AddNewClients
	void Add_New_Client(sClientInfo Client, vector<sClientInfo>& vClients);
	void AddClients(sClientInfo& Client, vector<sClientInfo>& vClients)
	{
		char AddMore = 'n';
		cout << "Adding New Client: \n\n";
		do
		{
			Add_New_Client(Client, vClients);
			cout << "Client Added Successfully, do You Want to add more Clients? Y/N?";
			cin >> AddMore;

		} while (toupper(AddMore) == 'Y');
	}
	// Converts a client record (struct) into a string line separated by a delimiter
	string ConvertRecordToLine(sClientInfo& ClientInfo, string Dilem = "#//#")
	{
		string Text = "";

		Text += ClientInfo.AccountNumber + Dilem;
		Text += ClientInfo.PIN + Dilem;
		Text += ClientInfo.Name + Dilem;
		Text += ClientInfo.PhoneNumber + Dilem;
		Text += to_string(ClientInfo.AccountBalance);

		return Text;
	}

	// Splits a string into multiple parts stored in a vector using a given delimiter
	vector<string> SplitvString(string St1, string delim)
	{
		vector <string> vString;
		short Pos = 0;
		string sWord = "";
		while ((Pos = St1.find(delim)) != string::npos)
		{
			sWord = St1.substr(0, Pos);
			if (sWord != "")
			{
				vString.push_back(sWord);
			}
			St1.erase(0, Pos + delim.length());
		}
		if (St1 != "")
		{
			vString.push_back(St1);
		}
		return vString;
	}

	// Converts a line of text from file into a client record (struct)
	sClientInfo ConvertLineToRecord(string strClientInfoLine, string Seperator = "#//#")
	{
		sClientInfo Client;
		vector<string>vClientData;

		vClientData = SplitvString(strClientInfoLine, Seperator);

		Client.AccountNumber = vClientData[0];
		Client.PIN = vClientData[1];
		Client.Name = vClientData[2];
		Client.PhoneNumber = vClientData[3];
		Client.AccountBalance = stod(vClientData[4]);

		return Client;
	}

	// Prints a single client record in formatted style
	void PrintClientRecord(sClientInfo& ClientInfo)
	{
		cout << "\nThe following is extracted client record\n\n";

		cout << setw(17) << "AccountNumber   : " << ClientInfo.AccountNumber << endl;
		cout << setw(17) << "pin Code        : " << ClientInfo.PIN << endl;
		cout << setw(17) << "Name            : " << ClientInfo.Name << endl;
		cout << setw(17) << "Phone           : " << ClientInfo.PhoneNumber << endl;
		cout << setw(17) << "Account Balance : " << ClientInfo.AccountBalance << endl;

	}
	void PrintClientRecordToList(sClientInfo& ClientInfo)
	{
		cout << "| " << left << setw(15) << ClientInfo.AccountNumber;
		cout << "| " << left << setw(10) << ClientInfo.PIN;
		cout << "| " << left << setw(30) << ClientInfo.Name;
		cout << "| " << left << setw(12) << ClientInfo.PhoneNumber;
		cout << "| " << left << setw(12) << ClientInfo.AccountBalance;

	}

	// Saves a single client data line into the file (append mode)
	void SaveClientDataToFile(string FileName, string stDataLine)
	{
		fstream MyFile;

		MyFile.open(FileName, ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	// Saves all clients from vector into the file (skips those marked for delete)
	void SaveClientsDataToFile(string FileName, vector<sClientInfo>& vClients)
	{
		fstream MyFile;

		MyFile.open(FileName, ios::out);

		if (MyFile.is_open())
		{
			for (sClientInfo& C : vClients)
			{
				string DataLine = "";
				if (C.MarkForDelete == false)
				{
					DataLine = ConvertRecordToLine(C);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}

	}

	// Adds a new client by reading input and saving it to file
	void Add_New_Client(sClientInfo Client, vector<sClientInfo>& vClients)
	{
		Client = ReadNewClientInfo(Client, vClients);
		SaveClientDataToFile(ClientsFileName, ConvertRecordToLine(Client));
	}

	

	// Loads all client data from file into a vector
	vector<sClientInfo> LoadClientsDataFormFile(string FileName)
	{


		vector<sClientInfo> vClients;

		fstream MyFile;

		MyFile.open(FileName, ios::in);


		if (MyFile.is_open())
		{
			string Line = "";
			sClientInfo Client;

			while (getline(MyFile, Line))
			{

				Client = ConvertLineToRecord(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}

		return vClients;
	}

	// Prints all clients stored in the vector in table-like format
	void PrintAllClientsData(vector<sClientInfo>& vClients)
	{
		cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n\n";
		cout << "----------------------------------------------------------------------------------------------------------------\n\n";
		cout << "| " << left << setw(15) << "Account Number ";
		cout << "| " << left << setw(10) << "Pin Code ";
		cout << "| " << left << setw(40) << "Client Name ";
		cout << "| " << left << setw(12) << "Phone ";
		cout << "| " << left << setw(8) << "Balance Account ";
		cout << "\n\n----------------------------------------------------------------------------------------------------------------\n\n";


		for (sClientInfo Client : vClients)
		{
			PrintClientRecordToList(Client);
			cout << endl;
		}
		cout << "\n\n----------------------------------------------------------------------------------------------------------------\n\n";
	}

	// Prints client details in card style format
	void PrintClientCard(sClientInfo& ClientInfo)
	{
		cout << "\nThe following are the client details:\n\n";

		cout << setw(17) << "AccountNumber   : " << ClientInfo.AccountNumber << endl;
		cout << setw(17) << "pin Code        : " << ClientInfo.PIN << endl;
		cout << setw(17) << "Name            : " << ClientInfo.Name << endl;
		cout << setw(17) << "Phone           : " << ClientInfo.PhoneNumber << endl;
		cout << setw(17) << "Account Balance : " << ClientInfo.AccountBalance << endl;

	}

	// Reads account number input from user
	string ReadClientAccountNumber()
	{
		string AccountNumber = "";

		cout << "\nPlease enter an account number ?";
		cin >> AccountNumber;

		return AccountNumber;
	}

	// Finds a client by account number and returns it if found
	bool FindClientAccountNumber(string AccountNumber, vector<sClientInfo>& vClients, sClientInfo& Client)
	{

		for (sClientInfo& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				Client = C;
				return true;
			}
		}

		return false;
	}

	// Marks a client for deletion by account number
	bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClientInfo>& vClients)
	{
		for (sClientInfo& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.MarkForDelete = true;
				return true;
			}
		}
		return false;
	}

	// Deletes a client by account number after confirmation
	bool DeleteClientByAccountNumber(string AccountNumber, vector<sClientInfo>& vClients)
	{
		sClientInfo Client;
		char Answer = 'n';

		if (FindClientAccountNumber(AccountNumber, vClients, Client))
		{
			PrintClientCard(Client);


			cout << "\nAre you sure that you want to delete this Client? Y/N?";
			cin >> Answer;

			if (Answer == 'y' || Answer == 'Y')
			{

				MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
				SaveClientsDataToFile(ClientsFileName, vClients);

				vClients = LoadClientsDataFormFile(ClientsFileName);

				cout << "\nClient deleted Successfully\n";

				return true;
			}
			else
			{
				cout << "\nClient was not deleted.\n";
			}
		}
		else
		{
			cout << "\nClient with Account Number (" << AccountNumber << ") is Not found !\n\n";
		}
		return false;
	}

	// Reads new client data to update an existing client record
	sClientInfo ChangeClientRecord(string AccountNumber)
	{
		sClientInfo ClientInfo;

		ClientInfo.AccountNumber = AccountNumber;

		cout << "\nEnter PinCode?";
		getline(cin >> ws, ClientInfo.PIN);

		cout << "\nEnter Name?";
		getline(cin, ClientInfo.Name);

		cout << "\nEnter Phone?";
		getline(cin, ClientInfo.PhoneNumber);

		cout << "\nEnter AccountBalance?";
		cin >> ClientInfo.AccountBalance;


		return ClientInfo;

	}

	// Updates a client record by account number after confirmation
	bool UpdateClientByAccountNumber(string AccountNumber, vector<sClientInfo>& vClients)
	{
		sClientInfo Client;
		char Answer = 'n';

		if (FindClientAccountNumber(AccountNumber, vClients, Client))
		{
			PrintClientCard(Client);

			cout << "\nAre you sure that you want to update this Client? (Y or N)?";
			cin >> Answer;

			if (Answer == 'y' || Answer == 'Y')
			{

				for (sClientInfo& C : vClients)
				{
					if (C.AccountNumber == AccountNumber)
					{
						C = ChangeClientRecord(AccountNumber);
						break;
					}
				}

				SaveClientsDataToFile(ClientsFileName, vClients);

				cout << "\nClient Updated Successfully\n";
				return true;
			}
			else
			{
				cout << "\nClient was not Updated.\n";
				return false;
			}

		}
		else
		{
			cout << "\nClient with Account Number (" << AccountNumber << ") is Not found !\n\n";
			return false;
		}


	}


}

