#include "StudentManager.h"
#include "Exceptions.h"
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

namespace {
std::string csvEscape(const std::string& value) {
    std::string result = "\"";
    for (char ch : value) { if (ch == '"') result += '"'; result += ch; }
    return result + '"';
}
std::vector<std::string> parseCSV(const std::string& line) {
    std::vector<std::string> fields; std::string field; bool quoted = false;
    for (std::size_t i = 0; i < line.size(); ++i) {
        char ch = line[i];
        if (ch == '"' && quoted && i + 1 < line.size() && line[i + 1] == '"') { field += '"'; ++i; }
        else if (ch == '"') quoted = !quoted;
        else if (ch == ',' && !quoted) { fields.push_back(field); field.clear(); }
        else field += ch;
    }
    fields.push_back(field); return fields;
}
}

void StudentManager::rebuildIndexes() {
    idIndex.clear(); nameIndex.clear();
    for (std::size_t i = 0; i < students.size(); ++i) {
        idIndex[students[i].getStudentID()] = i;
        nameIndex[students[i].getName()].push_back(students[i].getStudentID());
    }
}
void StudentManager::addStudent(const Student& student) {
    if (idIndex.count(student.getStudentID())) throw DuplicateStudentException("Student ID already exists.");
    students.push_back(student); rebuildIndexes();
}
void StudentManager::displayStudents() const {
    if (students.empty()) { std::cout << "No student records found\n"; return; }
    for (const Student& student : students) student.displayDetails();
}
Student& StudentManager::searchStudent(int id) {
    const auto found = idIndex.find(id);
    if (found == idIndex.end()) throw StudentNotFoundException("Student ID not found.");
    return students[found->second];
}
const Student& StudentManager::searchStudent(int id) const {
    const auto found = idIndex.find(id);
    if (found == idIndex.end()) throw StudentNotFoundException("Student ID not found.");
    return students[found->second];
}
std::vector<int> StudentManager::searchStudent(const std::string& name) const {
    const auto found = nameIndex.find(name);
    return found == nameIndex.end() ? std::vector<int>{} : found->second;
}
void StudentManager::updateStudent(int id, const std::string& name, int age, const std::string& course) {
    searchStudent(id).updateDetails(name, age, course); rebuildIndexes();
}
void StudentManager::deleteStudent(int id) {
    const auto found = idIndex.find(id);
    if (found == idIndex.end()) throw StudentNotFoundException("Student ID not found.");
    students.erase(students.begin() + static_cast<std::ptrdiff_t>(found->second)); rebuildIndexes();
}
void StudentManager::enterMarks(int id, const std::vector<int>& marks) { searchStudent(id).setMarks(marks); }
void StudentManager::sortByMarks() {
    std::sort(students.begin(), students.end(), [](const Student& left, const Student& right) { return right < left; });
    rebuildIndexes();
}
std::size_t StudentManager::size() const { return students.size(); }

void StudentManager::saveToCSV(const std::string& filename) const {
    const std::string tempName = filename + ".tmp";
    std::ofstream output(tempName, std::ios::out | std::ios::trunc);
    if (!output) throw StudentException("Could not open temporary CSV file for writing.");
    output << "id,name,age,course,marks\n";
    output.seekp(0, std::ios::end);
    for (const Student& student : students) {
        output << student.getStudentID() << ',' << csvEscape(student.getName()) << ',' << student.getAge() << ','
               << csvEscape(student.getCourse()) << ",\"";
        const auto& marks = student.getMarks();
        std::vector<std::string> markFields(marks.size());
        std::transform(marks.begin(), marks.end(), markFields.begin(), [](int mark) { return std::to_string(mark); });
        for (std::size_t i = 0; i < markFields.size(); ++i) { if (i) output << ';'; output << markFields[i]; }
        output << "\"\n";
    }
    output.flush();
    if (!output) throw StudentException("Error while writing CSV file.");
    const std::streampos endPosition = output.tellp();
    (void)endPosition;
    output.close();
    std::ifstream check(tempName, std::ios::binary);
    if (!check) throw StudentException("Could not verify saved CSV file.");
    check.seekg(0, std::ios::end); const std::streampos fileSize = check.tellg();
    check.seekg(0, std::ios::beg); (void)fileSize;
    check.close();
    const std::string backupName = filename + ".bak";
    const bool hasPreviousFile = std::rename(filename.c_str(), backupName.c_str()) == 0;
    if (!hasPreviousFile) {
        std::ifstream existing(filename, std::ios::binary);
        if (existing.good()) throw StudentException("Could not preserve the existing CSV file before saving.");
    }
    if (std::rename(tempName.c_str(), filename.c_str()) != 0) {
        if (hasPreviousFile) std::rename(backupName.c_str(), filename.c_str());
        throw StudentException("Could not replace CSV file with saved records.");
    }
    if (hasPreviousFile) std::remove(backupName.c_str());
}

void StudentManager::loadFromCSV(const std::string& filename) {
    std::ifstream input(filename);
    if (!input) return;
    std::string line;
    if (!std::getline(input, line)) return;
    std::vector<Student> loaded;
    while (std::getline(input, line)) {
        if (line.empty()) continue;
        const auto fields = parseCSV(line);
        if (fields.size() != 5) throw InvalidInputException("Malformed row in students CSV file.");
        try {
            const int id = std::stoi(fields[0]);
            const std::string name = fields[1]; const int age = std::stoi(fields[2]);
            Student student(name, age, id, fields[3]);
            std::stringstream marks(fields[4]); std::string markText;
            while (std::getline(marks, markText, ';')) if (!markText.empty()) student.addMarks(std::stoi(markText));
            if (std::find_if(loaded.begin(), loaded.end(), [id](const Student& item) { return item.getStudentID() == id; }) != loaded.end())
                throw DuplicateStudentException("Duplicate student ID in CSV file.");
            loaded.push_back(student);
        } catch (const std::exception& error) { throw InvalidInputException(std::string("Invalid CSV record: ") + error.what()); }
    }
    students = loaded; rebuildIndexes();
}
