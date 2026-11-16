#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int age;
public:
    Person() : name("Unknown"), age(0) {}
    Person(const std::string& personName, int personAge) : name(personName), age(personAge) {}
    virtual void displayDetails() const {
        std::cout << "Name: " << name << "\nAge: " << age << '\n';
    }
    virtual ~Person() = default;
};

#endif
