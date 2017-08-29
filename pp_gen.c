#include <stdlib.h>
#include <stdio.h>

#define UNARY_FUNCTION(func_name, math_size, operation) do {            \
        for(int x = 0; x < math_size; ++x) {                            \
            printf("#define __" #func_name "_%d %d\n", x, (operation)); \
        }                                                               \
        printf("#define " #func_name "(x) CAT2(__" #func_name "_, x)\n"); \
    } while(0)

#define BINARY_FUNCTION(func_name, math_size, operation) do {           \
        for(int x = 0; x < math_size; ++x) {                            \
            for(int y = 0; y < math_size; ++y) {                        \
                printf("#define __" #func_name "_%d_%d %d\n", x, y, (operation)); \
            }                                                           \
        }                                                               \
        printf("#define " #func_name "(x, y) CAT4(__" #func_name "_, x , _, y)\n"); \
    } while(0)

int main(int argc, char** argv)
{
    int math_size = 4;
    if (argc > 1) {
        math_size = atoi(argv[1]);
    }

    for(int ii = 0; ii < math_size; ++ii) {
        printf("#define PP_UINT_%d %d\n", ii, ii);
    }
    printf("#define PP_UINT_MAX %d\n", math_size - 1);


    printf("#define CAT2(x0, x1)         x0 ## x1\n");
    printf("#define CAT3(x0, x1, x2)     x0 ## x1 ## x2\n");
    printf("#define CAT4(x0, x1, x2, x3) x0 ## x1 ## x2 ## x3\n");
    
    UNARY_FUNCTION(PP_BOOL, math_size, x != 0);
    printf("#define PP_NOT(x) __PP_NOT(PP_BOOL(x))\n");
    printf("#define __PP_NOT(x) CAT2(__PP_NOT_, x)\n");
    printf("#define __PP_NOT_1 0\n");
    printf("#define __PP_NOT_0 1\n");

    BINARY_FUNCTION(PP_EQ,  math_size, x == y);
    printf("#define PP_NEQ(x, y) PP_NOT(PP_EQ(x, y))\n");
    
    BINARY_FUNCTION(PP_ADD, math_size, (x + y) % math_size);
    BINARY_FUNCTION(PP_SUB, math_size, (x + math_size - y) % math_size);

    printf("#define PP_INC(x) PP_ADD(x, 1)\n");
    printf("#define PP_DEC(x) PP_SUB(x, 1)\n");
    
    BINARY_FUNCTION(PP_MUL, math_size, (x * y) % math_size);
    BINARY_FUNCTION(PP_DIV, math_size, (x / (y ? y : 1) ) % math_size);

    for(int i = 0; i < math_size; ++i) {
        printf("#define PP_INDEX_SEQ_%d ", i);
        for(int j = 0; j < i; ++j) {
            printf("%d%s", j, j == i - 1 ? "" : ", ");
        }
        printf("\n");
    }

    printf("#define PP_INDEX_SEQ PP_INDEX_SEQ_%d\n", math_size - 1);

    printf("#define PP_GET_NTH(n, ...) __PP_EVAL_1(__PP_GET_NTH(n, ##__VA_ARGS__))\n");
    printf("#define __PP_GET_NTH(n, ...) PP_DEFER_2(__PP_GET_LAST)(PP_DEFER_1(CAT2) (PP_INDEX_SEQ_, PP_SUB(PP_UINT_MAX, n)), ##__VA_ARGS__)\n");
    
    printf("#define PP_LEN(...) __PP_GET_LAST(__VA_ARGS__");
    for(int i = 0; i < math_size; ++i) {
        printf(", %d", math_size - i - 1); 
    }
    printf(", 0)\n");

    printf("#define __PP_GET_LAST(");
    for(int i = 0; i < math_size; ++i) {
        printf("x%d%s", i, i ? ", " : "");
    }
    printf("last, ...) last\n");

    printf("#define PP_IF(cond, then_do, else_do) __PP_IF(PP_BOOL(cond), then_do, else_do)\n");
    printf("#define __PP_IF(cond, then_do, else_do) CAT2(__PP_IF_, cond)(then_do, else_do)\n");
    printf("#define __PP_IF_1(then_do, else_do) then_do\n");
    printf("#define __PP_IF_0(then_do, else_do) else_do\n");

    printf("#define PP_EVAL(...) __PP_EVAL_1024(__VA_ARGS__)\n");
    printf("#define __PP_EVAL_1(...) __VA_ARGS__\n");
    printf("#define __PP_EVAL_2(...)    __PP_EVAL_1(__PP_EVAL_1(__PP_EVAL_1(__VA_ARGS__)))\n");
    printf("#define __PP_EVAL_4(...)    __PP_EVAL_2(__PP_EVAL_2(__PP_EVAL_2(__VA_ARGS__)))\n");
    printf("#define __PP_EVAL_8(...)    __PP_EVAL_4(__PP_EVAL_4(__PP_EVAL_4(__VA_ARGS__)))\n");
    printf("#define __PP_EVAL_16(...)   __PP_EVAL_8(__PP_EVAL_8(__PP_EVAL_8(__VA_ARGS__)))\n");
    printf("#define __PP_EVAL_32(...)   __PP_EVAL_16(__PP_EVAL_16(__PP_EVAL_16(__VA_ARGS__)))\n");
    printf("#define __PP_EVAL_64(...)   __PP_EVAL_32(__PP_EVAL_32(__PP_EVAL_32(__VA_ARGS__)))\n");
    printf("#define __PP_EVAL_128(...)  __PP_EVAL_64(__PP_EVAL_64(__PP_EVAL_64(__VA_ARGS__)))\n");
    printf("#define __PP_EVAL_256(...)  __PP_EVAL_128(__PP_EVAL_128(__PP_EVAL_128(__VA_ARGS__)))\n");
    printf("#define __PP_EVAL_512(...)  __PP_EVAL_256(__PP_EVAL_256(__PP_EVAL_256(__VA_ARGS__)))\n");
    printf("#define __PP_EVAL_1024(...) __PP_EVAL_512(__PP_EVAL_512(__PP_EVAL_512(__VA_ARGS__)))\n");
    

    printf("#define PP_EMPTY()\n");
    printf("#define PP_DEFER_1(fn) fn PP_EMPTY()\n");
    printf("#define PP_DEFER_2(fn) fn PP_EMPTY PP_EMPTY()()\n");
    printf("#define PP_DEFER_3(fn) fn PP_EMPTY PP_EMPTY PP_EMPTY()()()\n");
    printf("#define PP_DEFER_4(fn) fn PP_EMPTY PP_EMPTY PP_EMPTY PP_EMPTY()()()()\n");

    printf("#define PP_FOR(from, to, fn) PP_EVAL(__PP_FOR(from, to, fn))\n");
    printf("#define __PP_FOR(from, to, fn) PP_IF(PP_EQ(from, to), ,fn(from)) PP_IF(PP_EQ(from, to), , PP_DEFER_4(__PP_FOR_I) () (PP_INC(from), to, fn))\n");
    printf("#define __PP_FOR_I() __PP_FOR\n");
}


