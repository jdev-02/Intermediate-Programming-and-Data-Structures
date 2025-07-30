#ifndef Student_h
#define Student_h

#define NUM_TESTS 3

using namespace std;

// Base class for all students
class Student {

  protected:
    string name;
    int tests[NUM_TESTS];
    string courseGrade;

  public:

    Student() { name = "No name"; }

    Student(string name) {
        this->name = name;
        courseGrade = "N/A";
    }

    string getName() const { return name; }

    void setName(string name) { this->name = name; }

    string getCourseGrade() const { return courseGrade; }

    int getTestScore(int testNumber) const { return tests[testNumber-1]; }

    void setTestScore(int testNumber, int testScore) {
        tests[testNumber-1] = testScore;
    }

    //undefined method in Base class, but OK
    void computeCourseGrade() {}

    //pure virtual method
//    virtual void computeCourseGrade() = 0;

};  //end Student class

#endif
