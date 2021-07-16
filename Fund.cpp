/*
*
*
* Alan Lai
* 12/1/2020 - 12/10/2020
*
* Fund.cpp
*
* The fund class holds money for an account. It consists of an ID, name, amount, and joint ID if applicable.
* A fund has a history too.
*/
#ifndef FUND_CPP
#define FUND_CPP
#include <iostream>
#include <vector>
#include <string>
#include "Transaction.h"
#include "Fund.h"
using namespace std;

Fund::Fund() 
{
}

Fund::Fund(int fund_id)
{	// Fund ID automatically sets the name [0-9]
	this->fund_ID_ = fund_id;
	switch (fund_id)
	{
	case 0:
		this->name_ = "Money Market";
		this->joint_ID_ = 1;
		break;
	case 1:
		this->name_ = "Prime Money Market";
		this->joint_ID_ = 0;
		break;
	case 2:
		this->name_ = "Long-Term Bond";
		this->joint_ID_ = 3;
		break;
	case 3:
		this->name_ = "Short-Term Bond";
		this->joint_ID_ = 2;
		break;
	case 4:
		this->name_ = "500 Index Fund";
		break;
	case 5:
		this->name_ = "Capital Value Fund";
		break;
	case 6:
		this->name_ = "Growth Equity Fund";
		break;
	case 7:
		this->name_ = "Growth Index Fund";
		break;
	case 8:
		this->name_ = "Value Fund";
		break;
	case 9:
		this->name_ = "Value Stock Index";
		break;
	}
}

Fund::~Fund()
{
}

string Fund::getName() const
{
	return name_;
}

int Fund::getID() const
{
	return fund_ID_;
}
int Fund::getAmount() const
{
	return amount_;
}

int Fund::getJointID() const
{
	return joint_ID_;
}


bool Fund::HasJoint() const
{
	if (joint_ID_ == -1)
	{
		return false;
	} 
	return true;
}

bool Fund::Withdraw(int amount)
{
	amount_ = amount_ - amount;
	return true;
}

bool Fund::Deposit(int amount)
{
	this->amount_ += amount;
	return true;
}

vector<Transaction> Fund::getHistory() const
{
	return fund_history_;
}



void Fund::PushHistory(Transaction toInsert)
{
	fund_history_.push_back(toInsert);
}
#endif
