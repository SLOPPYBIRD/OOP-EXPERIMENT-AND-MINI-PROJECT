#include "StudentManager.h"
#include "Exceptions.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace {
const std::string DATA_FILE = "data/students.csv";
template <typename T> T readValue(const std::string& prompt) {
    T value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) { std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); return value; }
        if (std::cin.eof()) throw InvalidInputException("Input stream closed.");
        std::cout << "Invalid input. Please try again.\n";
        std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
std::string readText(const std::string& prompt) {
    std::string value;
    do { std::cout << prompt; std::getline(std::cin, value); if (value.empty()) std::cout << "Value cannot be empty.\n"; } while (value.empty());
    return value;
}
std::vector<int> readMarks() {
    const int count = readValue<int>("Number of subject marks: ");
    if (count < 0 || count > 20) throw InvalidInputException("Enter a subject count from 0 to 20.");
    std::vector<int> marks;
    for (int i = 0; i < count; ++i) marks.push_back(readValue<int>("Mark " + std::to_string(i + 1) + " (0-100): "));
    return marks;
}
void printMenu() {
    std::cout << "\n=== Student Management System ===\n"
              << "1. Add student\n2. Display all students\n3. Search by ID\n4. Update student details\n"
              << "5. Delete student\n6. Enter/replace subject marks\n7. Sort by marks\n8. Save records\n"
              << "9. Reload records from CSV\n0. Save and exit\n";
}
}

int main() {
    StudentManager manager;
    try { manager.loadFromCSV(DATA_FILE); std::cout << manager.size() << " record(s) loaded.\n"; }
    catch (const std::exception& error) { std::cerr << "Could not load records: " << error.what() << '\n'; }

    bool running = true;
    while (running) {
        try {
            printMenu();
            switch (readValue<int>("Choose an option: ")) {
            case 1: {
                const int id = readValue<int>("Student ID: ");
                const std::string name = readText("Name: ");
                const int age = readValue<int>("Age: ");
                if (age < 1 || age > 120) throw InvalidInputException("Age must be between 1 and 120.");
                const std::string course = readText("Course: ");
                Student student(name, age, id, course);
                manager.addStudent(student);
                std::cout << "Student added.\n"; break;
            }
            case 2: manager.displayStudents(); break;
            case 3: manager.searchStudent(readValue<int>("Student ID: ")).displayDetails(); break;
            case 4: {
                const int id = readValue<int>("Student ID: ");
                const std::string name = readText("New name: ");
                const int age = readValue<int>("New age: ");
                if (age < 1 || age > 120) throw InvalidInputException("Age must be between 1 and 120.");
                manager.updateStudent(id, name, age, readText("New course: "));
                std::cout << "Student updated.\n"; break;
            }
            case 5: manager.deleteStudent(readValue<int>("Student ID: ")); std::cout << "Student deleted.\n"; break;
            case 6: {
                const int id = readValue<int>("Student ID: ");
                const std::vector<int> marks = readMarks();
                manager.enterMarks(id, marks); std::cout << "Marks saved.\n"; break;
            }
            case 7: manager.sortByMarks(); std::cout << "Students sorted from highest to lowest percentage.\n"; manager.displayStudents(); break;
            case 8: manager.saveToCSV(DATA_FILE); std::cout << "Records saved.\n"; break;
            case 9: manager.loadFromCSV(DATA_FILE); std::cout << "Records reloaded.\n"; break;
            case 0: manager.saveToCSV(DATA_FILE); running = false; std::cout << "Records saved. Goodbye.\n"; break;
            default: std::cout << "Choose a menu option from 0 to 9.\n";
            }
        } catch (const std::exception& error) { std::cout << "Error: " << error.what() << '\n'; }
    }
    return 0;
}
