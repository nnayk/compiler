#ifndef LABEL_HPP
#define LABEL_HPP
#include <string>

class Label {
    public:
        std::string id;
        Label(const std::string &id);
        std::string getLabel();
        static std::shared_ptr<Label> create(const std::string &id = std::to_string(counter));
    private: 
        const static std::string PREFIX;
        static int counter;
};
#endif
