#include <iostream>
#include <sstream>
#include <deque>

using namespace std;

template <typename T>
string toString(T num)
{
    ostringstream oss;
    oss << num;
    return oss.str();
}

template <typename T>
ostream &operator <<(ostream &os, deque<T> &d) {
	deque<T> hold;
	os << "[";
	while (!d.empty()) {
		T t = d.front();
		hold.push_front(t);
		d.pop_front();
		os << t << (!d.empty() ? ", " : "");
	}
	os << "]";
	while (!hold.empty()) {
		d.push_front(hold.front());
		hold.pop_front();
	}
	return os;
}

int main()
{
    deque<int> di;
    bool odd = false;
    
    cout << "Deque Demo: Double ended and alternating here" << endl << endl;
    
    for (int i = 0; i < 20; i++)
	{
		if (odd == false){odd = true; di.push_front(i);}
		else{odd = false; di.push_back(i);}
    }
    
    cout << "Deque of 20 Integers" << endl;
    cout << di << endl;
    
   	while (!di.empty()) {
        if(odd == false){odd = true; di.pop_back();}
        else{odd = false; di.pop_front();}

		cout << di << endl;
	}
    
   	const int ARR_SIZE = 4;
	string arr[ARR_SIZE] = {"cat", "dog", "cow", "elephant"};

	cout << endl;

	deque<string> ds;

	for (int i = 0; i < ARR_SIZE; i++)
	{
        if(odd == false){odd = true; ds.push_back(arr[i]);}
		else{odd = false; ds.push_front(arr[i]);}
    }

    cout << "Deque of 4 Strings" << endl;
	cout << ds << endl;

	while (!ds.empty()) {
		if(odd == false){odd = true; ds.pop_front();}
		else{odd = false; ds.pop_back();}
		cout << ds << endl;
	}
	
	cout << endl;
	
	for(int i = 0; i < ARR_SIZE; i++)
	{
	    if(odd == false){odd = true; ds.push_back(toString(i));}
	    else{odd = false; ds.push_front(toString(i));}
    }
    
    cout << "Deque of 4 Integers converted to Strings" << endl;
    cout << ds << endl;
    
    while(!ds.empty())
    {
        if(odd == false){odd = true; ds.pop_front();}
        else{odd = false; ds.pop_back();}
        cout << ds << endl;
    }
    
    return(0);
}
