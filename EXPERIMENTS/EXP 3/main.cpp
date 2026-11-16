
#include <iostream>
#include <utility>
using namespace std;

class A {
    int a;

public:
    // Default constructor
    A() {
        a = 0;
    }

    // Parameterized constructor
    A(int x) {
        a = x;
    }

    // Copy constructor
    A(const A &obj) {
        a = obj.a;
    }

    // Move constructor
    A(A &&obj) {
        a = obj.a;
        obj.a = 0;
    }

    void print() {
        cout << a << endl;
    }
};

int main() {
    A obj1;
    obj1.print();

    A obj2(10);

    A obj3(obj2);
    obj3.print();

    A obj4(std::move(obj2));
    obj4.print();

    return 0;
}
