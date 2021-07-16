# Jolly-Banker
A Back-End Bankiing application that processes transactions.

## Overview
1. This program reads in a string of transactions from a file into an in-memory queue. These transactions can open accounts, withdraw funds, deposit funds, transfer funds, or ask for the transactional history to be printed.
2. This program reads from the queue and processes the transactions in order.
3. When the queue has been depleted the program will print out all open accounts and balances in those accounts.

## Driver Class
•	A transaction queue will be here to store input of transactions and will be executed one by one
•	A bank will be initiated in the class to open a bank program.
•	This Driver will take in console input to execute actions, which all runs through the bank

## Bank Class
Bank class has a binary tree of bank accounts to store all bank accounts made. There is also a private account retrieving help method, although this can just be done through retrieve from the tree.
•	Default Constructor
-	Initializes an empty bank account vector
•	Withdraw/deposit  from Accounts
-	Finds an account
-	Checks if amount is valid (invalid cases includes withdrawing more than fund balance) [returns false if not enough money left]
•	Transfer between account
-	Checks if amount transferred from the first account is valid. A second check is done to see if any joint funds can cover for missing money. Otherwise, this returns false.
-	Executes the transfer through acc1.transfer
•	Print History/Fund History
-	Displays history through a loop of cout statements. 
•	Open a new account
-	Checks if the account number is a duplicate. If dupe, returns false
-	Constructs a new account 
-	Initializes the first and last name, ID^

## BSTree Class
BSTree is a binary tree data structure that consists of a nodes that hold accounts. They also go left and right to create a subtree structure. 
•	Default Constructor
-	Initialize a null root
•	Adding an account
-	Recursively goes left if the root data is higher and right if lower. Once a spot is found, the account is inserted into a tree node.
•	Retrieving an Account: This is searched by ID
-	Recursively goes left/right depending on the root’s ID value. Sets the account reference when found, otherwise returns false.
•	Helper methods: 
-	Display: Displays contents of the account tree
-	Empty, IsEmpty

## Account Class
The Account class consists of an ID for the class, first/last name, a string of vectors for the history of transactions and a vector consisting of the 10 funds.
•	Default Constructor
-	Sets account ID, first/last name
-	This will initialize ten funds in the funds vector…all different fund types for this account. 
-	A string vector will be made for all previous transactions having to do with this account.
-	History will be updated that “Account <id> has been created” for the first thing in history.
•	Getter: Get Fund Balance
-	Uses funds vector to find a fund and returns the value of that fund’s balance.
•	Transfer Money from one account to another
-	Checks for valid amounts including joint funds. 
-	If the withdrawal exceeds the fund amount, the joint fund will be checked, too. Otherwise return false.
-	If valid, the money is removed and added to another account’s funds.
•	Display History/fundHistory
-	Displays history log with a loop starting from 0 to vector size.
•	Setters/Getters

## Fund Class
The Fund class is a small helper class which is seen in Fund vectors of every account. It consists of an ID (0-10) with its matching Index/Market/Fund. There is also an amount of money in the fund and a string vector for transaction history, having to do with the fund.
•	Default Constructor
-	Initialized with an ID and name, and default amount is  0.
•	getName(): returns name of Fund
•	getID returns the ID of the fund
•	setAmount is to update the fund amount
•	getAmount returns the value of the amount in the fund. This should be CONST
•	getHistory is to access the history of the fund, typically to print it out.


## Design

![alt text](https://github.com/alan-lai1738/Jolly-Banker/blob/main/InkedProgram%205%20design%20Alan_LI.jpg?raw=true)
