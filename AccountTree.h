/*
*
*
* Alan Lai
* 12/1/2020 - 12/10/2020
*
* AccountTree.h
*
* This is the declaration of AccountTree, which is used to store accounts in the bank.
* An Account tree holds subtree/twig nodes. All twigs have a left and right.
* An account tree can insert and retrieve accounts.
* Display prints out the tree contents in order of account ID.
* Extra methods: Empty, isEmpty, getSize
* Recursive helper traverser methods: TraverseAndInsert, TraverseAndDisplay, TraverseAndRecieve, recursive size method
*/
#ifndef BS_TREE_H
#define BS_TREE_H
#include <iostream>
#include "Account.h"
using namespace std;


class AccountTree
{
public:
	AccountTree();
	~AccountTree();

	bool Insert(Account *toInsert);
	bool Retrieve(const int& numToFind, Account*& acc) const;
	void Display() const;
	void Empty();
	bool isEmpty() const;
	int getSize();

private:
	struct Node
	{
		Account* p_account_;
		Node* right;
		Node* left;
	};
	Node* root_ = NULL;

	bool TraverseAndInsert(Node* current, Account* toInsert);
	void TraverseAndDisplay(Node* current) const;
	Account* TraverseAndRetrieve(Node* current, const int& to_find) const;
	int size(Node* current);
};

#endif
