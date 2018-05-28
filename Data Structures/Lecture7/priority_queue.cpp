#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

template <typename T>
string toString(T num)
{
    ostringstream oss;
    oss << num;
    return oss.str();
}

template <typename T>
ostream &operator <<(ostream &os, priority_queue<T> &p) {
	priority_queue<T> hold;
	os << "[";
	while (!p.empty()) {
		T t = p.top();
		hold.push(t);
		p.pop();
		os << t << (!p.empty() ? ", " : "");
	}
	os << "]";
	while (!hold.empty()) {
		p.push(hold.top());
		hold.pop();
	}
	return os;
}

int main()
{
    cout << "Priority Queue Demo: Greatest/Largest at Top" << endl << endl;
    
    priority_queue<int> pi;
    
    for (int i = 0; i < 20; i++)
	{
		pi.push(i);
    }
    
    cout << "Priority Queue of 20 Integers" << endl;
    cout << pi << endl;
    
   	while (!pi.empty()) {
		pi.pop();
		cout << pi << endl;
	}
    
   	const int ARR_SIZE = 4;
	string arr[ARR_SIZE] = {"cat", "ridiculousness", "elephant", "rodent"};

	cout << endl;

	priority_queue<string> ps;

	for (int i = 0; i < ARR_SIZE; i++)
		ps.push(arr[i]);

    cout << "Piority Queue of 4 Strings: In order of the first letter, NOT the string length" << endl;
	cout << ps << endl;

	while (!ps.empty()) {
		ps.pop();
		cout << ps << endl;
	}
	
	cout << endl;
	
	for(int i = 0; i < ARR_SIZE; i++)
	{
	    ps.push(toString(i));
    }
    
    cout << "Priority Queue of 4 Integers converted to Strings" << endl;
    cout << ps << endl;
    
    while(!ps.empty())
    {
        ps.pop();
        cout << ps << endl;
    }
    
    return(0);
}
