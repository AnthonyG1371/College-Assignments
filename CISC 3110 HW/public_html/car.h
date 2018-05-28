#include<iostream>
#include<string>
using namespace std;
using std::string;

class car
{
  private:
    int year;
    string make;
    int speed;
  public:
    car();
    car(int, string);
    void dispspeed();
    void dispyear();
    void dispmake();
    int getspeed();
    int getyear();
    string getmake();
    int changeyear(car, int);
    string changemake(car, string);
    int accelerate();
    int brake();
    int getconstyear() const;
};

//PART 3's CLASS
class Carrental
{
  private:
    car Carinfo;
    int milage;
    double cost;
    bool available;
  public:
    Carrental();
    Carrental(int, string, int, double);
    bool isavailable();
    string cartype(Carrental);
    void dispmembers();
};

//PART B's Function Prototypes
int PriceperDay(car);
int accelerate_by(car &, int);
int PriceperDay2(const car &);
car GetanewCar();
