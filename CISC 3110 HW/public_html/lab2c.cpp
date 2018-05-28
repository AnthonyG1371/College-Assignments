//This program contains C++ Strings part 1 for Lab 2

#include<iostream>
#include<string>

using namespace std;

void readstrings(string, string);

int main()
{

  string s1, s2;

//Part 2-1
  readstrings(s1, s2);

  return (0);
}//END OF MAIN

//Part 2-1     Function to read in 2 strings and determine how many times the second string appears in the first
void readstrings(string s1, string s2)
{
  int pos = 0;
  int findnum = 0;

  cout << "C++ Strings Part 1\n";
  cout << "Enter in a string: ";
  getline(cin, s1);
  cout << s1 << endl << endl;

  cout << "Enter in another string. This program will determine how many \ntimes this one appears in the first string: ";
  getline(cin, s2);
  cout << s2 << endl;

  int size1 = s1.length();

  while(pos < size1)
  {
    std::size_t found = s1.find(s2, pos);
    if (found == string::npos)
    {
      pos = size1;
    }
    else
    {
      findnum += 1;
      pos = found+1;
    }
  }

  cout << "\nNumber of matches: " << findnum << endl;
  cout << endl;
  system("pause");
  system("cls");
}
