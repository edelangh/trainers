
#pragma once

#include "Args.hpp"

class Parser
{
    public:
        Parser();
        ~Parser();

        void parse(Args &a, int ac, char **av);
};
