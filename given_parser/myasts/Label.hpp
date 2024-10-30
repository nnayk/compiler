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
