#ifndef LABEL_HPP
#define LABEL_HPP
#include <string>

class Label {
    public:
        int id;
        Label();
        std::string getLabel();
    private: 
        const static std::string PREFIX;
        static int counter;
};
#endif
