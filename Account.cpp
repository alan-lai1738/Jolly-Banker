/*
*
*
* Alan Lai
* 12/1/2020 - 12/10/2020
*
* Account.cpp
*
* The Account class has an ID, first/last name, ten funds, and a transaction history.
* You can deposit, transfer, and withdraw money between accounts.
* Display history and fund history views previous transactions of the account/fund.
*/
#ifndef ACCOUNT_CPP
#define ACCOUNT_CPP
#include <ostream>
#include <iostream>
#include <vector>
#include <string>
#include "Account.h"
#include "Fund.h";
using namespace std;

//Constructors
Account::Account()
{
	accoount_id_ = 0;
}

Account::Account(int id, string the_firstname, string the_lastname)
{
	this->accoount_id_ = id;
	this->first_name_ = the_firstname;
	this->last_name_ = the_lastname;
	// Create the ten funds in the account
	Fund f0(0), f1(1), f2(2), f3(3), f4(4), f5(5), f6(6), f7(7), f8(8), f9(9);
	this->funds_[0] = f0;
	this->funds_[1] = f1;
	this->funds_[2] = f2;
	this->funds_[3] = f3;
	this->funds_[4] = f4;
	this->funds_[5] = f5;
	this->funds_[6] = f6;
	this->funds_[7] = f7;
	this->funds_[8] = f8;
	this->funds_[9] = f9;

	// Transaction is tracked
	Transaction opening_transaction('O', the_firstname, the_lastname, id);
	transaction_history_.push_back(opening_transaction);
}


//Actions: All these create a transaction
bool Account::Deposit(int fundID, int amount)
{
	if (amount < 0)
	{
		// Update Transaction Logs with Failed transaction
		Transaction failed_deposit('D', this->first_name_, this->last_name_, this->accoount_id_, fundID, amount, false);
		failed_deposit.setReason("Can't deposit a negative amount.");
		transaction_history_.push_back(failed_deposit);
		funds_[fundID].PushHistory(failed_deposit);
		cerr << "ERROR:" << failed_deposit << endl;
		return false;
	}
	funds_[fundID].Deposit(amount);
	// Update Transaction Logs: Account History and Fund History
	Transaction successful_deposit('D', this->first_name_, this->last_name_, this->accoount_id_, fundID, amount, true);
	transaction_history_.push_back(successful_deposit);
	funds_[fundID].PushHistory(successful_deposit);
	return true;
}

