//This is C-String Part 2 of Lab 2

#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

//function prototypes
void displayRules();
bool validatePasswd(char *passwd);


int main() 
{
  char newpasswd[25];
  bool OK = false;

  while (!OK) 
  {
  cout << "Enter a valid password. To see the password rules, type ? and press enter."<< endl;

  cin >> newpasswd;

//check whether the user entered a ?

// FILL IN MISSING CODE TO DISPLAY RULES IF THE USER ENTERED a ?

  if(newpasswd[0] == '?')
  {
    displayRules();
  }
  else {
     OK = validatePasswd(newpasswd);
     if (OK)
       cout << "Your password has been accepted. "<< endl;
     }
     system("pause");
     system("cls");
  } // end while

return 0;
} // end main

void displayRules()
{

// FILL IN THE MISSING CODE TO DISPLAY THE RULES
cout << "Password Rules:\n";
cout << "The password must be at least 8 characters long.\n";
cout << "The password must contain at least: one alpha character [a-zA-Z]\n";
cout << "one numeric character [0-9]\n";
cout << "one special character from this set: ! $ % ?\n";
cout << "The password must not contain spaces\n";
cout << "The password must not begin with an exclamation [!] or a question mark [?]\n";
cout << "The first 3 characters of the password must not be the same character\n\n";

return;
}

bool validatePasswd(char *passwd)
{
bool OK=false;
bool check = false;

//Check length
  if (strlen(passwd) < 8) //FILL IN THE CONDITION
  { 
   cout << "Length must be at least 8" << endl;
   return false;
  }

//Check for alpha character
//FILL IN CODE HERE. Note: The next 3 tests are very similar to one another.
  for(int i = 0; i < strlen(passwd); i++)
  {
    for(int j = 65; j <= 90; j++)  //Checks all Uppercase ASCII characters
    {
      if(passwd[i] == (char) j)
        check = true;
    }
    for(int j = 97; j <= 122; j++)
    {
      if(passwd[i] == (char) j)
        check = true;
    }
  }
  if(check == false)
  {
    cout << "Your password must contain at least one alpha character" << endl;
    return false;
  }

//Check for numeric character
//FILL IN CODE HERE
  
  check = false;
  for(int i = 0; i < strlen(passwd); i++)
  {
    for(int j = 48; j <= 57; j++)
    {
      if (passwd[i] == (char) j)   //||
        check = true;
    }
  }
  if(check == false)
  {
    cout << "Your password must contain at least one number" << endl;
    return false;
  }

//Check for special character
//FILL IN CODE HERE
  check = false;
  for(int i = 0; i <= strlen(passwd); i++)
  {
    if(passwd[i] == (char) 33 || passwd[i] == (char) 36 || passwd[i] == (char) 37 || passwd[i] == (char) 63)
      check = true;
  }
  if(check == false)
  {
    cout << "Your password must contain one of any of these characters: ?!$%" << endl;
    return false;
  }

// Check that the password does not begin with ? or !
  if (passwd[0]=='?' || passwd[0]=='!')
  {
    cout << "Your password cannot start with ? or !" << endl;
    return false;
  }
  
// Check that there are no spaces in the password
  for(int i = 0; i <= strlen(passwd); i++)
  {
    if(isspace(passwd[i]))
    {
      cout << "Your password cannot contain spaces" << endl;
      return false;
    }
  }
   
// Check that the first 3 characters are not equivalent
//FILL IN CODE HERE
  if(passwd[0] == passwd[1] && passwd[0] == passwd[2] && passwd[1] == passwd[2])
  {
    cout << "The first three characters cannot be the same" << endl;
    return false;
  }

return true;
}
