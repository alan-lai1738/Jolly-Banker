/*
*
*
* Alan Lai 
* 12/1/2020 - 12/10/2020
*
* Bank.h
*
* This is the implementation of Bank for the Jolly Banker. 
* The Bank class reads a file and puts it into a queue. These transactions
* are executed and put into the tree. 
*/
#ifndef BANK_H
#define BANK_H
#include <iostream>
#include <string>
#include <queue>
#include "AccountTree.h"

class Bank
{
public:
	// Constructors/Destructors
	Bank();
	~Bank();

	// Actions
	void ReadTransactions(string fileName);
	void ExecuteTransactions();
	void Display();

private:
	// Data
	AccountTree bank_accounts_;
	queue<vector<string>> transaction_queue_;
	// Helper Methods
	bool OpenAccount(int account_id, string first_name, string last_name);
	bool ExecuteDeposit(int account_id, int fund_id, int amount);
	bool ExecuteWithdrawal(int account_id, int fund_id, int amount);
	bool ExecuteTransfer(int account_id, int destination_id, int fund_id, int target_fund, int amount);
	bool DisplayHistory(int account_id, int fund_id);
};

#endif
