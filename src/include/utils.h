#ifndef __UTILS_H__
#define __UTILS_H__

// C
#include <stdlib.h>
#include <math.h>

// C++
#include <set>
#include <map>

//R internals
#include <R.h>
#include <Rinternals.h>

const double MAGIC_SMALL_NUMBER = 0.00000001;

// key: x, Q
typedef std::set< std::pair< double, double > > AGPData;

// key: x value: pair<Q, R>
typedef std::map< double, std::pair< double, double > > BLData;

inline void insert(BLData& data, double x, double Q, double R = DBL_MAX) {
    data[x] = std::make_pair(Q, R);
}

// AGP ------------------------------------------------------------------------
inline double agp_xi(double xi, double xi1, double Qi, double Qi1, double lip) {
    return 0.5 * (xi1 + xi) - (Qi1 - Qi) / (2 * lip);
}

inline double agp_Ri(double xi, double xi1, double Qi, double Qi1, double lip) {
    return lip * (xi1 - xi) + pow(Qi1 - Qi,2) / (lip * (xi1 - xi)) - 2 * (Qi1 + Qi);
}

// PIYAVSKY -------------------------------------------------------------------
inline double piyavsky_xi(double xi, double xi1, double Qi, double Qi1, double lip) {
    return 0.5 * (xi1 + xi) - (Qi1 - Qi) / (2 * lip);
}

double piyavsky_Ri(double xi, double xi1, double Qi, double Qi1, double lip) {
    return (Qi1 - Qi) / (2 * lip) - (xi1 + xi) / 2;
}

class RFunction {
private:
    SEXP r_fcall, r_tmp, rho;
public:
    RFunction(SEXP r_func, SEXP _rho) : rho(_rho) {
        r_fcall = PROTECT(lang2(r_func, R_NilValue));
        r_tmp   = PROTECT(allocVector(REALSXP, 1));
    }
    ~RFunction() {
        UNPROTECT(2);
    }

    double operator()(double arg) {
        REAL(r_tmp)[0] = arg;
        SETCADR(r_fcall, r_tmp);
        r_tmp = eval(r_fcall, rho);
        return *REAL(r_tmp);
    }

    // convert C double value to SEXP
    SEXP get_double_as_SEXP(double v) {
        REAL(r_tmp)[0] = v;
        return r_tmp;
    }
};

#endif // __UTILS_H__