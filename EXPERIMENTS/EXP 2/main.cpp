
#include <iostream>
#include <string>
using namespace std;

class Vehicle {
public:
    string brand;
    string number;
    string color;

    Vehicle(string b, string n, string c) {
        brand = b;
        number = n;
        color = c;
    }
};

class Car : public Vehicle {
public:
    int passengers;
    int year;

    Car(string b, string n, string c, int p, int y)
        : Vehicle(b, n, c) {
        passengers = p;
        year = y;
    }

    void display() {
        cout << "Brand: " << brand << endl;
        cout << "Car Number: " << number << endl;
        cout << "Color: " << color << endl;
        cout << "Passengers: " << passengers << endl;
        cout << "Year: " << year << endl;
    }
};

int main() {
    Car car("Toyota", "MH12AB1234", "Blue", 4, 2000);

    car.display();

    return 0;
}
