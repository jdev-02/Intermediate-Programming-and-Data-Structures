#include <iostream>
#include "Student.h"
#include "UndergraduateStudent.h"
#include "GraduateStudent.h"

using namespace std;

int main()
{

  Student s1;
  Student s2("Alan");

  cout << "s1's name is " << s1.getName() << endl;
  s1.setName ("Bruce");
  cout << "s1's name is " << s1.getName() << endl << endl;

  cout << "s2's name is " << s2.getName() << endl;

  s2.setTestScore(1, 95);
  s2.setTestScore(2, 98);
  s2.setTestScore(3, 92);
  cout << s2.getName() << " has test scores of "
       << s2.getTestScore(1) << ", "
       << s2.getTestScore(2) << endl;
  cout << s2.getName() << " has course grade of "
       << s2.getCourseGrade() << endl;
  s2.computeCourseGrade();  //method not defined for Student Base class
  cout << s2.getName() << " has course grade of "
       << s2.getCourseGrade() << endl;

/*
  UndergraduateStudent s3("Ashley");

  s3.setTestScore(1, 70);
  s3.setTestScore(2, 80);
  s3.setTestScore(3, 60);
  s3.computeCourseGrade();
  cout << s3.getName() << " has test scores of "
       << s3.getTestScore(1) << ", "
       << s3.getTestScore(2) << ", "
       << s3.getTestScore(3) << endl;
  cout << s3.getName() << " has course grade: "
       << s3.getCourseGrade() << endl;

  s3.setTestScore(3, 50);
  s3.computeCourseGrade();
  cout << s3.getName() << " has new test score of "
       << s3.getTestScore(3) << endl;
  cout << s3.getName() << " has course grade: " << s3.getCourseGrade() << endl << endl;


  GraduateStudent s4("Sam");

  s4.setTestScore(1, 80);
  s4.setTestScore(2, 75);
  s4.setTestScore(3, 85);
  s4.computeCourseGrade();
  cout << s4.getName() << " has test scores of "
       << s4.getTestScore(1) << ", "
       << s4.getTestScore(2) << ", "
       << s4.getTestScore(3) << endl;
  cout << s4.getName() << " has course grade: "
       << s4.getCourseGrade() << endl;

  s4.setTestScore(3, 70);
  s4.computeCourseGrade();
  cout << s4.getName() << " has new test score of "
       << s4.getTestScore(3) << endl;
  cout << s4.getName() << " has course grade: " << s4.getCourseGrade() << endl << endl;


  Student *s5 = new Student("Mary");
  Student *s6 = new UndergraduateStudent("John");
//  GraduateStudent *s7 = new Student;
  cout << "s5's name is " << s5->getName() << endl;
  cout << "s6's name is " << s6->getName() << endl;

  //Create an array of 40 students in a course
  Student *roster[40];
  roster[0] = new UndergraduateStudent();
  roster[1] = new UndergraduateStudent();
  roster[2] = new GraduateStudent();
  roster[0]->computeCourseGrade();
*/

  return 0;
}
