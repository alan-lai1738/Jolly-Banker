/*
*
* CSS 342, Program 5
*
* Alan Lai
* 12/1/2020 - 12/10/2020
*
* Transaction.cpp
*
* Transaction is a class for finished transactions. These are added to the transaction logs.
* The private data values of type, first/last names 1/2, account IDs 1/2,
* amount, status, failure reason, joint transaction, and joint amount are all
* different depending on the transaction type. These are stored and printed in account/fund
* histories.
*/
#ifndef TRANSACTION_CPP
#define TRANSACTION_CPP
#include <iostream>
#include <ostream>
#include <string>
#include "Transaction.h"
using namespace std;

ostream& operator<<(ostream& the_stream, Transaction& rhs)
{
	switch (rhs.type_)
	{
	case 'O':
		the_stream << "Account #" << rhs.acc_id1_ << " was opened for " << rhs.first_name_ << " " << rhs.last_name_ << ".";
		return the_stream;
		break;
	case 'D':
		if (rhs.executed_status_ == true)
		{
			the_stream << "$" << rhs.amount_ << " was deposited into " << rhs.first_name_ << " " << rhs.last_name_ << "'s " << rhs.fund_name1_ << ".";
		}
		else if (rhs.executed_status_ == false)
		{
			the_stream << "Failed to deposit $" << rhs.amount_ << " into " << rhs.first_name_ << " " << rhs.last_name_ << "'s " << rhs.fund_name1_ << ". REASON: " << rhs.getReason();
		}
		return the_stream;
		break;
	case 'W':
		if (rhs.executed_status_ == true && rhs.is_a_joint_transaction_ == false)
		{
			the_stream << "$" << rhs.amount_ << " was withdrawn from " << rhs.first_name_ << " " << rhs.last_name_ << "'s " << rhs.fund_name1_ << ".";
		}
		else if (rhs.executed_status_ == false && rhs.is_a_joint_transaction_ == false)
		{
			the_stream << "Failed to withdraw $" << rhs.amount_ << " from " << rhs.first_name_ << " " << rhs.last_name_ << "'s " << rhs.fund_name1_ << ". REASON: " << rhs.getReason();
		}
		else if (rhs.executed_status_ = true && rhs.is_a_joint_transaction_ == true)
		{
			the_stream << "$" << (rhs.amount_ - rhs.joint_amount_) << " from " << rhs.fund_name1_ << " and $" << rhs.joint_amount_ << " from " << rhs.getJointName(rhs.fund_id1_) << " was withdrawn from " << rhs.first_name_ << " " << rhs.last_name_ << "'s account.";
		}
		return the_stream;
		break;
	case 'T':
		if (rhs.acc_id1_ == rhs.acc_id2_)
		{
			if (rhs.executed_status_ == true && rhs.is_a_joint_transaction_ == false)
			{
				the_stream << rhs.first_name_ << " " << rhs.last_name_ << " did an internal transfer of $" << rhs.amount_ << " from their " << rhs.fund_name1_ << " to their " << rhs.fund_name2_ << ".";
			}
			else if (rhs.executed_status_ == false && rhs.is_a_joint_transaction_ == false)
			{
				the_stream << "Failed to do an internal transfer of $" << rhs.amount_ << " in" << rhs.first_name_ << " " << rhs.last_name_ << "'s " << rhs.fund_name1_ << " to " << rhs.fund_name2_ << ". REASON: " << rhs.getReason();
			}
		}
		else
		{
			if (rhs.executed_status_ == true && rhs.is_a_joint_transaction_ == false)
			{
				the_stream << "$" << rhs.amount_ << " was transferred from " << rhs.first_name_ << " " << rhs.last_name_ << "'s " << rhs.fund_name1_ << " to " << rhs.first_name2_ << " " << rhs.last_name2_ << "'s " << rhs.fund_name2_ << ".";
			}
			else if (rhs.executed_status_ == false && rhs.is_a_joint_transaction_ == false)
			{
				the_stream << "Failed to transfer $" << rhs.amount_ << " from " << rhs.first_name_ << " " << rhs.last_name_ << "'s " << rhs.fund_name1_ << " to " << rhs.first_name2_ << " " << rhs.last_name2_ << "'s " << rhs.fund_name2_ << ". REASON: " << rhs.getReason();
			}
			else if (rhs.executed_status_ == true && rhs.is_a_joint_transaction_ == true)
			{
				the_stream  << "$" << (rhs.amount_ - rhs.joint_amount_) << " from " << rhs.fund_name1_ << " and $" << rhs.joint_amount_ << " from " << rhs.getJointName(rhs.fund_id1_) << " was transferred from " << rhs.first_name_ << " " << rhs.last_name_ << " to " << rhs.first_name2_ << " " << rhs.last_name2_ << "'s " << rhs.fund_name2_ << ".";
			}
		}
		return the_stream;
		break;
	case 'H':
		the_stream << "History was viewed for " << rhs.first_name_ << " " << rhs.last_name_ << ".";
		return the_stream;
		break;
	case 'F':
		the_stream << "History was viewed for " << rhs.first_name_ << " " << rhs.last_name_ << "'s " << rhs.fund_name1_ << ".";
		return the_stream;
	}
}

