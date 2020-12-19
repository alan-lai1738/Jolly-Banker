/*
*
* CSS 342, Program 5
*
* Alan Lai
* 12/1/2020 - 12/10/2020
*
* Fund.h
*
* The fund class holds money for an account. It consists of an ID, name, amount, and joint ID if applicable.
* A fund has a history too.
*/
#ifndef FUND_H
#define FUND_H
#include <iostream>
#include <vector>
#include <string>
#include "Transaction.h"
using namespace std;
class Fund
{
public: 
	// Constructors
	Fund();
	Fund(int fundID);
	~Fund();
		
	// Getters
	string getName() const;
	int getID() const;
	int getAmount() const;
	int getJointID() const;
	bool HasJoint() const;

	// Actions
	bool Withdraw(int amount);
	bool Deposit(int amount);
	vector<Transaction> getHistory() const;
	void PushHistory(Transaction toInsert);



private:
	int fund_ID_;
	string name_;
	int amount_ = 0;
	vector<Transaction> fund_history_;
	int joint_ID_ = -1;
};

#endif