#include "pp.h"

#include <assert.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    assert(0 == PP_BOOL(0)  && "Unexpected boolean value");
    assert(1 == PP_BOOL(1)  && "Unexpected boolean value");
    assert(1 == PP_BOOL(10) && "Unexpected boolean value");
    
    assert(5 == PP_ADD(3, 2) && "Unexpected arithmetic value");
    assert(6 == PP_MUL(3, 2) && "Unexpected arithmetic value");
    assert(1 == PP_SUB(3, 2) && "Unexpected arithmetic value");
    assert(2 == PP_DIV(4, 2) && "Unexpected arithmetic value");

    assert(10 == PP_MUL(PP_ADD(2, 3), 2) && "Unexpected arithmetic value");

    assert(1 == PP_BOOL(PP_ADD(2, 3)) && "Unexpected boolean value");

    assert(0 == PP_LEN()        && "Unexpected len");
    assert(1 == PP_LEN(1)       && "Unexpected len");
    assert(2 == PP_LEN(1, 1)    && "Unexpected len");
    assert(3 == PP_LEN(1, 1, 1) && "Unexpected len");

    assert('f' == PP_IF(0, 't', 'f') && "Unexpected if result");
    assert('t' == PP_IF(1, 't', 'f') && "Unexpected if result");
    assert('t' == PP_IF(2, 't', 'f') && "Unexpected if result");
    
    do {
#define INC_X(it) ++x;
        int x = 0;
        PP_FOR(0, 50, INC_X);
        assert(x == 10);
#undef INC_X
    } while(0);
    
    printf("passed\n");
    return 0;
}
