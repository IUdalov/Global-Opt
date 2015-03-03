#include "methods.h"


SEXP direct_search(SEXP r_func, SEXP r_left, SEXP r_right, SEXP r_steps, SEXP rho) {
    // Declaration
    SEXP r_fcall, r_ans, r_arg;
    double left, right, min, res, step, value;
    int steps;

    // Protect from gc
    r_fcall = PROTECT(lang2(r_func, R_NilValue));
    r_ans   = PROTECT(allocVector(REALSXP, 1));
    r_arg   = PROTECT(allocVector(REALSXP, 1));

    // Initialization
    left    = *REAL(r_left);
    right   = *REAL(r_right);
    steps   = (int)(*REAL(r_steps));
    step    = (right - left) / ((double)steps);
    res     = left;
    eval_func(r_fcall, min, left, r_arg, r_ans, rho)

    // Atgorithm
    for(double i = left + step; i <= right; i += step) {
        eval_func(r_fcall, value, i, r_arg, r_ans, rho);
        if (value < min) {
            min = value;
            res = i;
        }
    }

    REAL(r_ans)[0] = res;
    UNPROTECT(3); // Enable gc for objects
    return r_ans;
}

SEXP agp_search(SEXP r_func, SEXP r_left, SEXP r_right, SEXP r_eps, SEXP r_lip, SEXP rho) {

    SEXP r_fcall, r_ans, r_arg;
    double left, right, eps, lip, R_min, Q_min;
    int n, i_min, n_max;
    double* x, *Q, *R;

    r_fcall = PROTECT(lang2(r_func, R_NilValue));
    r_ans   = PROTECT(allocVector(REALSXP, 1));
    r_arg   = PROTECT(allocVector(REALSXP, 1));

    left    = *REAL(r_left);
    right   = *REAL(r_right);
    eps     = *REAL(r_eps);
    lip     = *REAL(r_lip);

    n_max = START_N;
    n = 2;
    x = (double*)malloc(n_max * sizeof(double));
    Q = (double*)malloc(n_max * sizeof(double));
    R = (double*)malloc(n_max * sizeof(double));

    i_min = 0;
    x[0] = left;
    x[1] = right;
    eval_func(r_fcall, Q[0], x[0], r_arg, r_ans, rho);
    eval_func(r_fcall, Q[1], x[1], r_arg, r_ans, rho);
    R_min = R[0] = agp_Ri(x[0], x[1], Q[0], Q[1], lip);
    Q_min = Q[0] < Q[1] ? Q[0] : Q[1];
    while(fabs(R_min - Q_min) > eps ) {
        
    }

    free(x);
    free(Q);
    free(R);
    UNPROTECT(3);
    return R_NilValue;
}
