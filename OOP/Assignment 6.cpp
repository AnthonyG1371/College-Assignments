#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<list>
#include<time.h>
using namespace std;

template <typename T>
void arandinit(T *arr, int n)
{
  for(int i = 0; i < n; i++)
  {
  	int random = rand() % 1000;
  	arr[i] = random;
  }
}

template <typename T>
vector<T> vrandinit(vector<T> &v, int n)
{
  for(int i = 0; i < n; i++)
  {
  	int random = rand() % 1000;
  	v.push_back(random);
  	//v.push_back(i);
  }
  return v;
}

//////////////////////////////////////////
///-------QUESTION 1: Sort Times-------///
//////////////////////////////////////////
clock_t clockstart()
{
  return clock();
}
void clockend(clock_t startT)
{
  clock_t endT = clock();
  cout << "Time the function took: " << difftime(endT, startT) << endl;
}

///BUBBLESORT///
template <typename T>
void bubblesort(T *arr, int n)
{
  for(int i = 0; i < n;i++)
    cout << arr[i] << endl;

  clock_t startT =  clockstart();
  bool swapped = true;
  while(swapped)
  {
    swapped = false;
    for(int i = 0; i < n-1; i++)
    {
      if(arr[i] < arr[i+1])
      {
        T temp = arr[i+1];
        arr[i+1] = arr[i];
        arr[i] = temp;
        swapped = true;
      }
    }
  }

  clockend(startT);
}

///MERGESORT///
template <typename T>
void merge(vector<T> &v, int low, int middle, int high)
{
  vector<T> tempvect;
  int p1 = low;
  int p2 = middle;
  while (p1 < middle && p2 < high)
  {
    if(v[p1] <= v[p2])
    {
      tempvect.push_back(v[p1]);
      p1++;
    }
    else
    {
      tempvect.push_back(v[p2]);
    }
    while(p1 < middle)
    {
      tempvect.push_back(v[p1]);
      p1++;
    }
    while(p2 < high)
    {
      tempvect.push_back(v[p2]);
      p2++;
    }
    for(int i = 0; i < tempvect.size(); i++)
      v[low+i] = tempvect[i];
  }
}
template <typename T>
void mergesort(vector<T> &v, int low, int high)
{
  if(low >= high)
    return;
  int middle = low + (high - low)/2;
  mergesort(v, low, middle);
  mergesort(v, middle, high);
  merge(v, low, middle, high);
}

template <typename T>
void mergesort(vector<T> &v)
{
  clock_t startT  = clockstart();
  mergesort(v, 0, v.size());
  clockend(startT);
}

///QUICKSORT///
template <typename T>
void swap(vector<T> &v, int &s1, int &s2)
{
  int temp = s2;
  s2 = s1;
  s1 = temp;
}

template <typename T>
int partition(vector<T> v, int low, int high)
{
  int middle = low + (high-low)/2;
  T pivot = v.at(middle);
  swap(v, low, middle);
  int f = low+1;
  int b = high-1;
  while(f <= b)
  {
      while(f < b && v.at(f) <= pivot)
        f++;
      while(v.at(b) > pivot)
        b--;
      if(v.at(b) > pivot)
      {
        swap(v, f, b);
        f++;
        b--;
      }
  }
  swap(v, low, b);
  return b;
}

template <typename T>
void quicksort(vector<T> v, int low, int high)
{
  clock_t startT = clockstart();
  if(low >= high)
    return;
  T pivot = partition(v, low, high);
  quicksort(v, low, pivot);
  quicksort(v, pivot, high);
  clockend(startT);
}

//////////////////////////////////////////////////////////////
///-------QUESTION 2: n letter words in a,b alphabet-------///
//////////////////////////////////////////////////////////////
void aplhawordss(list<string> * strlist, string curstr, string prevstr, char alphabet[], int &lcount, int &wordcount, int &n)
{
  char letter;
  int size = 2;

  if(lcount < n)
  {
    prevstr = curstr;
    if(lcount < n)
	{
	  curstr += alphabet[0];
	  lcount++;
	  aplhawordss(strlist, curstr, prevstr, alphabet, lcount, wordcount, n);
    }
	if(lcount < n)
	{
	  curstr = prevstr;
	  curstr += alphabet[1];
	  lcount++;
      aplhawordss(strlist, curstr, prevstr, alphabet, lcount, wordcount, n);
    }
  }

  if(lcount == n)
  {
  	if(curstr.find("aa") == -1)
  	{
      strlist->push_front(curstr);
      cout << curstr << endl;
      wordcount++;
    }
  }
  lcount--;
  curstr = prevstr;
}

void alphawords()
{
  int wordcount = 0; int lcount = 0; int n = 5;
  string curstr = ""; string prevstr = "";
  char alphabet[] = {'a','b'};
  list<string> * strlist = new list<string>;
  //int x = 9/0;
  aplhawordss(strlist, curstr, prevstr, alphabet, lcount, wordcount, n);
}

