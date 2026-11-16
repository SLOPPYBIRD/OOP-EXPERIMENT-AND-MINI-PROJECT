
#include <iostream>
#include <string>
using namespace std;

int main() {
    int age = 18;
    float height = 5.9f;
    double salary = 25000.00;
    char grade = 'A';
    bool isStudent = true;
    string name = "Sandesh";

    const float PI = 3.14159;

    cout << "Enter your age: ";
    cin >> age;

    cout << "Enter your name: ";
    cin >> name;

    cout << "\n--- Student Details ---" << endl;
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Grade: " << grade << endl;
    cout << "Student: " << boolalpha << isStudent << endl;
    cout << "PI: " << PI << endl;

    return 0;
}
