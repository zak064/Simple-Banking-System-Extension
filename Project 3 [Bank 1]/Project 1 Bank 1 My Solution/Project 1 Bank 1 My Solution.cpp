// Project 1 Bank 1 My Solution.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//



#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;
#include "MyClientLib.h"
using namespace MyClientLib;



enum enChoices { ShowClientList = 1, AddNewClient = 2, DeleteClient = 3, UpdateClientInfo = 4, FindClient = 5, EXIT = 6 };

void ShowMainMenueScreen()
{

	cout << "=========================================\n";
	cout << "            Main Menue Screen             \n";
	cout << "=========================================\n";
	cout << "[1] Show Client List.\n";
	cout << "[2] Add New Client.\n";
	cout << "[3] Delete Client.\n";
	cout << "[4] Update Client Info.\n";
	cout << "[5] Find Client.\n";
	cout << "[6] Exit.\n";
	cout << "=========================================\n";
	cout << "Choose what do you want to do? [1 to 6]? ";

}
void ShowChoiceHeader(enChoices Choice)
{

	switch (Choice)
	{
	case ShowClientList:
		break;
	case AddNewClient:
		cout << "-----------------------------------------\n	    Add New Client Screen\n-----------------------------------------\n\n\n";
		break;
	case DeleteClient:
		cout << "-----------------------------------------\n	    Delete Client Screen\n-----------------------------------------\n\n\n";
		break;
	case UpdateClientInfo:
		cout << "-----------------------------------------\n	    Update Info Client Screen\n-----------------------------------------\n\n\n";
		break;
	case FindClient:
		cout << "-----------------------------------------\n	    Find Client Screen\n-----------------------------------------\n\n\n";
		break;
	default:
		break;
	}

}

void MainMenueChoices(enChoices Choice, vector<sClientInfo>& vClients)
{
	sClientInfo Client;
	string AccountNumber;
	switch (Choice)
	{
	case ShowClientList:
		PrintAllClientsData(vClients);
		break;
	case AddNewClient:
		ShowChoiceHeader(Choice);
		AddClients(Client, vClients);
		break;
	case DeleteClient:
		ShowChoiceHeader(Choice);
		AccountNumber = ReadString("Please Enter AccountNumber? ");
		DeleteClientByAccountNumber(AccountNumber, vClients);
		break;
	case UpdateClientInfo:
		ShowChoiceHeader(Choice);

		AccountNumber = ReadString("Please Enter AccountNumber? ");
		UpdateClientByAccountNumber(AccountNumber, vClients);
		break;
	case FindClient:
		ShowChoiceHeader(Choice);

		AccountNumber = ReadString("Please Enter AccountNumber? ");
		if (FindClientAccountNumber(AccountNumber, vClients, Client))
		{
			PrintClientCard(Client);
		}
		else
		{
			cout << "\nClient with Account Number [" << AccountNumber << "] is not found!";
		}
		break;
	default:
		break;
	}
}

void MainMenueScreen(vector<sClientInfo>& vClients)
{
	int Choice = 0;
	do
	{
		vector <sClientInfo> vClients = LoadClientsDataFormFile(ClientsFileName);
		ShowMainMenueScreen();
		cin >> Choice;
		system("cls");
		MainMenueChoices((enChoices)Choice, vClients);
		if (Choice == 6)
		{
			break;
		}

		cout << "\n\n\nPress Any Key to go back to Main Menue...";
		system("pause");
		system("cls");

	} while (Choice != 6);
	cout << "-----------------------------------------\n	    Program ends:)\n-----------------------------------------\n\n\n";
}
int main()
{
	// 1️⃣ Name lesen
	vector <sClientInfo> vClients = LoadClientsDataFormFile(ClientsFileName);
	
	MainMenueScreen(vClients);

	return 0;
}
