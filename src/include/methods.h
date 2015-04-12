#ifndef __METHODS_H__
#define __METHODS_H__

#include <Rinternals.h>

SEXP agp_search_unsafe(SEXP r_func, SEXP r_left, SEXP r_right, SEXP r_eps, SEXP r_r, SEXP rho);
SEXP agp_search_n_unsafe(SEXP r_func, SEXP r_left, SEXP r_right, SEXP rho);

#endif // __METHODS_H__
