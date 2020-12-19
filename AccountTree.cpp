/*
*
* CSS 342, Program 5
*
* Alan Lai
* 12/1/2020 - 12/10/2020
*
* AccountTree.cpp
* 
* This is the defintion of AccountTree, which is used to store accounts in the bank.
* An Account tree holds subtree/twig nodes. All twigs have a left and right.
* An account tree can insert and retrieve accounts.
* Display prints out the tree contents in order of account ID.
* Extra methods: Empty, isEmpty, getSize
* Recursive helper traverser methods: TraverseAndInsert, TraverseAndDisplay, TraverseAndRecieve, recursive size method
*/
#include "AccountTree.h"
#include "Account.h"

AccountTree::AccountTree()
{
}

AccountTree::~AccountTree()
{
	Empty();
}

bool AccountTree::Insert(Account *toInsert)
{
	int accountID = toInsert->getID();
	if (accountID < 1000 || accountID > 9999)
	{
		cerr << "ERROR: Invalid Account Number" << endl;
		return false;
	}

	if (root_ == NULL)
	{
		root_ = new Node;
		root_->p_account_ = toInsert;
		root_->left = NULL;
		root_->right = NULL;
		return true;
	}
	else
	{	// Recursive case
		Node* current = root_;
		TraverseAndInsert(current, toInsert);
	}
	return false;
}

bool AccountTree::TraverseAndInsert(Node* current, Account* toInsert)
{	// Recursive helper function that finds a place to insert the Account. Returns false if a duplicate/fail
	if (toInsert->getID() > current->p_account_->getID())
	{
		if (current->right == NULL)
		{
			Node* InsertNode = new Node();
			InsertNode->p_account_ = toInsert;
			InsertNode->left = NULL;
			InsertNode->right = NULL;
			current->right = InsertNode;
			return true;
		}
		else
		{
			return TraverseAndInsert(current->right, toInsert);
		}
	}
	else if (toInsert->getID() < current->p_account_->getID())
	{
		if (current->left == NULL)
		{
			Node* InsertNode = new Node();
			InsertNode->p_account_ = toInsert;
			InsertNode->left = NULL;
			InsertNode->right = NULL;
			current->left = InsertNode;
			return true;
		}
		else
		{
			return TraverseAndInsert(current->left, toInsert);
		}
	}
	else
	{
		cerr << "ERROR: Account #" << toInsert->getID() << " is already opened. Operation terminated." << endl;
		return false;
	}
}

bool AccountTree::Retrieve(const int& numToFind, Account*& acc) const
{
	Account* temp_acc = TraverseAndRetrieve(root_, numToFind);
	
	if (temp_acc == NULL)
	{
		return false;
	}
	else
	{
		acc = temp_acc;
		return true;
	}
}

Account* AccountTree::TraverseAndRetrieve(Node* current, const int& to_find) const
{
	if (current == NULL)
	{
		return NULL;
	}
	else if(to_find == current->p_account_->getID())
	{
		return (current->p_account_);
	}
	else if (to_find < current->p_account_->getID())
	{
		return TraverseAndRetrieve(current->left, to_find);
	}
	else
	{
		return TraverseAndRetrieve(current->right, to_find);
	}
}

void AccountTree::Display() const
{
	if (root_ == NULL)
	{
		cerr << "ERROR: Account Tree is Empty" << endl;
	}
	TraverseAndDisplay(root_);
}

void AccountTree::TraverseAndDisplay(Node* current) const
{
	if (current->right != NULL && current->left != NULL)
	{
		TraverseAndDisplay(current->right);
		cout << *(current->p_account_) << endl;
		TraverseAndDisplay(current->left);
	}
	else if (current->left != NULL)
	{
		cout << *(current->p_account_) << endl;
		TraverseAndDisplay(current->left);
	}
	else if (current->right != NULL)
	{
		cout << *(current->p_account_) << endl;
		TraverseAndDisplay(current->right);
	}
	else
	{
		cout << *(current->p_account_) << endl;
	}
}

void AccountTree::Empty()
{
	delete root_;
	root_ = NULL;
}

bool AccountTree::isEmpty() const
{
	if (root_->left == NULL && root_->right == NULL)
	{
		return true;
	}
	return false;
}

int AccountTree::getSize()
{
	return size(root_);
}

int AccountTree::size(Node* current)
{
	if (current == NULL)
	{
		return 0;
	}
	else return size(current->left) + 1 + size(current->right);
}

