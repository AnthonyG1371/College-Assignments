#include"car.h"
#include<iostream>
#include<string.h>
//PART 1 FUNCTIONS
car::car()
{
  year = 0;
  make = "";
  speed = 0;
}

car::car(int cyear, string cmake)
{
  year = cyear;
  make = cmake;
  speed = 0;
}

void car::dispspeed()
{
  cout << "The car's current speeed is " << speed << endl;
}

void car::dispyear()
{
  cout << "Car's Year: " << year << endl;
}
void car::dispmake()
{
  cout << "Car's Make: " << make << endl;
}

int car::getspeed()
{
  return(speed);
}

int car::getyear()
{
  return(year);
}

string car::getmake()
{
  return(make);
}

int car::accelerate()
{
  speed += 1;
}

int car::brake()
{
  speed -= 5;
  if(speed < 0)
    speed = 0;
}

int car::changeyear(car ncar, int nyear)
{
  year = nyear;
  return(year);
}

string car::changemake(car ncar, string nmake)
{
  make = nmake;
  return(make);
}

//PART B FUNCTIONS
int PriceperDay(car Car)
{
  if(Car.getyear() > 2)
    return(55);
  else
    return(100);
}

int accelerate_by(car &Car, int accel)
{
  for(int i = 0; i < accel; i++)
    Car.accelerate();
}

//The difference between this and the pass by value in part 1 is that this will 
//make it so that you should not be able to modify the sent parameter. In addition,
//this function will not create a copy of the parameters every time the funtion
//is called, possibly saving time while running the program.
int PriceperDay2(const car &Car)
{
  if(Car.getconstyear() > 2)
    return(55);
  else
    return(100);
}

int car::getconstyear() const
{
  return(year);
}

car GetanewCar()
{
  int nyear;
  string nmake;
  
  cout << "We are now going to 'get a new car'. Please enter its data" << endl;

  cout << "What is the year of the new car? ";
  cin >> nyear;
  cout << "What is the make of the new car? ";
  cin >> nmake;

  car newcar(nyear, nmake);
  return(newcar);
}
 
//PART 3 FUNCTIONS
Carrental::Carrental()
{
//  As Carinfo is of object car, it automatically instantiates by default
//  Carinfo.car();
//  Carinfo.changeyear(Carinfo, 0);
//  Carinfo.changemake(Carinfo, "");
//  Carinfo.speed = 0;
  cost = 0.00;
  milage = 0;
  available = 0;
  cout << Carinfo.getyear() << endl;
}

Carrental::Carrental(int cyear, string cmake, int cmilage, double ccost)
{
  Carinfo.changemake(Carinfo, cmake);
  Carinfo.changeyear(Carinfo, cyear);
  milage = cmilage;
  cost = ccost;
  available = 1;
}

bool Carrental::isavailable()
{
  if(available = 1)
    return(true);
  return(false);
}

string Carrental::cartype(Carrental rent)
{
  return(rent.Carinfo.getmake());
}

void Carrental::dispmembers()
{
  cout << "Car's Year: " << Carinfo.getyear() << endl;
  cout << "Car's Milage: " << milage << endl;
  cout << "Car's Cost: " << cost << endl;
}
