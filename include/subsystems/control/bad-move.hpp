//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-10-13
//* Desc: mfw pid controller no work.
//*       Temporary movement code that's very bad. Declarations.

#ifndef A_BAD_MOVE_HPP
#define A_BAD_MOVE_HPP

//! Prefix all objects here with "a_" except for child members and namespaces.

//* Headers
#include "api.h"

//* User-defined types

class a_Bad_Move
{
public:
    a_Bad_Move();
    void move_str(double dist);
    void move_pnt_trn(double head);

private:

};

#endif // A_BAD_MOVE_HPP
