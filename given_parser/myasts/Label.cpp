#include "Label.hpp"
#include <spdlog/spdlog.h>

int Label::counter = 0;
const std::string Label::PREFIX ="L";
Label::Label(const std::string &id) : id(id) {
    spdlog::debug("inside Label::{}\n",__func__);
    if(id==std::to_string(counter)) counter++;
};

std::shared_ptr<Label> Label::create(const std::string &id) {
    spdlog::debug("inside Label::{}\n",__func__);
    return std::shared_ptr<Label>(new Label(id));
}

std::string Label::getLabel() {
    return fmt::format("{}{}",Label::PREFIX,this->id);  
}
