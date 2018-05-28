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
ostream &operator <<(ostream &os, queue<T> &q) {
	queue<T> hold;
	os << "[";
	while (!q.empty()) {
		T t = q.front();
		hold.push(t);
		q.pop();
		os << t << (!q.empty() ? ", " : "");
	}
	os << "]";
	while (!hold.empty()) {
		q.push(hold.front());
		hold.pop();
	}
	return os;
}

int main()
{
    cout << "Queue Demo: First in First out" << endl << endl;
    
    queue<int> qi;
    
    for (int i = 0; i < 20; i++)
	{
		qi.push(i);
    }
    
    cout << "Queue of 20 Integers" << endl;
    cout << qi << endl;
    
   	while (!qi.empty()) {
		qi.pop();
		cout << qi << endl;
	}
    
   	const int ARR_SIZE = 4;
	string arr[ARR_SIZE] = {"cat", "dog", "cow", "elephant"};

	cout << endl;

	queue<string> qs;

	for (int i = 0; i < ARR_SIZE; i++)
		qs.push(arr[i]);

    cout << "Queue of 4 Strings" << endl;
	cout << qs << endl;

	while (!qs.empty()) {
		qs.pop();
		cout << qs << endl;
	}
	
	cout << endl;
	
	for(int i = 0; i < ARR_SIZE; i++)
	{
	    qs.push(toString(i));
    }
    
    cout << "Queue of 4 Integers converted to Strings" << endl;
    cout << qs << endl;
    
    while(!qs.empty())
    {
        qs.pop();
        cout << qs << endl;
    }
    
    return(0);
}
