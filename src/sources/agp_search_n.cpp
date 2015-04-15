#include "methods.h"
#include "utils.h"
// #include "evolvnet.h"
#include <stdio.h>

SEXP agp_search_n_unsafe(SEXP r_func, SEXP r_N, SEXP r_left, SEXP r_right, SEXP rho) {
    RNFunction func(r_func, r_N, rho);
    int N = *INTEGER(r_N);
    double* left_bound = new double[N];
    double* right_bound = new double[N];
    double* arg = new double[N];

    // TODO: impliment method
    for(int i = 0; i < N; i++){
        left_bound[i] = REAL(r_left)[i];
        right_bound[i] = REAL(r_right)[i];
    }

    printf("N: %d, func: %lf\n", N, func(right_bound));

    delete []left_bound;
    delete []right_bound;
    delete []arg;
    return R_NilValue;
}
