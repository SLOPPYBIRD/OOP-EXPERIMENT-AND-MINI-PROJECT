#include "Student.h"
#include "Exceptions.h"
#include <algorithm>
#include <iomanip>

Student::Student() : Person(), studentID(0), course("Not Assigned") {}
Student::Student(const std::string& studentName, int studentAge, int id, const std::string& studentCourse)
    : Person(studentName, studentAge), studentID(id), course(studentCourse) {}

void Student::addMarks(int mark) {
    if (mark < 0 || mark > 100) throw InvalidMarksException("Marks must be between 0 and 100.");
    marks.push_back(mark);
}
void Student::setMarks(const std::vector<int>& newMarks) {
    for (int mark : newMarks) if (mark < 0 || mark > 100) throw InvalidMarksException("Marks must be between 0 and 100.");
    marks = newMarks;
}
void Student::displayDetails() const {
    std::cout << "\n--- Student Details ---\n";
    Person::displayDetails();
    std::cout << "Student ID: " << studentID << "\nCourse: " << course << "\nMarks: ";
    if (marks.empty()) std::cout << "None";
    for (int mark : marks) std::cout << mark << ' ';
    std::cout << "\nTotal: " << getTotalMarks() << "  Percentage: " << std::fixed << std::setprecision(2)
              << getPercentage() << "%  Grade: " << getGrade() << '\n';
}
int Student::getStudentID() const { return studentID; }
const std::string& Student::getCourse() const { return course; }
const std::string& Student::getName() const { return name; }
int Student::getAge() const { return age; }
const std::vector<int>& Student::getMarks() const { return marks; }
void Student::updateDetails(const std::string& studentName, int studentAge, const std::string& studentCourse) {
    name = studentName; age = studentAge; course = studentCourse;
}
int Student::getTotalMarks() const { return std::accumulate(marks.begin(), marks.end(), 0); }
double Student::getPercentage() const { return marks.empty() ? 0.0 : static_cast<double>(getTotalMarks()) / marks.size(); }
std::string Student::getGrade() const {
    if (marks.empty()) return "N/A";
    const double percentage = getPercentage();
    if (percentage >= 90) return "A+";
    if (percentage >= 80) return "A";
    if (percentage >= 70) return "B";
    if (percentage >= 60) return "C";
    if (percentage >= 50) return "D";
    return "F";
}
bool Student::operator<(const Student& other) const { return getPercentage() < other.getPercentage(); }
