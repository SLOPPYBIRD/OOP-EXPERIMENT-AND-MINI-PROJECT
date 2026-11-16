#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <numeric>
#include <vector>

class Student : public Person {
private:
    int studentID;
    std::string course;
    std::vector<int> marks;
public:
    Student();
    Student(const std::string& name, int age, int id, const std::string& course);
    void addMarks(int mark);
    void setMarks(const std::vector<int>& newMarks);
    void displayDetails() const override;
    int getStudentID() const;
    const std::string& getCourse() const;
    const std::string& getName() const;
    int getAge() const;
    const std::vector<int>& getMarks() const;
    void updateDetails(const std::string& name, int age, const std::string& course);
    int getTotalMarks() const;
    double getPercentage() const;
    std::string getGrade() const;
    bool operator<(const Student& other) const;
};

#endif
