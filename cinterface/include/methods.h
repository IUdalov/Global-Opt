#ifndef __METHODS_H__
#define __METHODS_H__

#include <Rinternals.h>

SEXP direct_search_unsafe(SEXP r_func, SEXP r_left, SEXP r_right, SEXP r_steps, SEXP rho);
SEXP agp_search_unsafe(SEXP r_func, SEXP r_left, SEXP r_right, SEXP r_eps, SEXP r_r, SEXP rho);
SEXP broken_line_search_unsafe(SEXP r_func, SEXP r_left, SEXP r_right, SEXP r_eps, SEXP r_lip, SEXP rho);

#endif // __METHODS_H__
