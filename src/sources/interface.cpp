#include "methods.h"

extern "C" {
    SEXP agp_search(SEXP r_func, SEXP r_left, SEXP r_right, SEXP r_eps, SEXP r_r, SEXP rho) {
        return agp_search_unsafe(r_func, r_left, r_right, r_eps, r_r, rho);
    }

    SEXP agp_search_n(SEXP r_func, SEXP r_left, SEXP r_right, SEXP rho) {
        return agp_search_n_unsafe(r_func, r_left, r_right, rho);
    }
}
