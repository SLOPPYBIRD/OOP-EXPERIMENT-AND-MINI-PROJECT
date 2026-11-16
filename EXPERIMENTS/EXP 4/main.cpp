
#include <iostream>
#include <string>
using namespace std;

// Base class
class Person {
protected:
    string name;
    int age;

public:
    void getPersonDetails(string n, int a) {
        name = n;
        age = a;
    }

    void displayPersonDetails() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
};

// Single inheritance: Student inherits Person
class Student : public Person {
protected:
    int rollNo;
    string course;

public:
    void getStudentDetails(int r, string c) {
        rollNo = r;
        course = c;
    }

    void displayStudentDetails() {
        displayPersonDetails();
        cout << "Roll Number: " << rollNo << endl;
        cout << "Course: " << course << endl;
    }
};

// Multilevel inheritance: GraduateStudent inherits Student
class GraduateStudent : public Student {
private:
    string researchTopic;

public:
    void getGraduateDetails(string topic) {
        researchTopic = topic;
    }

    void displayGraduateDetails() {
        displayStudentDetails();
        cout << "Research Topic: " << researchTopic << endl;
    }
};

int main() {
    // Demonstrating single inheritance
    cout << "=== Student Details ===" << endl;

    Student s;
    s.getPersonDetails("Rahul", 20);
    s.getStudentDetails(101, "B.Tech CSE");
    s.displayStudentDetails();

    // Demonstrating multilevel inheritance
    cout << "\n=== Graduate Student Details ===" << endl;

    GraduateStudent g;
    g.getPersonDetails("Priya", 24);
    g.getStudentDetails(201, "M.Tech CSE");
    g.getGraduateDetails("Artificial Intelligence");
    g.displayGraduateDetails();

    return 0;
}
