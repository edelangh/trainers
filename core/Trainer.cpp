
#include "Trainer.hpp"

Trainer::Trainer(Args &a, IInterface *i) : _a(a), _i(i)
{
    _i->prompt("Welcome");
}
Trainer::~Trainer() {}

int     Trainer::run(void) {return 0;}
