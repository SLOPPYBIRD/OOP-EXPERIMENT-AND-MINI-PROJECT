
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Generic Stack class
template <class T>
class Stack {
private:
    vector<T> elements;

public:
    // Insert element
    void push(T value) {
        elements.push_back(value);
    }

    // Remove element
    void pop() {
        if (elements.empty()) {
            cout << "Stack is empty!" << endl;
        } else {
            cout << "Popped: " << elements.back() << endl;
            elements.pop_back();
        }
    }

    // Display stack
    void display() {
        if (elements.empty()) {
            cout << "Stack is empty!" << endl;
        } else {
            for (int i = elements.size() - 1; i >= 0; i--) {
                cout << elements[i] << " ";
            }
            cout << endl;
        }
    }
};

int main() {

    // Integer Stack
    cout << "Integer Stack:" << endl;
    Stack<int> s1;
    s1.push(10);
    s1.push(20);
    s1.push(30);
    s1.display();
    s1.pop();
    s1.display();

    // Float Stack
    cout << "\nFloat Stack:" << endl;
    Stack<float> s2;
    s2.push(10.5);
    s2.push(20.5);
    s2.display();
    s2.pop();
    s2.display();

    // String Stack
    cout << "\nString Stack:" << endl;
    Stack<string> s3;
    s3.push("Apple");
    s3.push("Banana");
    s3.push("Mango");
    s3.display();
    s3.pop();
    s3.display();

    return 0;
}
