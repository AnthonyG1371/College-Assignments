#include"car.h"
#include<iostream>
#include<string.h>
//MAIN
int main()
{
  int cyear, cspeed, price, accel, cmilage;
  double ccost;
  string cmake;
  
//PART 1 MAIN

  cout << "Part 1: Instantiate/Change speed of Car Object" << endl << endl;
  cout << "What is the car's year? ";
  cin >> cyear;

  cout << "What is the car's make? ";
  cin >> cmake;

  //Initializing the object with constructor
  car Car(cyear, cmake);

  cout << "How fast do you want to go? Please enter an integer: ";
  cin >> cspeed;

  for(int i = 0; i < cspeed; i++)
  {
    Car.accelerate();
  }
  Car.dispspeed();

  cout << "We will now decelerate your car by 5 twice" << endl;
  Car.brake();
  Car.brake();
  Car.dispspeed();

  Car.dispmake();
  Car.dispyear();

//PART B MAIN
  cout << endl << "Part B: Functions using the Car class" << endl << endl;
  price = PriceperDay(Car);
  cout << "The car's price is determined by it's year" << endl;
  cout << "Car's Price: " << price << endl;

  cout << "By how much do you want to speed up your car? ";
  cin >> accel;
  accelerate_by(Car, accel);
  cout << "Speed: " << Car.getspeed() << endl;

  price = PriceperDay2(Car);
  cout << "The price will now be displayed again" << endl;
  cout << "Car's Price: " << price << endl;

  Car = GetanewCar();
  Car.dispmake();
  Car.dispyear();
  
//PART C MAIN
  cout << endl << "Part C: Rental Car" << endl << endl;
  cout << "What is the car's year? ";
  cin >> cyear;

  cout << "What is the car's make? ";
  cin >> cmake; 
  
  cout << "What is the cost of this car? ";
  cin >> ccost;
  
  cout << "What is the milage of this car? ";
  cin >> cmilage;
  
  //Carrental objects
  Carrental rent(cyear, cmake, cmilage, ccost);
  
  if(rent.isavailable())
    cout << "This car is available" << endl;
  else
    cout << "This car is not available" << endl;

  //cmake = rent.cartype(rent);
  rent.dispmembers();
  cout << "Make: " << rent.cartype(rent) << endl;
  
//  cin.ignore;
//  system("pause");
  return(0);
}
