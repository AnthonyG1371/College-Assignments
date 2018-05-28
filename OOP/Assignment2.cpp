#include<iostream>
#include<deque>
#include<list>
#include<stack>
#include<unordered_map>
#include<random>
using namespace std;

int numzeros(list<int>, int);
list<int> maxmin(list<int>, int);
void printpascal(int);
bool symarray();
void reversePolCal();
void hashstrings();
void uniqueroot();

//OBJECT OF TWO STRINGS
class strpair
{
public:
    strpair(string x, string y)
    {
        a = x;
        b = y;
    }
    string geta()
    {
        return a;
    }
    string getb()
    {
        return b;
    }
private:
    string a;
    string b;
};

int main()
{
    cout << "1 & 2: " << endl;
    int size, num;
    cout << "Enter Size of List: ";
    cin >> size;

    int basearr[size];
    for(int i = 0; i < size; i++)
    {
        cout << "Enter an integer number to the list: ";
        cin >> num;
        basearr[i] = num;
    }

//    int basearr[] = {50,3020,200};

	list<int> l(basearr, basearr + sizeof(basearr) / sizeof(int));
	int countzeros = numzeros(l,3);
	cout << "Number of Zeros in the list: " << countzeros << endl;

	list<int> relist = maxmin(l,3);
	cout << "Maximum: " << relist.front() << "   Minimum: " << relist.back() << endl;

    int rows;
    cout << endl << "3:" << endl;
    cout << "To which row of Pascal's Triangle do you want to print?" << endl;
    cout << "0 is the minimum value: ";
    cin >> rows;
	printpascal(rows);

	if(symarray())
    {
        cout << "The 2D arrays was symmetrical." << endl;
    }
    else
        cout << "The 2D array was not symmetrical." << endl;

    reversePolCal();

	hashstrings();

	uniqueroot();

	return 0;
}
//END OF MAIN

int numzeros(list<int> l, int size)
{
    int countzeros = 0;

	for(list<int>::iterator i=l.begin(); i != l.end(); i++)
	{
	    //cout << *i << endl;
	    while(*i / 10 != 0)
        {
	      if(*i % 10 == 0)
	        countzeros++;
          *i = *i / 10;
        }
	}
	return countzeros;
}

list<int> maxmin(list<int> l, int size)
{
    int max, min;
    max = l.front();
    min = l.front();

    for(list<int>::iterator i=l.begin(); i != l.end(); i++)
	{
	    if(*i > max)
            max = *i;
        if(*i < min)
            min = *i;
	}

	int arr[] = {max,min};

	list<int> relist(arr, arr + sizeof(arr) / sizeof(int));
	delete [] arr;

    return relist;
}

void printpascal(int n)
{
    if(n < 0)
    {
        cout << "You were supposed to enter a number of at least 0 or greater";
        return;
    }
    else if(n == 0)
    {
        cout << "1" << endl;
        return;
    }
    else if(n == 1)
    {
        cout << "1" << endl;
        cout << "1 1" << endl;
        return;
    }

    deque<int> pascal;
    deque<int> temp;
    temp.assign(1,1);
    pascal.assign(2,1);
    deque<int>::iterator it = pascal.begin();

    cout << temp[0] << endl;
    cout << pascal[0] << " " << pascal[1] << endl;

    for(int i = 2; i < n+1; i++)
    {
        int pos = 0;
        temp = pascal;
        pascal.assign(i+1,0);
        for(it = pascal.begin(); it != pascal.end(); it++)
        {
            if(pos-1 < 0)
                pascal[pos] = temp[pos];
            else if(pos > i-1)
                pascal[pos] = temp[pos-1];
            else
                pascal[pos] = temp[pos-1]+temp[pos];

            cout << *it << " ";
            pos++;
        }
        cout << endl;
	}
}

bool symarray()
{
    int size; int confirmrand; int n;
    cout << endl << "4: " << endl;
    cout << "What is the size of the square array? ";
    cin >> size;

    cout << "Do you want random numbers or not? 1 for yes, 0 for no: ";
    cin >> confirmrand;

	int arr[size][size];

	if(confirmrand == 1)
    {
        for(int i= 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                arr[i][j] = rand()%9;
            }
        }
    }
    else
    {
        for(int i= 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                cout << "Enter the next number in the 2d array: ";
                cin >> n;
                arr[i][j] = n;
            }
        }
    }


	for(int i= 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(arr[i][j] != arr[j][i])
			{
				return false;
			}
		}
	}

	return true;
}

void reversePolCal()
{
    int x, y, z, cint;

    string rpnexp;
    cout << endl << "5: " << endl;
    cout << "Enter an arithmetic expression in Reverse Polis Notation: ";
    cin >> rpnexp;

    stack<char> rpnstack;
    char operatorplus = '+';
    char operatormultiply = '*';
    for(string::iterator it = rpnexp.begin(); it != rpnexp.end(); it++)
    {
        char c = *it;
        if(c != operatorplus && c != operatormultiply)
        {
            cint = int(c)-48;
            rpnstack.push(cint);
        }
        else
        {
            x = int(rpnstack.top());
            rpnstack.pop();
            y = int(rpnstack.top());
            rpnstack.pop();
            if(c == '+')
            {
               // cout << x << " " << y << endl;
                z = x+y;
                rpnstack.push(z);
            }
            else if(c == '*')
            {
                z = x*y;
                rpnstack.push(z);
            }
        }
    }
    cout << "Your answer is " << int(rpnstack.top()) << endl;
}

void hashstrings()
{
    cout << endl << "6: " << endl;
    strpair str1("test", "one");
    strpair str2("round", "two");
    strpair str3("bleh", "three");
    strpair str4("round", "two");
    strpair stringarr[] = {str1, str2, str3,str4};
    //string stringarr[] = {"test","test","one","two", "test", "one"};
    int arrsize = 4; int most = 0,  mostloc = 0;
    int mostobj[arrsize];

    unordered_map<string, string> strmap;

    for(int i = 0; i < arrsize; i++)
    {
        for(int j  = 0; j < arrsize; j++)
        {
            if(stringarr[i].geta() == stringarr[j].geta() && stringarr[i].getb() == stringarr[j].getb())
                mostobj[i]++;
        }
        //strmap.emplace(stringarr[0]);
        strmap.emplace(stringarr[i].geta(),stringarr[i].getb());
    }

    for(int i = 0; i < arrsize; i++)
    {
        if(mostobj[i]> most)
            mostloc = i;
    }
    cout << "Most common string pairs: " << stringarr[mostloc].geta() << " " << stringarr[mostloc].getb() << endl;
}

void uniqueroot()
{
    cout << endl << "7: " << endl;
    //1_2_3_4_5_6_7_8_9_0, where each "_" is a single digit?
    int square;
    for(int i = 0; i < 10; i++)
    {
        switch(i)
        {
            case 0:
                square = 1020304050607080900;
                break;
            case 1:
                square = 1121314151617181910;
                break;
            case 2:
                square = 1222324252627282920;
                break;
            case 3:
                square = 1323334353637383930;
                break;
            case 4:
                square = 1424344454647484940;
                break;
            case 5:
                square = 1525354555657585950;
                break;
            case 6:
                square = 1626364656667686960;
                break;
            case 7:
                square = 1727374757677787970;
                break;
            case 8:
                square = 1828384858687888980;
                break;
            case 9:
                square = 1929394959697989990;
                break;

        }
        cout << "Root using " << i << ": " << sqrt(square) << endl;

    }
}