bool Account::Transfer(Account& destination, int fund_ID, int targetfund_ID, int amount)
{
	if (amount < 0)
	{
		// Update Transaction Logs with Failed transaction
		Transaction failed_transfer('T', first_name_, last_name_, destination.getFirstName(), destination.getLastName(), accoount_id_, fund_ID, amount, destination.getID(), targetfund_ID, false);
		failed_transfer.setReason("Can't transfer a negative amount.");
		transaction_history_.push_back(failed_transfer);
		funds_[fund_ID].PushHistory(failed_transfer);
		funds_[targetfund_ID].PushHistory(failed_transfer);
		cerr << "ERROR:" << failed_transfer << endl;
		return false;
	}
	if (funds_[fund_ID].HasJoint() == false)
	{	// Non-Joint Account Case
		if (funds_[fund_ID].getAmount() < amount)
		{	// If there is less money than requested in the transfer, this is a failed transfer
			Transaction failed('T', first_name_, last_name_, destination.getFirstName(), destination.getLastName(), accoount_id_, fund_ID, amount, destination.getID(), targetfund_ID, false);
			failed.setReason("Not enough funds to complete transfer.");
			transaction_history_.push_back(failed);
			funds_[fund_ID].PushHistory(failed);
			funds_[targetfund_ID].PushHistory(failed);
			if (this->accoount_id_ != destination.getID())
			{
				destination.PushHistory(failed);
				destination.getFunds(fund_ID).PushHistory(failed);
				destination.getFunds(targetfund_ID).PushHistory(failed);
			}
			cerr << "ERROR:" << failed << endl;
			return false;
		}
		else
		{	// If there is enough money to move from the Fund, move the money to the target fund.
			funds_[fund_ID].Withdraw(amount);
			destination.getFunds(targetfund_ID).Deposit(amount);
			Transaction success('T', first_name_, last_name_, destination.getFirstName(), destination.getLastName(), accoount_id_, fund_ID, amount, destination.getID(), targetfund_ID, true);
			transaction_history_.push_back(success);
			funds_[fund_ID].PushHistory(success);
			funds_[targetfund_ID].PushHistory(success);
			if (this->accoount_id_ != destination.getID())
			{
				destination.PushHistory(success);
				destination.getFunds(fund_ID).PushHistory(success);
				destination.getFunds(targetfund_ID).PushHistory(success);
			}
			return true;
		}
	}
	if (funds_[fund_ID].HasJoint() == true)
	{	// Case: There is a Joint Fund for the Fund were moving from
		int totalAmount = funds_[fund_ID].getAmount() + funds_[funds_[fund_ID].getJointID()].getAmount();
		if (totalAmount < amount)
		{	//	If total amount With joint fund is less than the request amount, this is a failed transfer.
			Transaction failed('T', first_name_, last_name_, destination.getFirstName(), destination.getLastName(), accoount_id_, fund_ID, amount, destination.getID(), targetfund_ID, false);
			failed.setReason("Not Enough funds to complete transfer.");
			transaction_history_.push_back(failed);
			funds_[fund_ID].PushHistory(failed);
			funds_[targetfund_ID].PushHistory(failed);
			if (this->accoount_id_ != destination.getID())
			{
				destination.PushHistory(failed);
				destination.getFunds(fund_ID).PushHistory(failed);
				destination.getFunds(targetfund_ID).PushHistory(failed);
			}
			cerr << "ERROR:" << failed << endl;
			return false;
		}
		else if(funds_[fund_ID].getAmount()  >= amount)
		{	// Case: There is enough in the fund that we don't need to pull from the joint fund
			funds_[fund_ID].Withdraw(amount);
			destination.getFunds(targetfund_ID).Deposit(amount);
			Transaction success('T', first_name_, last_name_, destination.getFirstName(), destination.getLastName(), accoount_id_, fund_ID, amount, destination.getID(), targetfund_ID, true);
			transaction_history_.push_back(success);
			funds_[fund_ID].PushHistory(success);
			funds_[targetfund_ID].PushHistory(success);
			if (this->accoount_id_ != destination.getID())
			{
				destination.PushHistory(success);
				destination.getFunds(fund_ID).PushHistory(success);
				destination.getFunds(targetfund_ID).PushHistory(success);
			}
			return true;
		}
		else
		{	
			// Else: We pull from the main fund and more from the joint fund.
			int temp = funds_[fund_ID].getAmount();
			funds_[fund_ID].Withdraw(funds_[fund_ID].getAmount());		// Take from Main Fund
			int jointIdx = funds_[fund_ID].getJointID();	// Take enough from the joint fun
			funds_[jointIdx].Withdraw(amount - temp);
			destination.getFunds(targetfund_ID).Deposit(amount);
			Transaction success('T', first_name_, last_name_, destination.getFirstName(), destination.getLastName(), accoount_id_, fund_ID, amount, destination.getID(), targetfund_ID, true, true, (amount - temp));
			transaction_history_.push_back(success);
			funds_[fund_ID].PushHistory(success);
			funds_[jointIdx].PushHistory(success);
			funds_[targetfund_ID].PushHistory(success);
			if (this->accoount_id_ != destination.getID())
			{
				destination.PushHistory(success);
				destination.getFunds(fund_ID).PushHistory(success);
				destination.getFunds(targetfund_ID).PushHistory(success);
			}
			return true;
		}
	}
}



