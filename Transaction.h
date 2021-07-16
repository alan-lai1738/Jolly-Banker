/*
*
*
* Alan Lai
* 12/1/2020 - 12/10/2020
*
* Transaction.h
*
* Transaction is a class for finished transactions. 
* The private data values of type, first/last names 1/2, account IDs 1/2,
* amount, status, failure reason, joint transaction, and joint amount are all
* different depending on the transaction type. These are stored and printed in account/fund
* histories. 
*/
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <ostream>
#include <string>
using namespace std;

class Transaction
{
	friend ostream& operator<<(ostream& the_stream, Transaction& rhs);

public:
	// Constructor for Account Opening Transaction: Type O AND Constructor for History Display Transaction: Type H
	Transaction(char type, string firstName, string lastName, int accID);
	// Constructor for Withdrawal Transaction: Type W/Constructor for Deposit Transaction: Type D
	Transaction(char type, string firstName, string lastName, int accID, int fundID, int amount, bool status);
	// Constructor for Withdrawal Transaction: Type W/Constructor except it's a joint withdrawal
	Transaction(char type, string firstName, string lastName, int accID, int fundID, int amount, bool status, bool joint, int jointAmount);
	// Constructor for Transaction of Transfer from one account's fund to another account's fund: Type T
	Transaction(char type, string firstName, string lastName, string firstName1, string lastName2, int accID1, int fundID1, int amount, int accID2, int fundID2, bool status);
	// Constructor for Transaction of Transfer, with joint amount
	Transaction(char type, string firstName, string lastName, string firstName1, string lastName2, int accID1, int fundID1, int amount, int accID2, int fundID2, bool status, bool joint, int jointAmount);
	// Constructor for Fund History Display transaction: Type F
	Transaction(char type, string firstName, string lastName, int accID, int fundID);

	char getType() const;
	int getAccID1() const;
	int getAccID2() const;
	string getFirstName() const;
	string getLastName() const;
	string getFirstName2() const;
	string getLastName2() const;
	int getAmount() const;
	int getFundID1() const;
	int getFundID2() const;
	string getFundName1() const;
	string getFundName2() const;
	bool getStatus() const;
	bool isJoint() const;
	int getJointAmount() const;
	string getReason() const;

	void setReason(string reason);
	

private:
	char type_;
	string first_name_, last_name_;
	string first_name2_, last_name2_;
	int acc_id1_, fund_id1_, acc_id2_, fund_id2_;
	string fund_name1_, fund_name2_;
	int amount_;
	bool executed_status_;
	string fail_reason_;
	bool is_a_joint_transaction_ = false;
	int joint_amount_;

	string getJointName(int id) const;
	string convert(int fund);
};

#endif
