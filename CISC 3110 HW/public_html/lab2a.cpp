//This program contains C-string Part 1.
//Originally, C-Strings Part 1 was in the same program as C++ Strings 1 and 2

#include<iostream>
#include<cstring>
#include<cctype>
using namespace std;

const int LEN = 100;

void string_replace(char *,char);

int main()
{

  char *s = new char[LEN];
  char c;

//Part 1-1
  cout << "C Strings Part 1\n";
  cout << "Input a string: ";
  cin.getline(s,LEN);
  cout << "\nEnter a single character. Any occurence of this character in the string \nwill be changed to its uppercase equivalent: ";
  cin >> c;
  string_replace(s, c);
  cout << "Your string is now: " << s << endl << endl;
  system("pause");
  system("cls");
  
  return(0);
}//END OF MAIN

//Part 1-1   Function to replace any occurence of c in s with its uppercase equivalent
void string_replace(char *s,char c)
{
  int slen;
  slen = strlen(s);
  
  for(int i = 0; i < slen; i++)
  {
    if(s[i] == c)
    {
      s[i] = toupper(c);
    }
  }
}
