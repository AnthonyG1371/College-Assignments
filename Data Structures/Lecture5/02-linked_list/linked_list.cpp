#include <iostream>

#include "node.h"
#include "linked_list.h"
#include "linked_list_exception.h"

using namespace std;

class LinkedList;

ostream &operator <<(ostream &os, const LinkedList &linkedList) {
	os << "{";
	Node *p = linkedList.head;
	while(p){
        os << p->data << (p->next ? ", " : "");
		p = p->next;
		if(p == linkedList.head){p = false;}
	}
	os << "}";
	return os;
}

LinkedList::LinkedList() : head(NULL) {}

LinkedList::LinkedList(const LinkedList &other) {head = copyNodes(other.head);}

LinkedList::~LinkedList() {clear();}

LinkedList &LinkedList::operator =(const LinkedList &rhs) {
	if (this == &rhs) return *this;
	clear();
	head = copyNodes(rhs.head);
	return *this;
}

/*void LinkedList::insertAfter(Node *nodeP, const EType &val) {
	if (!nodeP) throw LinkedListException("Attempting to insert after NULL");
	Node *newNodeP = new Node(val, nodeP->next);
	nodeP->next = newNodeP;
	if(newNodeP->next == NULL)
	{
      tail->prev = newNodeP;
//	cout << "test" <<endl;
//      newNodeP->next = head->next;//front;
    }
		
	newNodeP->prev = nodeP;
}*/

void LinkedList::insertAfter(Node *nodeP, const EType &val) {
	if (!nodeP) throw LinkedListException("Attempting to insert after NULL");
	Node *newNodeP = new Node(val, nodeP->next);
//	newNodeP->next = nodeP->next;
//	nodeP->next->prev = newNodeP;
	nodeP->next = newNodeP;
	newNodeP->prev = nodeP;
	cout << newNodeP->prev->data<<endl;
	
	if(newNodeP->next == head)
	    head->prev = newNodeP;
}

//"New" method to insert where necassary
void LinkedList::insert(Node *nodeP, const EType &val) {
//	if (!nodeP) throw LinkedListException("Attempting to insert after NULL");
//	if(nodeP->next == NULL){insertFront(val);}
    if(!head)
    {
        insertFront(val);
    }
	else
	{
	    insertAfter(nodeP, val);
    }
}

/*void LinkedList::insertFront(const EType &val) 
{
     head = new Node(val, head, tail);
     tail = new Node(val, head, tail);
     if(head->next == NULL)
     {
//      head->next = head;
//      head->prev = head;
     }
     else if(head->prev == NULL)
     {
//       head->prev = tail->prev;    
     }
     
}*/

/*void LinkedList::insertFront(const EType &val) {
		Node *p = new Node(val);
		if (head)
			p->next  = head->next;
		else
			head = p;
		head->next = p;
}*/

void LinkedList::insertFront(const EType &val) 
{
//     if (!head) throw LinkedListException("Attempting to insert after NULL");
	
//     Node *newNodeP = new Node(val, head, head);
//     head->next = newNodeP;
     
     head = new Node(val, head);
//     head->next = head; //Crucial Line: Adds circularity
     head->prev = head;
}

/*void LinkedList::initialize()
{
     head = new Node();
}*/

/*EType LinkedList::remove(Node *nodeP) {
{
/*    if(nodeP->next == head)
        removeFront();
    else
        removeAfter(nodeP);
        return 0;
}*/

//Taken straight from the class lecture, so it isn't my own work...
EType LinkedList::remove(Node *nodeP) {
	if (!nodeP) throw "null pointer";
	Node *left = nodeP->prev;
	Node *right = nodeP->next;
	if (left) left->next = right;
	if (right) right->prev = left;
	EType data = nodeP->data;
	delete (nodeP);
	return data;
}

void LinkedList::removeAfter(Node *nodeP) {
	if (!nodeP) throw LinkedListException("Attempting to remove after NULL");
	if (!nodeP->next) throw LinkedListException("Attempting to remove nonexistent node");
	Node *nextNodeP = nodeP->next;
	nodeP->next = nextNodeP->next;
	nextNodeP->next->prev = nodeP;
	delete nextNodeP;
}

void LinkedList::removeFront() {
	Node *hold = head;
	head = head->next;
	delete hold;
}

void LinkedList::clear() {
	while (!isEmpty()) 
		removeFront();
}

bool LinkedList::empty()
{
    if(!head)
        return true;
}

Node *LinkedList::copyNodes(Node *head) const {
	if (!head) return 0;
	return new Node(head->data, copyNodes(head->next)); 
}

Node *LinkedList::find(Node *head, const EType &val) const {
	if (!head) return 0;
	if (head->data == val) return head;
	return find(head->next, val);
}

int LinkedList::getSize(Node *head) const 
{
//    Node *x = head->next;
//    while(!head)
    return head ? getSize(head->next) + 1 : 0;
}

int LinkedList::size()
{
//    while(!head->prev)
//    return head ? getSize(head->next) + 1 : 0;
    int x;
    Node *y = head;
    while(y->next)
    {
      y = y->next;
      x++;
    }
    return x;
}
