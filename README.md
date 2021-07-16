# Jolly-Banker
A Back-End Bankiing application that processes transactions. 

## Overview
This bank runs with an account binary tree to keep track of accounts. Accounts are viewed through the findAccount method and will be retrieved through the tree. Accounts have a history log done through a string vector. There is also a separate fund vector with Fund objects to keep track of unique balances in unique funds. 
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
  
  
## Client Accounts and funds
Each client account contains assets held in up to ten funds.  A client account is represented by a first and last name (two strings) and a unique 4 digit identifier.  A fifth digit canbe added to the digit id to represent the individual fund within the account as enumerated below:
  
0: Money Market [joint]
1: Prime Money Market [joint] 
2: Long-Term Bond 
3: Short-Term Bond 
4: 500 Index Fund 
5: Capital Value Fund
6: Growth Equity Fund
7: Growth Index Fund
8: Value Fund
9: Value Stock Index
  
## Transactions
There are five types of transactions and each are identified by a character beginning the line. 
• O:  Open a client account with the appropriate funds
• D:  Deposit assets into a fund
• W: Withdraw assets from a fund
• T:  Transfer assets between funds (can be funds owned by a single client or transfers between clients)
• H:  Display the history of all transactions for a client account or for a single fund.  Include errors in the output where appropriate. After this character key, the account-fund number is given followed by relevant information for the transaction.   
 ![image](https://user-images.githubusercontent.com/70036749/125998723-95182f55-59ef-47fc-872e-27ef11a4f56c.png)

 ## Errors
 ![image](https://user-images.githubusercontent.com/70036749/125998813-3c64c035-3722-4291-bc97-90fdfb2f52d2.png)

