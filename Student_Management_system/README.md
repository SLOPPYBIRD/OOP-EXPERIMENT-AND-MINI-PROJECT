# Student Management System

A menu-driven C++17 console application for managing student profiles and subject marks. It was written as a second-year B.Tech OOP mini-project and uses only the C++ standard library.

## Features

- Add, display, find by ID, update, and delete student records.
- Add or replace a student's subject marks; calculate total, average percentage, and grade.
- Sort students from highest to lowest percentage.
- Automatically load `data/students.csv` at startup and save on exit; option 8 saves immediately.
- Reject duplicate IDs, invalid marks, and invalid menu input.
- CSV fields are quoted, so commas and quotation marks in names or courses are retained.

## Build and run

From the project root, using MinGW g++:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp src/Student.cpp src/StudentManager.cpp -o StudentManagementSystem.exe
./StudentManagementSystem.exe
```

Run from the project root so the relative `data/students.csv` path resolves. The CSV file is included with its header; if it is absent on first run, records can still be entered and saved.

## OOP and STL concepts

- Encapsulation and constructors: `Student` stores profile data and marks behind a public interface.
- Inheritance, runtime polymorphism, overriding, and virtual destructor: `Student` derives from `Person` and overrides `displayDetails()`.
- Overloading: `StudentManager::searchStudent` accepts an ID or name.
- Operator overloading: `Student::operator<` compares percentages and is used by sorting.
- Templates: `readValue<T>` validates typed console input.
- Exceptions: `Exceptions.h` defines a small hierarchy for duplicate, missing, invalid mark, and invalid input errors.
- STL: `vector` stores records and marks; `map` indexes IDs; `unordered_map` indexes names; `sort`, `find`/`find_if`-style lookup, `transform` support appear in the manager and reports. The manager currently uses map lookups for IDs and unordered-map lookups for names.

## Project layout

See [UML_Diagram.md](UML_Diagram.md) for the class diagram. Source files are in `src/`; persistent records are in `data/`.
