#include "methods.h"
#include "utils.h"

#include "iostream"
#include "stdio.h"

// DIRECT SEARCH IMPL ---------------------------------------------------------
SEXP direct_search_unsafe(SEXP r_func, SEXP r_left, SEXP r_right, SEXP r_steps, SEXP rho) {
    // Declaration
    double left, right, min, res, step, value;
    int steps;
    RFunction func(r_func, rho);

    // Initialization
    left    = *REAL(r_left);
    right   = *REAL(r_right);
    steps   = (int)(*REAL(r_steps));
    step    = (right - left) / ((double)steps);
    res     = left;
    min = func(left);

    // Atgorithm
    for(double i = left + step; i <= right; i += step) {
        value = func(i);
        if (value < min) {
            min = value;
            res = i;
        }
    }

    return func.get_double_as_SEXP(res);
}

// AGP SEARCH IMPL ------------------------------------------------------------
double recalc_lip(const AGPData& d, double r);
void update_data(const AGPData& d, double& new_x, double& x_diff, double lip);
double get_global_min(const AGPData& d);

SEXP agp_search_unsafe(SEXP r_func, SEXP r_left, SEXP r_right, SEXP r_eps, SEXP r_r, SEXP rho) {

    RFunction func(r_func, rho);
    double left  = *REAL(r_left);
    double right = *REAL(r_right);
    double eps   = *REAL(r_eps);
    double r     = *REAL(r_r);
    double lip = r;

    //INFO
    printf("left: %lf\nright: %lf\neps: %lf\nr: %lf\n", left, right, eps, r);

    AGPData data;
    data.insert(std::make_pair(left, func(left)));
    data.insert(std::make_pair(right, func(right)));

    double x_diff = right - left;
    double new_x = agp_xi(left, right, func(left), func(right), lip);

    // INFO:
    //print_set(data); printf("new_x: %.8lf lip: %.8lf\n", new_x, lip);

    while( x_diff > eps) {
        data.insert(std::make_pair(new_x, func(new_x)));
        lip = recalc_lip(data, r);
        update_data(data, new_x, x_diff, lip);

        // INFO:
        print_set(data); printf("new_x: %.8lf lip: %.8lf\n", new_x, lip);
    }

    return func.get_double_as_SEXP(get_global_min(data));
}

double recalc_lip(const AGPData& d, double r) {
    double l = DBL_MIN;
    for(AGPData::const_iterator it = d.begin(); it != --d.end();) {
        double x = it->first;
        double Q = it->second;
        it++;
        double x1 = it->first;
        double Q1 = it->second;
        double tmp = fabs( (Q1 - Q) / (x1 - x) );

        if (tmp > l) { l = tmp; }
    }

    if (l < MAGIC_SMALL_NUMBER) {
        return 1;
    } else {
        return l * r;
    }
}

void update_data(const AGPData& d, double& new_x, double& x_diff, double lip) {
    double R_min = DBL_MAX;
    double x_tmp, x1_tmp, Q_tmp, Q1_tmp;
    for(AGPData::const_iterator it = d.begin(); it != --d.end();) {
        double x = it->first;
        double Q = it-> second;
        it++;
        double x1 = it->first;
        double Q1 = it->second;
        double tmp_val = agp_Ri(x, x1, Q, Q1, lip);
        if (tmp_val < R_min) {
            R_min = tmp_val;
            x_tmp = x; x1_tmp = x1;
            Q_tmp = Q; Q1_tmp = Q1;
        }
        double tmp_x = x1 - x;
        if (tmp_x < x_diff) {x_diff = tmp_x;}
    }

    new_x = agp_xi(x_tmp, x1_tmp, Q_tmp, Q1_tmp, lip);
}

double get_global_min(const AGPData& d) {
    double Q_min = DBL_MAX;
    double x_min;
    for(AGPData::const_iterator it = d.begin(); it != d.end(); it++) {
        if (it->second < Q_min) {x_min = it->first; Q_min = it->second;}
    }
    return x_min;
}

// BROKEN LINE SEARCH IMPL ----------------------------------------------------
SEXP broken_line_search_unsafe(SEXP r_func, SEXP r_left, SEXP r_right, SEXP r_eps, SEXP r_lip, SEXP rho) {
    RFunction func(r_func, rho);
    double left  = *REAL(r_left);
    double right = *REAL(r_right);
    double lip   = *REAL(r_lip);
    double eps   = *REAL(r_eps);



    return func.get_double_as_SEXP(0);
}