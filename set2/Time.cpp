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
  }
  else
  {
    hour = 0;
  }
}

// getter method
int Time::getHour()
{
  return hour;
}


int main()
{
  Time t1;
  Time t2(12);

  cout << "The t1 hour is " << t1.getHour() << endl;
  cout << "The t2 hour is " << t2.getHour() << endl;

  t1.setHour(8);
  cout << "The t1 hour is " << t1.getHour() << endl;

  return 0;
}
