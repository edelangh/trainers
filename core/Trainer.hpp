
#pragma once

#include "Args.hpp"
#include "IInterface.hpp"
#include "Test.hpp"

class Trainer
{
    public:
        Trainer(Args &a, IInterface *i);
        ~Trainer();

        int     run(void);

        int     getNextTestId();
        Test    *getTest(int id);

        void    test(Test *t);

        Args        _a;
        IInterface  *_i;
};
