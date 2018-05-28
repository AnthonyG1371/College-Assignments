#include <iostream>
#include <sstream>
#include <stack>

using namespace std;

template <typename T>
string toString(T num)
{
    ostringstream oss;
    oss << num;
    return oss.str();
}

template <typename T>
bool contains(stack<T> si , T x)
{     
     while(si.empty() != true)
     {
          if(si.top() == x)
            return true;
          si.pop();
     }
     return false;
}

template <typename T>
ostream &operator <<(ostream &os, stack<T> &s) {
	stack<T> hold;
	os << "[";
	while (!s.empty()) {
		T t = s.top();
		hold.push(t);
		s.pop();
		os << t << (!s.empty() ? ", " : "");
	}
	os << "]";
	while (!hold.empty()) {
		s.push(hold.top());
		hold.pop();
	}
	return os;
}

int main() {
	cout << boolalpha;
    cout << "Stack Demo: Last in First Out" << endl << endl;

	stack<int> si;

	for (int i = 0; i < 20; i++)
	{
		si.push(i);
    }

    cout << "Stack of 20 Integers" << endl;
	cout << "si contains 15: " << contains(si, 15) << endl;
	cout << "si contains 23: " << contains(si, 23) << endl;

	cout << si << endl;

	while (!si.empty()) {
		si.pop();
		cout << si << endl;
	}


	const int ARR_SIZE = 4;
	string arr[ARR_SIZE] = {"cat", "dog", "cow", "elephant"};

	cout << endl;

	stack<string> ss;

	for (int i = 0; i < ARR_SIZE; i++)
		ss.push(arr[i]);

    cout << "Stack of 4 Strings" << endl;
    cout << "ss contains \"dog\": " << contains(ss, string("dog")) << endl;
	cout << "ss contains \"muskrat\": " << contains(ss, string("muskrat")) << endl;

	cout << ss << endl;

	while (!ss.empty()) {
		ss.pop();
		cout << ss << endl;
	}
	
	cout << endl;
	
	for(int i = 0; i < ARR_SIZE; i++)
	{
	    ss.push(toString(i));
    }
    
    cout << "Stack of 4 Integers converted to Strings" << endl;
    cout << "ss contains 3: " << contains(ss, string("2")) << endl;
    cout << "ss contains 7: " << contains(ss, string("7")) << endl;
    cout << ss << endl;
    
    while(!ss.empty())
    {
        ss.pop();
        cout << ss << endl;
    }

	return 0;
}