Transaction::Transaction(char type, string firstName, string lastName, int accID)
{	// Type: O, H
	this->type_ = type;
	this->first_name_ = firstName;
	this->last_name_ = lastName;
	this->acc_id1_ = accID;

}

Transaction::Transaction(char type, string firstName, string lastName, int accID, int fundID, int amount, bool status)
{	// Type: W, D
	this->type_ = type;
	this->first_name_ = firstName;
	this->last_name_ = lastName;
	this->acc_id1_ = accID;
	this->fund_id1_ = fundID;
	this->fund_name1_ = convert(fundID);
	this->amount_ = amount;
	this->executed_status_ = status;
}

Transaction::Transaction(char type, string firstName, string lastName, int accID, int fundID, int amount, bool status, bool joint, int jointAmount)
{	// Type: W, JOINT
	this->type_ = type;
	this->first_name_ = firstName;
	this->last_name_ = lastName;
	this->acc_id1_ = accID;
	this->fund_id1_ = fundID;
	this->fund_name1_ = convert(fundID);
	this->amount_ = amount;
	this->executed_status_ = status;
	this->is_a_joint_transaction_ = true;
	this->joint_amount_ = jointAmount;
}

Transaction::Transaction(char type, string firstName, string lastName, string firstName2, string lastName2, int accID1, int fundID1, int amount, int accID2, int fundID2, bool status)
{	//	Type T
	this->type_ = type;
	this->first_name_ = firstName;
	this->last_name_ = lastName;
	this->first_name2_ = firstName2;
	this->last_name2_ = lastName2;
	this->acc_id1_ = accID1;
	this->fund_id1_ = fundID1;
	this->fund_name1_ = convert(fundID1);
	this->acc_id2_ = accID2;
	this->fund_id2_ = fundID2;
	this->fund_name2_ = convert(fundID2);
	this->amount_ = amount;
	this->executed_status_ = status;
}

Transaction::Transaction(char type, string firstName, string lastName, string firstName2, string lastName2, int accID1, int fundID1, int amount, int accID2, int fundID2, bool status, bool joint, int jointAmount)
{	//	Type T JOINT
	this->type_ = type;
	this->first_name_ = firstName;
	this->last_name_ = lastName;
	this->first_name2_ = firstName2;
	this->last_name2_ = lastName2;
	this->acc_id1_ = accID1;
	this->fund_id1_ = fundID1;
	this->fund_name1_ = convert(fundID1);
	this->acc_id2_ = accID2;
	this->fund_id2_ = fundID2;
	this->fund_name2_ = convert(fundID2);
	this->amount_ = amount;
	this->executed_status_ = status;
	this->is_a_joint_transaction_ = true;
	this->joint_amount_ = jointAmount;
}

Transaction::Transaction(char type, string firstName, string lastName, int accID, int fundID)
{	// Type F
	this->type_ = type;
	this->first_name_ = firstName;
	this->last_name_ = lastName;
	this->acc_id1_ = accID;
	this->fund_id1_ = fundID;
	this->fund_name1_ = convert(fundID);
}

char Transaction::getType() const
{
	return type_;
}

int Transaction::getAccID1() const
{
	return acc_id1_;
}

int Transaction::getAccID2() const
{
	return acc_id2_;
}


string Transaction::getFirstName() const
{
	return first_name_;
} 

string Transaction::getLastName() const
{
	return last_name_;
}

string Transaction::getFirstName2() const
{
	return first_name2_;
}

string Transaction::getLastName2() const
{
	return last_name2_;
}

int Transaction::getAmount() const
{
	return amount_;
}
string Transaction::getFundName1() const
{
	return fund_name1_;
}

string Transaction::getFundName2() const
{
	return fund_name2_;
}
bool Transaction::getStatus() const
{
	return executed_status_;
}

bool Transaction::isJoint() const
{
	return is_a_joint_transaction_;
}

int Transaction::getJointAmount() const
{
	return joint_amount_;
}

void Transaction::setReason(string reason)
{
	fail_reason_ = reason;
}

string Transaction::getReason() const
{
	return fail_reason_;
}

int Transaction::getFundID1() const
{
	return fund_id1_;
}

int Transaction::getFundID2() const
{
	return fund_id2_;
}

string Transaction::getJointName(int id) const
{
	if (id == 0)
	{
		return "Prime Money Market";
	}
	else if (id == 1)
	{
		return "Money Market";
	}
	else if (id == 2)
	{
		return "Short-Term Bond";
	}
	else if (id == 3)
	{
		return "Long-Term Bond";
	}
	else return "";
}

string Transaction::convert(int fund)
{
	string fund_name1;
	switch (fund)
	{
	case 0:
		fund_name1 = "Money Market";
		break;
	case 1:
		fund_name1 = "Prime Money Market";
		break;
	case 2:
		fund_name1 = "Long-Term Bond";
		break;
	case 3:
		fund_name1 = "Short-Term Bond";
		break;
	case 4:
		fund_name1 = "500 Index Fund";
		break;
	case 5:
		fund_name1 = "Capital Value";
		break;
	case 6:
		fund_name1 = "Growth Equity Fund";
		break;
	case 7:
		fund_name1 = "Growth Index Fund";
		break;
	case 8:
		fund_name1 = "Value Fund";
		break;
	case 9:
		fund_name1 = "Value Stock Index";
		break;
	}
	return fund_name1;
}

#endif



	