#include <iostream>
#include <iomanip>

#include "linked_list.h"

using namespace std;

int main() {
	LinkedList li;

	cout << boolalpha;
	cout << li << endl;
//	cout << "size: " << li.getSize() << endl;
//	cout << "isEmpty: " << li.isEmpty() << endl;
//	cout << "contains(3): " << li.contains(3) << endl;
	cout << endl;

//    li.insertFront(NULL);
//    li.insertFront(1);
//    li.insertFront(1);
//	li.insertFront(0);
li.insert(li.head, 0);
/*	cout << li << endl;
	cout << "size: " << li.getSize() << endl;
	cout << "isEmpty: " << li.isEmpty() << endl;
	cout << "contains(3): " << li.contains(3) << endl;
	cout << "contains(20): " << li.contains(20) << endl;
*/	cout << endl;
	
//	li.remove(li.head);

	Node *p = li.head;
//    li.insertAfter(li.head, 2);
 //  	Node *p = 
	li.insert(p, 20);
	Node *q = p->next;
	li.insertAfter(q, 15);
	Node *r = q->next;
	li.insertAfter(q, 5);
		Node *s = q->next;
//    r->next = li.head;
//    li.head->prev = r;
//li.insertAfter(li.head->next, 2);
//li.insert(li.head, 5);
//if(r->next == NULL)
	cout << endl << s->prev->data << endl;

	cout << li << endl;
//	cout << r->next->data << endl;
	cout << q->next->data <<endl;

	cout << "size: " << li.size() << endl;
	cout << li.remove(q) << endl;
	cout << li << endl;
	cout << "Empty? " << li.empty() << endl;
	li.clear();
	cout << li << endl;
		cout << "Empty: " << li.empty() << endl;
/*	cout << "isEmpty: " << li.isEmpty() << endl;
	cout << "contains(3): " << li.contains(3) << endl;
	cout << "contains(20): " << li.contains(20) << endl;
	cout << "contains(17): " << li.contains(17) << endl;
	cout << endl;

	LinkedList li2 = li;
	cout << "After li2 declaration and copy constructor: " << endl;
	cout << "li: " << li << endl;
	cout << "li2: " << li2 << endl;
	cout << endl;

	LinkedList li3;
	cout << "After li3 declaration: " << endl;
	cout << "li3: " << li3 << endl;
	li3 = li;
	cout << "After li3 = li assignment: " << endl;
	cout << "li: " << li << endl;
	cout << "li3: " << li3 << endl;
	cout << endl;

	li.insertFront(17);
	cout << li << endl;
	cout << "size: " << li.getSize() << endl;
	cout << "isEmpty: " << li.isEmpty() << endl;
	cout << "contains(3): " << li.contains(3) << endl;
	cout << "contains(20): " << li.contains(20) << endl;
	cout << "contains(17): " << li.contains(17) << endl;
	cout << "contains(57): " << li.contains(57) << endl;
	cout << endl;

	cout << "li: " << li << endl;
	cout << "li2: " << li2 << endl;
	cout << "li3: " << li3 << endl;
*/  
    system("pause");
	return(0);
}
