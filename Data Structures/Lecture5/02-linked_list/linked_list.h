#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

#include "node.h"
#include "linked_list_exception.h"

class LinkedList {
	friend std::ostream &operator <<(std::ostream &os, const LinkedList &linkedList);
public:
	LinkedList();
	LinkedList(const LinkedList &other);
	~LinkedList();
	LinkedList &operator =(const LinkedList &rhs);

	void insertAfter(Node *nodeP, const EType &val);
	void insertFront(const EType &val);
	void insert(Node *nodeP, const EType &val);
	
	EType remove(Node *nodeP);
	void removeAfter(Node *nodeP);
	void removeFront();

	void clear();

	EType &front() const {return head->data;}	

	bool contains(const EType &val) const {return find(val);}
	Node *find(const EType &val) const {return find(head, val);}

	bool isEmpty() const {return !head;}
	//Empty function for the assignment
	bool empty();
	int getSize() const {return getSize(head);}
	int size();

// Making head and tail public for testing purposes
	Node *head;
private:
	Node *copyNodes(Node *head) const;
	int getSize(Node *head) const;
	Node *find(Node *head, const EType &val) const;
};

#endif
