#ifndef __UTILS_H__
#define __UTILS_H__

//R internals
#include <R.h>
#include <Rinternals.h>

// константа близкая к нулю, для сравнения double с нулём
const double MAGIC_SMALL_NUMBER = 0.00000001;

//typedef std::vector< double > rvector;

// класс, обёртка над R функцией принимающей double и возвращающей bouble
class RFunction {
private:
    SEXP r_fcall;   // "дескриптор" функции на R
    SEXP r_tmp;     // перменная R, аргумент - значение функции
    SEXP rho;       // 

public:
    RFunction(SEXP r_func, SEXP _rho)
            : rho(_rho) {
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

class RNFunction {
private:
    SEXP r_fcall;
    SEXP rho;

public:
    RNFunction(SEXP r_func, SEXP _rho)
        : rho(_rho) {

    }
    ~RNFunction() {
    }

    double operator()() {
        return 0;
    }

};

#endif // __UTILS_H__