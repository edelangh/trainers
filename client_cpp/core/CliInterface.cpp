
#include <iostream>
#include "CliInterface.hpp"

CliInterface::CliInterface(const Args &a) : IInterface(), _a(a) {}
CliInterface::~CliInterface() {}

void CliInterface::prompt(std::string s)
{
    std::cout << s << std::endl;
}