bool Account::Withdraw(int fund_ID, int amount)
{
	if (amount < 0)
	{
		Transaction failed_withdrawal('W', this->first_name_, this->last_name_, this->accoount_id_, fund_ID, amount, false);
		failed_withdrawal.setReason("Can't withdraw a negative amount.");
		transaction_history_.push_back(failed_withdrawal);	// Update history
		funds_[fund_ID].PushHistory(failed_withdrawal);		// Update Fund History
		cerr << "ERROR:" << failed_withdrawal << endl;		// Display Error
		return false;
	}
	if (funds_[fund_ID].HasJoint() == false)
	{
		if (funds_[fund_ID].getAmount() < amount)
		{	// If there is less money than requested in the withdrawal, this is a failed withdrawal.
			Transaction failed('W', first_name_, last_name_, accoount_id_, fund_ID, amount, false);
			failed.setReason("Not enough funds to complete withdrawal.");
			transaction_history_.push_back(failed);
			funds_[fund_ID].PushHistory(failed);
			cerr << "ERROR:" << failed << endl;
			return false;
		}
		else
		{
			funds_[fund_ID].Withdraw(amount);
			// Update Transaction Logs: Account History and Fund History
			Transaction successful_withdrawal('W', this->first_name_, this->last_name_, this->accoount_id_, fund_ID, amount, true);
			transaction_history_.push_back(successful_withdrawal);
			funds_[fund_ID].PushHistory(successful_withdrawal);
			return true;
		}
		return true;
	}
	if (funds_[fund_ID].HasJoint() == true)
	{	// Case: There is a Joint Fund for the Fund were moving from
		int totalAmount = funds_[fund_ID].getAmount() + funds_[funds_[fund_ID].getJointID()].getAmount();
		if (totalAmount < amount)
		{	//	If total amount With joint fund is less than the request amount, this is a failed transfer.
			Transaction failed('W', first_name_, last_name_, accoount_id_, fund_ID, amount, false);
			failed.setReason("Not enough funds to complete withdrawal.");
			transaction_history_.push_back(failed);
			funds_[fund_ID].PushHistory(failed);
			cerr << "ERROR:" << failed << endl;
			return false;
		}
		else if (funds_[fund_ID].getAmount() >= amount)
		{	// Case: There is enough in the fund that we don't need to pull from the joint fund
			funds_[fund_ID].Withdraw(amount);
			Transaction successful_withdrawal('W', this->first_name_, this->last_name_, this->accoount_id_, fund_ID, amount, true);
			transaction_history_.push_back(successful_withdrawal);
			funds_[fund_ID].PushHistory(successful_withdrawal);
			return true;
		}
		else
		{	
			// Else: We pull from the main fund and more from the joint fund.
			int temp = funds_[fund_ID].getAmount();
			funds_[fund_ID].Withdraw(funds_[fund_ID].getAmount());		// Take from Main Fund
			int jointIdx = funds_[fund_ID].getJointID();	// Take enough from the joint fund
			funds_[jointIdx].Withdraw(amount - temp);
			Transaction successful_withdrawal('W', this->first_name_, this->last_name_, this->accoount_id_, fund_ID, amount, true, true, (amount - temp));
			transaction_history_.push_back(successful_withdrawal);
			funds_[fund_ID].PushHistory(successful_withdrawal);
			return true;
		}
	}
}


void Account::ViewHistory()
{
	cout << "-----------------VIEWING " << transaction_history_.size() << " PREVIOUS TRANSACTIONS FOR " << first_name_ << " " << last_name_ << "'S ACCOUNT-----------------" << endl;
	for (int i = 0; i < transaction_history_.size(); i++)
	{
		cout << i+1 << ") " << transaction_history_[i] << endl;
	}
	//cout << "-------------------------------------END OF HISTORY-------------------------------------" << endl;
	transaction_history_.push_back(Transaction('H', first_name_, last_name_, accoount_id_));
}

void Account::FundHistory(int fundID)
{
	vector<Transaction> toPrint = funds_[fundID].getHistory();
	cout << "------------VIEWING " << toPrint.size() << " PREVIOUS TRANSACTIONS FOR " << first_name_ << " " << last_name_ << "'S " << funds_[fundID].getName() << "------------" << endl;
	for (int i = 0; i < toPrint.size(); i++)
	{
		cout << i + 1 << ") " << toPrint[i] << endl;
	}
	transaction_history_.push_back(Transaction('F', first_name_, last_name_, accoount_id_));
}

//Getters
int Account::getID() const
{
	return accoount_id_;
}

string Account::getFirstName() const
{
	return first_name_;
}

string Account::getLastName() const
{
	return last_name_;
}

Fund& Account::getFunds(int id)
{
	return funds_[id];
}

void Account::PushHistory(Transaction toInsert)
{
	transaction_history_.push_back(toInsert);
}


int Account::getFundBalance(int fundID) const
{
	return funds_[fundID].getAmount();
}

ostream& operator<<(ostream& the_stream, Account& rhs)
{
	the_stream << "---------------------------------------------------------------------------------------" << endl;
	the_stream << rhs.first_name_ << " " << rhs.last_name_ << " | " << "Account #" << rhs.accoount_id_ << endl;
	for (int i = 0; i < kNUMBER_OF_FUNDS; i++)
	{
		the_stream << rhs.funds_[i].getName() << ": $" << rhs.funds_[i].getAmount() << endl;
	}
	return the_stream;
}

#endif
