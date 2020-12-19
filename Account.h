/*
*
* CSS 342, Program 5
*
* Alan Lai
* 12/1/2020 - 12/10/2020
*
* Account.h
*
* The Account class has an ID, first/last name, ten funds, and a transaction history.
* You can deposit, transfer, and withdraw money between accounts.
* Display history and fund history views previous transactions of the account/fund.
*/
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include <vector>
#include <string>
#include "Fund.h"
using namespace std;

const int kNUMBER_OF_FUNDS = 10;	// There are TEN funds in every account.

class Account
{
	// Operator Overloads
	friend ostream& operator<<(ostream& the_stream, Account& rhs);

public:
	Account();
	//Constructors
	Account(int id, string the_firstname, string the_lastname);

	//Actions: All these create a transaction
	bool Deposit(int fundID, int amount);			
	bool Transfer(Account& destination, int fund_ID, int targetfund_ID, int amount);
	bool Withdraw(int fund_ID, int amount);
	void ViewHistory();
	void FundHistory(int fundID);
	
	//Getters
	int getID() const;
	string getFirstName() const;
	string getLastName() const;
	
	int getFundBalance(int fundID) const;

	
	

private:
	int accoount_id_ = 0;
	vector<Transaction> transaction_history_;
	string first_name_;
	string last_name_;
	Fund funds_[kNUMBER_OF_FUNDS];

	Fund& getFunds(int id);	// Helper method to access a certain fund from funds_
	void PushHistory(Transaction toInsert);	// Helper method to insert a transaction into the history.
};

#endif