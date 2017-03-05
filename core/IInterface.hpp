
#pragma once

#include <string>

class   IInterface
{
    public:
        virtual ~IInterface() {};

        virtual void    prompt(std::string s) = 0;
};