///////////////////////////////////////////////////////
///-------QUESTION 3: n choose k Combinations-------///
///////////////////////////////////////////////////////
template <typename T>
list<T> copy(list<T> l)
{
  list<T> copylist;
  for(list<int>::iterator itr = l.begin(); itr != l.end(); itr++)
  {
    copylist.insert(itr, *itr);
  }
  return copylist;
}

list<int> coppy(list<int> l)
{
  list<int> copylist;
  for(list<int>::iterator itr = l.begin(); itr != l.end(); itr++)
  {
    copylist.insert(itr, *itr);
  }
  return copylist;
}


template <typename T>
list<list<T>> nsubsets(list<T> l, int n)
{
  //T subset[] = {1,2,3};
  //int n = 2;
  list<T> l2 = copy(l);
  list<T> empty;
  list<list<T>> subsets;

  if(n == 0)
  {
    subsets.push_front(empty);
    return subsets;
  }
  if(l2.size() == n)
  {
    subsets.push_front(l2);
    return subsets;
  }
  T x = l2.back()-1;
  //subsets.insert(nsubsets(l2, n));
  list<T> r;
  //list<T>::iterator itr = r.begin();
  //for(list<T> r; r != n; nsubsets(l2, n-1))
  for(list<int>::iterator itr = r.begin(); itr != r.end(); nsubsets(l2, n-1))
  {
    //r.copy(r);
    r.push_front(x);
    return subsets;
  }
}

/////////////////////////////////////
///-------QUESTION 4: Sudoku-------//
/////////////////////////////////////

bool checkhv(int arr[][9], int n, int row, int col)
{
  for(int i = 0; i < 9; i++)
  {
    if(arr[row][i] == n)
      return false;
    if(arr[i][col] == n)
      return false;
  }
  return true;
}

bool checksection(int sect[][9], int sectnum, int n)
{
  if(sect[sectnum][n] == n)
    return false;
  return true;
}

void sudoku()
{
  int sarr[9][9];
  int sect[9][9];
  int sectnum = 0;
  int previ = -1; int prevj = -1; int prevk = -1;

  for(int i = 0; i < 9; i++)
  {
    for(int j = 0; j < 9; j++)
    {
        sarr[i][j] = -1;
        sect[i][j] = -1;
    }
  }

  sarr[0][0] = 5; sarr[0][1] = 3; sarr[0][4] = 7;
  sarr[1][0] = 6; sarr[1][3] = 1; sarr[1][4] = 9; sarr[1][5] = 5;
  sarr[2][1] = 9; sarr[2][2] = 8; sarr[2][7] = 6;
  sarr[3][0] = 8; sarr[3][4] = 6; sarr[3][8] = 3;
  sarr[4][0] = 4; sarr[4][3] = 8; sarr[4][5] = 3; sarr[4][8] = 1;
  sarr[5][0] = 7; sarr[5][4] = 2; sarr[5][8] = 6;

  for(int i = 0; i < 9; i++)
  {
    for(int j = 0; j < 9; j++)
    {
      if(sarr[i][j] == -1)
      {
        for(int k = 1; k <= 9; k++)
        {
          sectnum = i/3*3 + j/3;
          if(checkhv(sarr, k, i, j) == true && checksection(sect, sectnum, k) == true)
          {
            sarr[i][j] = k;
            previ = i;
            prevj = j;
            break;
          }
          //COMMENT OUT THIS IF STATEMENT TO REMOVE BACKTRACKING
          //BACKTRACKING WILL TAKE A LONG TIME DUE TO THE EXPONENTAIL
          //NATURE OF THIS METHOD
          if(k == 9)
          {
            //cout << "Working, this will take a long time" << endl;
            prevk = sarr[previ][prevj];
            k = prevk;
            i = previ; j = prevj;
            if(i == -1 || j == -1 || k == -1)
            {
              cout << "Puzzle Failed" << endl;
              return;
            }
          }
        }
      }
    }
  }

  for(int i = 0; i < 9; i++)
  {
    for(int j = 0; j < 9; j++)
    {
        cout << sarr[i][j] << " ";
    }
    cout << endl;
  }
}

int main()
{
  ///QUESTION1
  vector<int> v;
  v = vrandinit(v, 15);
  int arr[15];
  arandinit(arr, 15);
  int i = 0;

  bubblesort(arr, 15);
  mergesort(v);
  quicksort(v, 0, 14);

  while(i<15)
  {
  	cout << arr[i] << endl;
	i++;
  }

  ///QUESTION2
  //alphawords();

  ///QUESTION3 (may be unstable)
  //list<int> l;
  // list<list<int>> result;
  //l.push_front(1); l.push_front(2); l.push_front(3);
  //result = nsubsets(l, 2);
  //for(list<list<int>>::iterator itr = result.begin(); itr != result.end(); itr++)
  //  cout << *itr;

  ///QUESTION4
  //sudoku();
  return 0;
}

