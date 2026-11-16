
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>
using namespace std;

int main() {

    // Student names and marks using vector
    vector<int> marks = {85, 65, 90, 45, 75};

    // Map to store student names and marks
    map<string, int> students = {
        {"Sandesh", 85},
        {"Amit", 65},
        {"Priya", 90},
        {"Neha", 45},
        {"Rohan", 75}
    };

    // Unordered map to store student roll numbers
    unordered_map<int, string> rollNumbers = {
        {101, "Sandesh"},
        {102, "Amit"},
        {103, "Priya"},
        {104, "Neha"},
        {105, "Rohan"}
    };

    // Display student records
    cout << "--- Student Marks ---" << endl;
    for (auto s : students) {
        cout << s.first << " : " << s.second << endl;
    }

    // Sort marks in ascending order
    sort(marks.begin(), marks.end());

    cout << "\nSorted Marks: ";
    for (int m : marks) {
        cout << m << " ";
    }

    // Find students scoring above 80
    cout << "\n\nStudents scoring above 80:" << endl;

    for (auto s : students) {
        if (s.second > 80) {
            cout << s.first << " : " << s.second << endl;
        }
    }

    // Transform marks by adding 5 bonus marks
    transform(marks.begin(), marks.end(),
              marks.begin(), [](int m) {
                  return m + 5;
              });

    cout << "\nMarks after adding bonus: ";
    for (int m : marks) {
        cout << m << " ";
    }

    // Find a student using find_if
    auto it = find_if(students.begin(), students.end(),
                      [](const pair<string, int>& s) {
                          return s.second >= 90;
                      });

    if (it != students.end()) {
        cout << "\n\nStudent scoring 90 or above: "
             << it->first << endl;
    }

    // Display unordered map
    cout << "\n--- Roll Number Details ---" << endl;
    for (auto r : rollNumbers) {
        cout << r.first << " : " << r.second << endl;
    }

    return 0;
}
