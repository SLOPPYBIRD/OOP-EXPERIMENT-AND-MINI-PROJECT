
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    fstream file;

    // Write student records
    file.open("students.csv", ios::out);

    file << "101,Rahul,85\n";
    file << "102,Priya,90\n";
    file << "103,Amit,75\n";

    file.close();

    // Read student records
    file.open("students.csv", ios::in);

    string line;
    cout << "--- Student Records ---" << endl;

    while (getline(file, line)) {
        cout << line << endl;
    }

    // Demonstrate file pointer functions
    cout << "\nCurrent read position: " << file.tellg() << endl;

    file.seekg(0, ios::beg);
    cout << "After seekg(): " << file.tellg() << endl;

    file.close();

    // Demonstrate output file pointers
    file.open("students.csv", ios::out | ios::in);

    file.seekp(0, ios::end);
    cout << "Current write position: " << file.tellp() << endl;

    file << "104,Neha,88\n";

    file.seekp(0, ios::beg);
    cout << "After seekp(): " << file.tellp() << endl;

    file.close();

    return 0;
}
