//This program contains C-string Parts 1 and both parts of C++ Strings for Lab 2
//C-String Part 2 is in a seperate program

#include<iostream>
#include<string>
#include<cstring>
#include<cctype>
using namespace std;

const int LEN = 100;

void string_replace(char *,char);
void readstrings(string, string);
string * studentnum(int &);
void displaynames(string *, int);

int main()
{

  char *s = new char[LEN];
  char c;
  string s1, s2;
  string * names;
  int students = 0;

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

//Part 2-1
  cin.ignore();
  readstrings(s1, s2);

//Part 2-2
  names = studentnum(students);

  if (students != 0)
  {
    displaynames(names, students);
  }

  delete[] names;
  return (0);
}//END OF MAIN


//Part 1-1     Function to replace any occurence of c in s with its uppercase equivalent
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

//Part 2-2  Function to get the number of students in the class and their names in a dynamic array
string * studentnum(int &students)
{
  string * names;

  cout << "C++ Strings Part 2\n";
  cout << "How many students are in this class? ";
  cin >> students;

  if (students == 0)
  {
    cout << "How in the world are there no students!?\n\n";
    return(0);
  }

  names = new string[students];

  for(int i = 0; i < students; i++)
  {
    cout << "Enter student " << i+1 << "'s name: ";
    cin >> names[i];
  }

  return names;
}

//Function to display the names of the students in the class
void displaynames(string *names, int students)
{
  cout << "\n---List of students in the class---\n\n";
  for(int i = 0; i < students; i++)
  {
    cout << names[i] << endl;
  }
  cout << endl;
  system("pause");
}
