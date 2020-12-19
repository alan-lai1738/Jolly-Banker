// Program 5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <string>
#include "Account.h"
#include "AccountTree.h"
#include "Fund.h"
#include "Bank.h"
#include "Transaction.h"
#include <queue>
using namespace std;

int main()
{
	Bank JollyBanker;
	JollyBanker.ReadTransactions("BankTransIn.txt");
	JollyBanker.ExecuteTransactions();
	JollyBanker.Display();
	
	

		/*AccountTree tree;
		Account johnny(1001, "Johnny", "Cash");
		tree.Insert(&johnny);
		johnny.Deposit(0, 542);
		johnny.Deposit(1, 1542);
		johnny.Deposit(2, 5442);
		johnny.Deposit(3, 7540);
		johnny.Deposit(7, 5442);
		johnny.Deposit(6, 7542);
		johnny.Deposit(1, 1500);
		johnny.Deposit(2, 5000);
		johnny.Deposit(3, 7000);
		johnny.Deposit(7, 6543);
		johnny.Deposit(6, 7576);

		johnny.Withdraw(7, 1000);
		johnny.Withdraw(6, 65);
		johnny.Withdraw(0, 72);

		johnny.Transfer(johnny, 7, 5, 54);

		johnny.Withdraw(7, 20000);

		johnny.ViewHistory();

		Account hank(1253, "Hank", "Williams");
		tree.Insert(&hank);
		for (int i = 0; i < 10; i++)
		{
			hank.Deposit(i, 10000);
		}

		hank.fundHistory(4);
		hank.Withdraw(2, 15000);
		Account willie(9876, "Willie", "Nelson");
		tree.Insert(&willie);
		Account bob(9876, "Bob", "Willis");
		tree.Insert(&bob);
		//hank.Transfer()
		tree.Display();*/

}

