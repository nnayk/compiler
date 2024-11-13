#ifndef USE_BEFORE_INIT_EXCEPTION_HPP
#define USE_BEFORE_INIT_EXCEPTION_HPP
#include <iostream>
#include <exception>
#include <string>

// Custom exception class
class UseBeforeInitException : public std::exception {
private:
    std::string message;

public:
    // Constructor that accepts a message
    UseBeforeInitException(const std::string& msg) : message(msg) {}

    // Override the what() method to return the message
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};
#endif
