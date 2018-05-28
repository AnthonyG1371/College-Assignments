#include <iostream>
#include <string>
#include <list>
using namespace std;

////////////////////////
//Arithmetic Functions//
////////////////////////

//Successor: x+1
template<typename T>
T succ(T x)
{
  x = x+1;
  return x;
}

//Predecessor: x-1
template<typename T>
T pred(T x)
{
  x = x-1;
  return x;
}

//Recursively calls succ exactly x times on y
template<typename T>
T add(T x, T y)
{
  if(x == 0)
    return y;
  //cout << x << " " << y << endl;
  return succ(add(pred(x),y));
}

//Subtraction: Recursively calls pred on both x and y until y equals 0. Now it does work for negative y numbers.
template<typename T>
T sub(T x, T y)
{
  if(y == 0)
    return x;
  //cout << x << " " << y << endl;
  if(y > 0)
    return sub(pred(x),pred(y));
  else if(y < 0)
    return sub(pred(x),succ(y));
}

//Multiplication
template<typename T>
T mult(T x, T y)
{
  if(x == 0 || y == 0)
  {
  	return 0;
  }
  return add(mult(pred(x),y),y);
}

//All 5 Predicates
template<typename T>
bool le (T x, T y)
{
  if(x == 0)
    return true;
  if(y == 0)
    return false;
  le(pred(x), pred(y));
}

template<typename T>
bool lt(T x, T y)
{
	le(succ(x), y);
}

template<typename T>
bool gt(T x,T y)
{
  lt(y, x);
}

template<typename T>
bool ge(T x, T y)
{
  le(y, x);
}

template<typename T>
bool eq(T x, T y)
{
  if(ge(x, y) == ge(y, x))
    return true;
  return false;
}

//Division
template<typename T>
T div(T x, T y)
{
  if(lt(x,y) == true)
  {
  	cout << "Undefined" << endl;
  	return 0;
  }
  //cout << x << " " << y << endl;
  succ(div(sub(x,y),y));
}

//Remainder
template<typename T>
T rem(T x, T y)
{
  if(lt(x,y) == true)
  {
  	return x;
  }
  //cout << x << " " << y << endl;
  rem(sub(x,y),y);
}

//Exponent: Decrements y while multiplying x until y = 0
template<typename T>
T expo(T x, T y)
{
  if(y == 0)
  {
  	return succ(0);
  }
  //cout << x << " " << y << endl;
  mult(x,expo(x,pred(y)));
}

//Factorial: Decrements x, multiples each decrement until x = 0 (does not multiply by 0);
template<typename T>
T fact(T x)
{
  if(x == 0)
  {
  	return 1;
  }
  //cout << x << endl;
  mult(x,fact(pred(x)));
}

//Greatest Common Denominator
template<typename T>
T gcd(T x, T y)
{
  if(x == 0)
  	return y;
  if(y == 0)
    return x;
  //cout << x << endl;
  gcd(y,rem(x,y));
}


//Fibonacci
template<typename T>
T fib(T x)
{
  if(x == 0)
  	return 0;
  else if (x == 1 || x == 2)
    return succ(0);
  //cout << x << endl;
  add(fib(pred(x)),fib(pred(pred(x))));
}

////////////////////////////
//     LIST FUNCTIONS     //
////////////////////////////

//Front
template<typename T>
T first(list<T> L)
{
  return L.front();
}

//Last
template<typename T>
T last(list<T>& L, typename list<T>::iterator itr)
{
  if(itr == L.end())
  {
    itr--;
    return *itr;
  }
  itr++;
  last(L, itr);
}

//Contains
template<typename T>
bool contains(list<T> &L, T elm, typename list<T>::iterator itr)
{
  if(*itr == elm)
    return true;
  if(itr == L.end())
    return false;
  itr++;
  contains(L, elm, itr);

}

//Find First Of
template<typename T>
int find_first_of(list<T> &L, T elm, int i, typename list<T>::iterator itr)
{
  if(L.empty() == true || itr == L.end())
    return -1;
  if(*itr == elm)
    return i;
  itr++;
  i++;
  find_first_of(L, elm, i, itr);
}

//Find Last Of
template<typename T>
int find_last_of(list<T> &L, T elm, int current, int index, typename list<T>::iterator itr)
{
  if(L.empty() == true)
    return -1;
  if(*itr == elm)
    index = current;
  if(itr == L.end())
    return index;
  itr++;
  current++;
  find_last_of(L, elm, current, index, itr);
}

//Find Kth element
template<typename T>
T kth_elm(list<T> &L, int k, typename list<T>::iterator itr)
{
  if(L.empty() == true || k < 0 || k > L.size())
    return -1;
  if(k == 0)
  {
  	return *itr;
  }
  itr++;
  k--;
  kth_elm(L, k, itr);
}

//Length
template<typename T>
int length(list<T> &L, int i, typename list<T>::iterator itr)
{
  if(L.empty())
    return 0;
  if(itr == L.end())
    return i;
  itr++;
  i++;
  length(L, i, itr);
}

//Reverse
template<typename T>
list<T>* reverse(list<T> &L, list<T> * &R, typename list<T>::iterator itr)
{
  if(itr == L.end())
    return R;
  //cout << *itr;
  R->push_front(*itr);
  itr++;
  reverse(L, R, itr);
}

//Test Program, take off comments to test
int main()
{
  int x = 56, y = 104, z = 0;
  //z = add(x,y);
  //z = sub(x,y);
  //z = mult(x,y);
  //z = div(x,y);
  //z = rem(x,y);
  //z = fact(x);
  //z = gcd(x,y);
  //z = fib(x);
  //cout << z << endl;

  char chararr[] = {'a','b','z','e','k','e'};
  list<char> L (chararr, chararr + sizeof(chararr) / sizeof(char));
  //cout << last(L, L.begin());
  //cout << contains(L, 'e', L.begin());
  //cout << find_first_of(L, 'e', 1, L.begin());
  //cout << find_last_of(L,'e',1,-1,L.begin());
  //cout << kth_elm(L, 2, L.begin());
  //cout << length(L, 0, L.begin());
  list<char> * R = new list<char>[1];
  R = reverse(L, R, L.begin());
  for(list<char>::iterator itr = R->begin(); itr != R->end(); itr++)
    cout << *itr;
  return 0;
}
