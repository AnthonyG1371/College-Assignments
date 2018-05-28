#include <iostream>

#include "node.h"
#include "node_utils.h"

using namespace std;

int main() {
    
	Node *list = new Node(1, new Node(3, new Node(5)));
	
	//Prints Lists Contents
	cout << "Initial List of Nodes 1,3,5" << endl;
	Node *templist = list;
	while (list) {
		cout << *list;
		list = list->next;
		if (list) cout << " -> ";
	}
	list = templist;
	cout << endl << endl;

    insert(list, 2);
	
	cout << "Testing Insertion of 2: " << endl;
	while (list) {
		cout << *list;
		list = list->next;
		if (list) cout << " -> ";
	}
	
	list = templist;
	newremove(list, 5);
	cout << endl << endl;
	
	cout << "Testing Removal of 5:" << endl;
	while (list) {
		cout << *list;
		list = list->next;
		if (list) cout << " -> ";
	}
	cout << endl << endl;
	
    system("pause");
	return 0;
}
