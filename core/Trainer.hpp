
#pragma once

#include "Args.hpp"
#include "IInterface.hpp"

class Trainer
{
    public:
        Trainer(Args &a, IInterface *i);
        ~Trainer();

        int     run(void);

        Args        _a;
        IInterface  *_i;
};
