#include <stdlib.h>

typedef float arithm_t;

typedef struct _matrix_t {
    size_t     num_rows;
    size_t     num_cols;
    arithm_t** data;
}* matrix_t;

matrix_t mtrx_alloc(size_t num_rows, size_t num_cols) {
    matrix_t result = malloc(sizeof(*result));
    result->num_rows = num_rows;
    result->num_cols = num_cols;
    result->data     = malloc(num_cols * sizeof(arithm_t*));
    for(size_t col = 0; col < num_cols; ++col) {
        result->data[col] = malloc(num_rows*sizeof(arithm_t));
    }
    return result;
}

arithm_t uniform_dist(arithm_t a, arithm_t b) {
    arithm_t size = b - a;
    arithm_t result = a + ((arithm_t)rand()/(arithm_t)RAND_MAX)*size;
    return result;
}

void mtrx_uniform_dist(matrix_t m, arithm_t a, arithm_t b) {
    for(size_t col = 0; col < m->num_cols; ++col) {
        arithm_t* this_col = m->data[col];
        
        for(size_t row =0; row < m->num_rows; ++row) {
            this_col[row] = uniform_dist(a, b);
        }
    }
}

int mtrx_eq(matrix_t a, matrix_t b, arithm_t zero_tol) {
    if (a->num_rows != b->num_rows) {
        return 0;
    }
    if (a->num_cols != b->num_cols) {
        return 0;
    }
    
    size_t num_rows = a->num_rows;
    size_t num_cols = a->num_cols;

    for(size_t col = 0; col < num_cols; ++col) {
        for(size_t row =0; row < num_rows; ++row) {
            arithm_t diff = a->data[col][row] - b->data[col][row];
            arithm_t diff_sq = diff * diff;
            if (diff_sq > zero_tol) {
                return 0;
            }
        }
    }
    return 1;
}

matrix_t mtrx_mul(matrix_t result, matrix_t a, matrix_t b) {
    if (a->num_cols != b->num_rows) {
        return NULL;
    }

    size_t commond_size = a->num_cols;
    
    for(size_t row = 0; row < a->num_rows; ++row) {
        for(size_t col = 0; col < b->num_cols; ++col) {
            result->data[row][col] = 0;
            for(size_t idx = 0; idx < commond_size; ++idx) {
                result->data[row][col] += a->data[idx][row] * b->data[col][row];
            }
        }
    }
    
    return result;
}

int main(int argc, char** argv)
{
    size_t mat_size = 100;
    if (argc > 1) {
        mat_size = (size_t) atoi(argv[1]);
    }
    matrix_t a      = mtrx_alloc(mat_size, mat_size);
    matrix_t b      = mtrx_alloc(mat_size, mat_size);
    matrix_t result = mtrx_alloc(mat_size, mat_size);

    mtrx_uniform_dist(a, 0.f, 1.f);
    mtrx_uniform_dist(b, 0.f, 1.f);

    mtrx_mul(result, a, b);

    exit(EXIT_SUCCESS);
}
