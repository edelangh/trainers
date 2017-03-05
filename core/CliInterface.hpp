
#pragma once

#include "IInterface.hpp"
#include "Args.hpp"

class CliInterface : public IInterface
{
    public:
        CliInterface(const Args &a);
        virtual ~CliInterface();

        virtual void prompt(std::string s);

        Args    _a;
};
