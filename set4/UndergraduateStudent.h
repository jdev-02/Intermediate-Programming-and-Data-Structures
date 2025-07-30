#ifndef UndergraduateStudent_h
#define UndergraduateStudent_h
#include <iostream>
#include "Student.h"

using namespace std;

// Derived class from Student
class UndergraduateStudent : public Student {

  public:

    //invoke all Student constructors
    using Student::Student;

    //define Base class virtual method
    void computeCourseGrade() {
      int total = 0;

      for (int i = 0; i < NUM_TESTS; i++) {
        total += tests[i];
      }

      if (total / NUM_TESTS >= 70) {
        courseGrade = "Pass";
      } else {
        courseGrade = "Fail";
      }
    }

}; //end UndergraduateStudent class

#endif
