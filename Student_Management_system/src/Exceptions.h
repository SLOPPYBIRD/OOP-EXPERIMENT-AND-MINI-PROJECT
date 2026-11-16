#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>
#include <string>

class StudentException : public std::runtime_error {
public: explicit StudentException(const std::string& message) : std::runtime_error(message) {}
};
class DuplicateStudentException : public StudentException {
public: explicit DuplicateStudentException(const std::string& message) : StudentException(message) {}
};
class StudentNotFoundException : public StudentException {
public: explicit StudentNotFoundException(const std::string& message) : StudentException(message) {}
};
class InvalidMarksException : public StudentException {
public: explicit InvalidMarksException(const std::string& message) : StudentException(message) {}
};
class InvalidInputException : public StudentException {
public: explicit InvalidInputException(const std::string& message) : StudentException(message) {}
};
#endif
