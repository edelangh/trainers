
#pragma once

#include "interface.h"

class   Args
{
    public:
        Args();
        Args(const Args &a);
        ~Args();

        Args &operator=(const Args &a);
        Interface interface;
};
