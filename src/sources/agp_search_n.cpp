#include "methods.h"
#include "utils.h"
#include "evolvnet.h"

SEXP agp_search_n_unsafe(SEXP r_func, SEXP r_left, SEXP r_right, SEXP rho) {
    RNFunction func(r_func, rho);

    return R_NilValue;
}