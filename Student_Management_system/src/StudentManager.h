#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "Student.h"
#include <map>
#include <unordered_map>
#include <vector>

class StudentManager {
private:
    std::vector<Student> students;
    std::map<int, std::size_t> idIndex;
    std::unordered_map<std::string, std::vector<int>> nameIndex;
    void rebuildIndexes();
public:
    void addStudent(const Student& student);
    void displayStudents() const;
    Student& searchStudent(int id);
    const Student& searchStudent(int id) const;
    std::vector<int> searchStudent(const std::string& name) const;
    void updateStudent(int id, const std::string& name, int age, const std::string& course);
    void deleteStudent(int id);
    void enterMarks(int id, const std::vector<int>& marks);
    void sortByMarks();
    void saveToCSV(const std::string& filename) const;
    void loadFromCSV(const std::string& filename);
    std::size_t size() const;
};

#endif
