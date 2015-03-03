#ifndef __METHODS_H__
#define __METHODS_H__

// C
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

//R internals
#include <R.h>
#include <Rinternals.h>

#define START_N             10 // must >= 2
#define EXPAND_MEMORY_TIMES 2

#define eval_func(r_func, res, arg, r_arg, r_ans, rho)  \
    {                                                   \
        REAL(r_arg)[0] = arg;                           \
        SETCADR(r_func, r_arg);                         \
        r_ans = eval(r_fcall, rho);                     \
        res = *REAL(r_ans);                             \
    }


double agp_xi(double xi, double xi1, double Qi, double Qi1, double lip) {
    return (xi + xi1) / 2 - (Qi + Qi1) / (2 * lip);
}

double piyavsky_Ri(double xi, double xi1, double Qi, double Qi1, double lip) {
    return (Qi + Qi1) / (2 * lip) - lip * (xi1 - xi) / 2;
}

double agp_Ri(double xi, double xi1, double Qi, double Qi1, double lip) {
    return (Qi + Qi1) / (2 * lip) - lip * (1 + pow((Qi1 - Qi) / (xi1 - xi),2)) / 4 * (xi1 - xi);
}



int insert_elem(int n, int* max_n, double** x, double** Q, double** R, double elem_x, double elem_Q, double elem_R) {
    if (n + 1 > *max_n) {
        *max_n = EXPAND_MEMORY_TIMES * *max_n;
        *x = (double*)realloc(*x, sizeof(double) * *max_n);
        *Q = (double*)realloc(*Q, sizeof(double) * *max_n);
        *R = (double*)realloc(*R, sizeof(double) * *max_n);
        if (NULL == *x || NULL == *Q || NULL == *R) {return EXIT_FAILURE;}
    }
    // TODO:
    return 0;
}

#endif // __METHODS_H__
