#include <R.h>
#include <Rinternals.h>
#include "methods.h"

extern "C" {
    SEXP direct_search(SEXP r_func, SEXP r_left, SEXP r_right, SEXP r_steps, SEXP rho) {
        return direct_search_unsafe(r_func, r_left, r_right, r_steps, rho);
    }
}

extern "C" {
    SEXP agp_search(SEXP r_func, SEXP r_left, SEXP r_right, SEXP r_eps, SEXP r_r, SEXP rho) {
        return agp_search_unsafe(r_func, r_left, r_right, r_eps, r_r, rho);
    }
}

extern "C" {
    SEXP broken_line_search(SEXP r_func, SEXP r_left, SEXP r_right, SEXP r_eps, SEXP r_lip, SEXP rho) {
        return agp_search_unsafe(r_func, r_left, r_right, r_eps, r_lip, rho);
    }
}