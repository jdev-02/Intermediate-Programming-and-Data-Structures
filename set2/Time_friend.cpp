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

  friend void setLocalHour (Time &, int);

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


// friend function (not part of Time class)
void setLocalHour (Time &t, int h)
{
  t.hour = h;
}


int main()
{
  Time time1;
  cout << "The hour is " << time1.getHour() << endl;

  // invoke setter class method
  time1.setHour( 8 );
  cout << "The hour is " << time1.getHour() << endl;

  // call friend function
  setLocalHour( time1, 12 );
  cout << "The hour is " << time1.getHour() << endl;

  return 0;
}
