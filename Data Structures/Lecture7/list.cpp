#include <iostream>
#include <sstream>
#include <list>

using namespace std;

template <typename T>
string toString(T num)
{
    ostringstream oss;
    oss << num;
    return oss.str();
}

template <typename T>
ostream &operator <<(ostream &os, list<T> &l) {
	list<T> hold;
	os << "[";
	while (!l.empty()) {
		T t = l.front();
		hold.push_front(t);
		l.pop_front();
		os << t << (!l.empty() ? ", " : "");
	}
	os << "]";
	while (!hold.empty()) {
		l.push_front(hold.front());
		hold.pop_front();
	}
	return os;
}

int main()
{
    cout << "List Demo: Insertion Anywher(only front/back in this demo)" << endl << endl;
    
    list<int> li;
    
    for (int i = 0; i < 20; i++)
	{
		li.push_front(i);
    }
    
    cout << "List of 20 Integers" << endl;
    cout << li << endl;
    
   	while (!li.empty()) {
		li.pop_back();
		cout << li << endl;
	}
    
   	const int ARR_SIZE = 4;
	string arr[ARR_SIZE] = {"cat", "dog", "cow", "elephant"};

	cout << endl;

	list<string> ls;

	for (int i = 0; i < ARR_SIZE; i++)
		ls.push_back(arr[i]);

    cout << "List of 4 Strings" << endl;
	cout << ls << endl;

	while (!ls.empty()) {
		ls.pop_front();
		cout << ls << endl;
	}
	
	cout << endl;
	
	for(int i = 0; i < ARR_SIZE; i++)
	{
	    ls.push_back(toString(i));
    }
    
    cout << "List of 4 Integers converted to Strings" << endl;
    cout << ls << endl;
    
    while(!ls.empty())
    {
        ls.pop_front();
        cout << ls << endl;
    }
    
    return(0);
}
