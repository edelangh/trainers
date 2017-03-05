
#include "Args.hpp"

Args::Args() {}
Args::Args(const Args &a) {*this = a;}
Args::~Args() {}

Args &Args::operator=(const Args &a)
{
    this->interface = a.interface;
    return *this;
}
