#include "spdlog/spdlog.h"
#include <iostream>
#include <string>

int main()
{
    std::string name = "abc";
    spdlog::info("name is {}",name);
}
