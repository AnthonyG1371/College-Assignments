#ifndef NODE_H
#define NODE_H

#include <iostream>

typedef int EType;

struct Node {
	friend std::ostream &operator <<(std::ostream &os, const Node &node) {
		// Swap commented-out lines for a less/more detailed display of the node (includes node's address)
		//os << "#" << &node << "[" << node.data << " | " << (void *)node.next << "]";
		os << "[" << node.data << " | " << (void *)node.next << "]";
		return os;
	}
	Node(const EType &data, Node *next=0) : data(data), next(next) {}
	EType data;
	Node *next;
};

#endif
