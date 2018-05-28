#ifndef LINKED_LIST_EXCEPTION_H
#define LINKED_LIST_EXCEPTION_H

#include <iostream>
#include <string>

class LinkedListException {
	friend std::ostream &operator <<(std::ostream &os, const LinkedListException &e) {
		os << "*** LinkedListException *** " << e.message;
		return os;
	}
public:
	LinkedListException(std::string message) : message(message) {}
private:
	 std::string message;
};

#endif
