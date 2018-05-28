//This program contains C++ Strings part 2 for Lab 2

#include<iostream>
#include<string>

using namespace std;

string * studentnum(int &);
void displaynames(string *, int);

int main()
{

  string * names;
  int students = 0;

//Part 2-2
  names = studentnum(students);

  if (students != 0)
  {
    displaynames(names, students);
  }
  
  system("pause");
  delete[] names;
  return (0);
}//END OF MAIN

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
}
