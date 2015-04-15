#include <set>
#include "methods.h"
#include "utils.h"
#include "stdio.h"

// Набор точек, в которых происхоило измерение функии 
// <аргумент, значение>
typedef std::set< std::pair< double, double > > Points;

static inline double agp_xi(double xi, double xi1, double Qi, double Qi1, double lip) {
    return 0.5 * (xi1 + xi) - (Qi1 - Qi) / (2 * lip);
}

static inline double agp_Ri(double xi, double xi1, double Qi, double Qi1, double lip) {
    return lip * (xi1 - xi) + pow(Qi1 - Qi, 2) / (lip * (xi1 - xi)) - 2 * (Qi1 + Qi);
}

#ifdef DEBUG
void print_points(const Points& points) {
    for(Points::const_iterator it = points.begin(); it != points.end(); it++) {
        printf("x: %.7lf Q: %.7lf\n", it->first, it->second);
    }
    printf("Total points: %u\n", points.size());
}
#endif

static  double recalc_lip(const Points& d, double r) {
    double l = DBL_MIN;
    for(Points::const_iterator it = d.begin(); it != --d.end();) {
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

static void update_data(const Points& d, double& new_x, double& x_diff, double lip) {
    double R_max = -1000; //TOREMOVE
    double x_tmp = 0, x1_tmp = 0, Q_tmp = 0, Q1_tmp = 0;
    for(Points::const_iterator it = d.begin(); it != --d.end(); /*empty*/) {
        double x = it->first;
        double Q = it-> second;
        it++;
        double x1 = it->first;
        double Q1 = it->second;
        double tmp_val = agp_Ri(x, x1, Q, Q1, lip);

        if (tmp_val > R_max) {
            R_max = tmp_val;
            x_tmp = x; x1_tmp = x1;
            Q_tmp = Q; Q1_tmp = Q1;
        }

        double tmp_diff = x1 - x;
        if (tmp_diff < x_diff) {x_diff = tmp_diff;}
    }

    new_x = agp_xi(x_tmp, x1_tmp, Q_tmp, Q1_tmp, lip);
}

static double get_global_min(const Points& d) {
    double Q_min = DBL_MAX;
    double x_min = 0;
    for(Points::const_iterator it = d.begin(); it != d.end(); it++) {
        if (it->second < Q_min) {x_min = it->first; Q_min = it->second;}
    }
    return x_min;
}

SEXP agp_search_unsafe(SEXP r_func, SEXP r_left, SEXP r_right, SEXP r_eps, SEXP r_r, SEXP rho) {

    RFunction func(r_func, rho);
    double left  = *REAL(r_left);
    double right = *REAL(r_right);
    double eps   = *REAL(r_eps);
    double r     = *REAL(r_r);
    double lip = r;

#ifdef DEBUG
    printf("left: %.7lf\nright: %.7lf\n eps: %.7lf\n r: %.7lf\n", left, right, eps, r);
#endif

    Points data;
    data.insert(std::make_pair(left, func(left)));
    data.insert(std::make_pair(right, func(right)));

    double x_diff = right - left;
    double new_x = agp_xi(left, right, func(left), func(right), lip);

    while( x_diff > eps) {
        data.insert(std::make_pair(new_x, func(new_x)));
        lip = recalc_lip(data, r);
        update_data(data, new_x, x_diff, lip);
#ifdef DEBUG
            printf("new_x: %.7lf\n", new_x);
#endif
    }

#ifdef DEBUG
    print_points(data);
#endif

    return func.get_double_as_SEXP(get_global_min(data));
}
