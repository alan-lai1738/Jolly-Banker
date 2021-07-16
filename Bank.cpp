/*
*
*
* Alan Lai
* 12/1/2020 - 12/10/2020
*
* Bank.cpp
*
* This is the implementation of Bank for the Jolly Banker.
* The Bank class reads a file and puts it into a queue. These transactions
* are executed and put into the tree.
*/
#include "Bank.h"
#include <iostream>
#include <string>
#include "AccountTree.h"
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

Bank::Bank()
{

}

Bank::~Bank()
{

}


void Bank::ReadTransactions(string fileName)
{
	ifstream in(fileName);
	string line;	// Line were reading
	if (!in)
	{
		cout << "Can't open file" << endl;
	}

	while (!in.eof())
	{
		vector<string> trans_parameters;
		getline(in, line);
		if (line.empty())
		{
			break;
		}
		istringstream parseLine(line);
		string trans_type;	// Transaction Type
		parseLine >> trans_type;	// First letter is the transaction type.

		if (trans_type == "O")
		{
			string first_name, last_name, account_id;
			parseLine >> first_name >> last_name >> account_id;
			trans_parameters.push_back(trans_type);
			trans_parameters.push_back(first_name);
			trans_parameters.push_back(last_name);
			trans_parameters.push_back(account_id);
			
		}
		else if (trans_type == "W" || trans_type == "D")
		{
			int account_id, fund_id, amount;
			parseLine >> account_id >> amount;
			fund_id = account_id % 10;	// The fund ID is the last digit of a 5 digit input
			account_id = account_id / 10;	// The Account ID is the first 4 digits, cut the 5th one off
			trans_parameters.push_back(trans_type);	// Push values into a vector to process later
			trans_parameters.push_back(to_string(account_id));
			trans_parameters.push_back(to_string(fund_id));
			trans_parameters.push_back(to_string(amount));
			
		}
		else if (trans_type == "T")
		{
			int account_id, fund_id, amount, destination_id, destination_fund;
			parseLine >> account_id >> amount >> destination_id;
			fund_id = account_id % 10;
			account_id = account_id / 10;
			destination_fund = destination_id % 10;
			destination_id = destination_id / 10;
			trans_parameters.push_back(trans_type);
			trans_parameters.push_back(to_string(account_id));
			trans_parameters.push_back(to_string(fund_id));
			trans_parameters.push_back(to_string(amount));
			trans_parameters.push_back(to_string(destination_id));
			trans_parameters.push_back(to_string(destination_fund));
			
		}
		else if (trans_type == "H")
		{
			int account_id;
			parseLine >> account_id;
			trans_parameters.push_back(trans_type);
			trans_parameters.push_back(to_string(account_id));
		}
		else
		{
			cerr << "---------------------------------------------------------------------------------------" << endl;
			cerr << "ERROR: Invalid input/type of transaction!" << endl;
		}
		transaction_queue_.push(trans_parameters);	// Insert into the Transaction Queue
	}
}


void Bank::ExecuteTransactions()
{
	vector<string> current;	// Current Transaction we are executing
	while (!transaction_queue_.empty())
	{
		current = transaction_queue_.front();	// Grab the top of the queue transaction
		if (current[0] == "O")
		{
			OpenAccount(stoi(current[3]), current[2], current[1]);
		}
		else if (current[0] == "D")
		{
			ExecuteDeposit(stoi(current[1]), stoi(current[2]), stoi(current[3]));
		}
		else if (current[0] == "W")
		{
			ExecuteWithdrawal(stoi(current[1]), stoi(current[2]), stoi(current[3]));
		}
		else if (current[0] == "T")
		{
			ExecuteTransfer(stoi(current[1]), stoi(current[4]), stoi(current[2]), stoi(current[5]), stoi(current[3]));
		}
		else if (current[0] == "H")
		{
			if (current[1].size() == 4)
			{
				DisplayHistory(stoi(current[1]), -1);
			}
			else
			{
				int account_id = stoi(current[1]) / 10;
				int fund_id = stoi(current[1]) % 10;
				DisplayHistory(account_id, fund_id);
			}
		}
		transaction_queue_.pop();	// Move on to the next transaction in queue.
	}
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "Processing Done. Printing final balances...";
}

void Bank::Display()
{
	cout << endl;
	bank_accounts_.Display();
}

bool Bank::OpenAccount(int account_id, string first_name, string last_name)
{
	if (account_id < 1000 || account_id > 9999)
	{
		cerr << "---------------------------------------------------------------------------------------" << endl;
		cerr << "ERROR: " << account_id << "is an Invalid account ID. Must be 1000-9999." << endl;
		return false;
	}
	Account* acc = new Account(account_id, first_name, last_name);
	if (bank_accounts_.Retrieve(account_id, acc))
	{
		cerr << "---------------------------------------------------------------------------------------" << endl;
		cerr << "ERROR: Can't open account. Account #" << account_id << " already exists." << endl;
		return false;
	}
	else
	{
		bank_accounts_.Insert(acc);
		return true;
	}
}


// Helper methods for deposit, withdrawal, transfer, etc
bool Bank::ExecuteDeposit(int account_id, int fund_id, int amount)
{
	Account* acc;
	if (bank_accounts_.Retrieve(account_id, acc))
	{
		acc->Deposit(fund_id, amount);
		return true;
	}
	else
	{
		cerr << "---------------------------------------------------------------------------------------" << endl;
		cerr << "ERROR: Deposit failed. Account #" << account_id << " does not exist!" << endl;
		return false;
	}
}

bool Bank::ExecuteWithdrawal(int account_id, int fund_id, int amount)
{
	Account* acc;
	if (bank_accounts_.Retrieve(account_id, acc))
	{
		acc->Withdraw(fund_id, amount);
		return true;
	}
	else
	{
		cerr << "---------------------------------------------------------------------------------------" << endl;
		cerr << "ERROR: Deposit failed. Account #" << account_id << " does not exist!" << endl;
		return false;
	}
}

bool Bank::ExecuteTransfer(int account_id, int destination_id, int fund_id, int target_fund, int amount)
{
	Account* sender;
	Account* reciever;

	if (!bank_accounts_.Retrieve(account_id, sender))
	{
		cerr << "---------------------------------------------------------------------------------------" << endl;
		cerr << "ERROR: Transfer failed. Account #" << account_id << " does not exist!" << endl;
		return false;
	}
	if (!bank_accounts_.Retrieve(destination_id, reciever))
	{
		cerr << "---------------------------------------------------------------------------------------" << endl;
		cerr << "ERROR: Transfer failed. Account #" << destination_id << " does not exist!" << endl;
		return false;
	}
	bool ret_val =  sender->Transfer(*reciever, fund_id, target_fund, amount);
	if (ret_val == true)
	{
		return ret_val;
	}
	else
	{
		cerr << "---------------------------------------------------------------------------------------" << endl;
		cerr << "ERROR: Executing Transfer failed" << endl;
	}
}

bool Bank::DisplayHistory(int account_id, int fund_id)
{
	Account* acc;

	if (bank_accounts_.Retrieve(account_id, acc))
	{
		if (fund_id < 0)
		{
			acc->ViewHistory();
			return true;
		}
		else
		{
			acc->FundHistory(fund_id);
			return true;
		}
	}
	else
	{
		cerr << "---------------------------------------------------------------------------------------" << endl;
		cerr << "ERROR: History Display failed. Account #" << account_id << " does not exist!" << endl;
		return false;
	}
}
