#include <iostream>

using namespace std;

class Time
{
  public:
    Time();
    Time(int h);
    void setHour(int h);
    int getHour();

  private:
    int hour;
};

// default constructor
Time::Time()
{
  hour = 0;
}

// defined constructor
Time::Time(int h)
{
  hour = h;
}

// setter method
void Time::setHour(int h)
{
  if (h>= 0 && h <= 23)
  {
    hour = h;
    //in the example slide, the setter method was using int hour to show that you would need to use the this pointer to hour
    //in order to differentiate between the data memeber and the parameter
  }
  else
  {
    hour = 0;
  }
}

// getter method using this
int Time::getHour()
{
  return this->hour;
}


int main()
{

  Time time1;

  time1.setHour (6);

  cout << "The hour is " << time1.getHour() << endl;

  return 0;
}
