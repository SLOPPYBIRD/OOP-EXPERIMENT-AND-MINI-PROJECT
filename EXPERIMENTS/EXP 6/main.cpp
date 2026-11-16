
#include <iostream>
using namespace std;

class Complex {
private:
    float real, imag;

public:
    // Parameterized constructor
    Complex(float r = 0, float i = 0) {
        real = r;
        imag = i;
    }

    // Function overloading
    void display() {
        cout << real << " + " << imag << "i" << endl;
    }

    void display(string message) {
        cout << message << real << " + " << imag << "i" << endl;
    }

    // Operator overloading (+)
    Complex operator+(const Complex& c) {
        Complex temp;
        temp.real = real + c.real;
        temp.imag = imag + c.imag;
        return temp;
    }
};

int main() {
    Complex c1(3, 4);
    Complex c2(2, 5);

    cout << "First Complex Number: ";
    c1.display();

    cout << "Second Complex Number: ";
    c2.display();

    // Function overloading
    c1.display("Complex Number: ");

    // Operator overloading
    Complex c3 = c1 + c2;

    cout << "Sum of Complex Numbers: ";
    c3.display();

    return 0;
}
