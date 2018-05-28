#ifndef NODE_H
#define NODE_H

#include <iostream>

typedef int EType;

struct Node {
	friend std::ostream &operator <<(std::ostream &os, const Node &node) {
		os << '[' << node.data << " | #" << node.next << "  | #" << node.prev << ']';
		return os;
	}
	Node(const EType &data, Node *next=0, Node *prev=0) : data(data), next(next), prev(prev) {}
	EType data;
	Node *next;
	//Added previous node
	Node *prev;
};

#endif
