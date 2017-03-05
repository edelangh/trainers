

#include <iostream>
#include "Parser.hpp"
#include "SdlWindow.hpp"

// Interface
#include "CliInterface.hpp"

#include "Trainer.hpp"

int main( int argc, char** argv )
{
    Args        a;
    Parser      p;
    IInterface  *i;
    Trainer     *t;

    p.parse(a, argc, argv);

    switch (a.interface)
    {
        case CLI:
            i = new CliInterface(a);
            break ;
//        case SDL:
//            break ;
        default:
            std::cout << "Unknown interface" << std::endl;
            exit(-1);
    }

    t = new Trainer(a, i);
    return t->run();
}
