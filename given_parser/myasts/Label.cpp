#include "Label.hpp"
#include <fmt/core.h>

int Label::counter = 0;
const std::string Label::PREFIX ="L";
Label::Label() : id(Label::counter++) {};

std::string Label::getLabel() {
    return fmt::format("{}{}",Label::PREFIX,this->id);  
}
