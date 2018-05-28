#ifndef NODE_UTILS_H
#define NODE_UTILS_H

#include <iostream>

#include "node.h"
#include "node_utils.h"

using namespace std;

int length(const Node *head) {
	int count = 0;
	while (head) {
		count++;
		head = head->next;
	}
	return count;
}

//Modified insertAfter
void insert(Node *nodeP, const int &val) {
    if (!nodeP) throw "null pointer sent to insert";
    
    //Checks if the data to insert is greater than the last
    //data of the last node on the list
    if(val < nodeP->data)
    {
      cout << endl << nodeP->data << " " << val << endl;
      nodeP = new Node(val, nodeP);
      cout << endl << nodeP->data << endl;
    }
    else
    {
    //Do an insert after
	  Node *p = nodeP, *q = NULL; 

      while (p != NULL && val > p->data) {
	  	q = p;
		p = p->next;
	  }
	  
      nodeP = q;
	  Node *newNodeP = new Node(val, nodeP->next);
	  nodeP->next = newNodeP;
    }
}

int removeAfter(Node *nodeP) {
	if (!nodeP) throw "Passed NULL to removeAfter";
	if (!nodeP->next) throw "Attempting to remove nonexistent node";
	Node *nextNodeP = nodeP->next;
	nodeP->next = nextNodeP->next;
	EType data = nextNodeP->data;
	delete nextNodeP;
	return data;
}

void removeFront(Node *&head)
{
    Node *temp = head;
	head = head->next;
	delete temp;
}

//This is the remove function for the assignment
//It calls existing/provided functions to work on any case
bool newremove(Node *&head, const EType &data) {
	Node *p = head, *q = NULL; 

	while (p != NULL && data != p->data) {
		q = p;
		p = p->next;
	}
	if (p == NULL) 
		return false;
	else if (q == NULL)
		removeFront(head);
	else
		removeAfter(q);
}

//ALL FUNCTIONS BELOW WERE PROVIDED ON THE WEBPAGE

void clear(Node *&head) {
	while (head) {
		Node *p = head;
		head = head->next;
		delete p;
	}
}

Node *find(Node *head, const EType &val) {
	while (head) {
		if (head->data == val) return head;
		head = head->next;
	}
	return 0;
}

bool contains(Node *head, const EType &data) {
	return find(head, data);					// i.e., return find(head, data) != NULL
}

Node *copy(const Node *head) {
	Node *lastNode = 0, *newHead = 0;
	while (head) {
		Node *q = new Node(head->data);
		if (!newHead) 
			newHead = q;
		else
			lastNode->next = q;
		lastNode = q;
		head = head->next;
	}
	return newHead;
}

void print(ostream &os, const Node *head) {
	while (head) {
		os << *head;
		head = head->next;
	}
}

ostream &operator <<(ostream &os, const Node *head) {
	while (head) {
		os << *head;
		head = head->next;
		if (head) os << " -> ";
	}
	return os;
}

#endif
