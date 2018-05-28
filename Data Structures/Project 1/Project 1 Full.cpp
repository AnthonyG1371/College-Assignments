#include <iostream>
#include <fstream>
using namespace std;

ifstream infile;
ofstream outfile;

int main()
{
  string id, lastn, firstn, major, department, oldid;
  int courses, mcredits, coursid, credits, totalc;
  double gpa, mgpa;
  char grade;
  
  infile.open("students.txt");
  outfile.open("deansList.txt");
    
  if(!infile)
  {
    cout << "Error 404: File cannot be found\n";
    infile.close();
 	return(0);
  }
  while(!infile.eof())
  {
    infile >> id;
    if(id == oldid)
      break;
    oldid = id;
    infile >> lastn;
    infile >> firstn;
    infile >> major;
    
    cout << id << " " << lastn << ", " << firstn << "     Major: " << major << endl;;
    
    infile >> courses;

    totalc = 0;
    mcredits = 0;
    gpa = 0;
    mgpa = 0;
    
    if(courses == 0)
    {
      cout << "This student has no grades in transcript data." << endl << endl;
    }
    else
    {
      for(int i = 0; i < courses; i++)
      {
        infile >> department;
        infile >> coursid;
        infile >> credits;
        infile >> grade;
       
        if(department == major)
          mcredits += credits;
      
        totalc += credits;
      
        switch(grade)
        {
          case 'A':
            gpa = gpa + (4 * credits);
            if(department == major)
              mgpa = mgpa +(4 * credits);
            break;
          case 'B':
            gpa = gpa + (3 * credits);
            if(department == major)
              mgpa = mgpa +(3 * credits);
            break;
          case 'C':
            gpa = gpa + (2 * credits);
            if(department == major)
              mgpa = mgpa +(2 * credits);
            break;
          case 'D':
            gpa = gpa + (1 * credits);
            if(department == major)
              mgpa = mgpa +(1 * credits);
            break;
          case 'F':
            //There is no code for this section because no credits are added to the gpa.
            break;
        }
      }
              
        gpa = gpa / totalc;

        if(gpa >= 3)
        {
          outfile << id << " " << lastn << ", " << firstn << "     GPA: " << gpa << endl;
        }
      
        if(mcredits == 0)
          cout << "The student has taken no major courses yet." << endl;
        else
          mgpa = mgpa / mcredits;
      
        cout << "Completed Credits: " << totalc << "    GPA: " << gpa << "    Major GPA: " << mgpa << endl << endl;      
    }
  }

  system("pause");
  return(0);
}
