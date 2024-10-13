#ifndef TYPE_EXCEPTION_HPP
#define TYPE_EXCEPTION_HPP
#include <iostream>
#include <exception>
#include <string>

// Custom exception class
class TypeException : public std::exception {
private:
    std::string message;

public:
    // Constructor that accepts a message
    TypeException(const std::string& msg) : message(msg) {}

    // Override the what() method to return the message
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};
#endif
