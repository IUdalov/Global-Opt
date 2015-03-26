#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits>
#include <set>

const double MAGIC_SMALL_NUMBER = 0.00000001;
const double DBL_MAX = std::numeric_limits<double>::max();
const double DBL_MIN = std::numeric_limits<double>::min();

volatile double func(double x) {
    return sin(4 * x) + 2 * cos(x) + 0.01 * pow((x - 0.1), 2);
}

typedef std::set< std::pair< double, double > > Points;

bool parse_args(int argc, char* argv[], double& left, double& right, double& eps, double& r) {
    if (argc < 3) { return false; }
    left = atof(argv[1]);
    right = atof(argv[2]);
    if (right < left) { return false; }
    if (argc > 3) { eps = atof(argv[3]); }
    if (argc > 4) {
        r = atof(argv[4]);
    }
    if (argc > 5) {
        return false;
    } else {
        return true;
    }
}

void print_usage(char* progname) {
    printf("Usage: %s <left limit> <right limit> [<eps>] [<r>]\n", progname);
    printf("    Left limit must be greater than right limit.\n");
    printf("    r >= 1\n");
}

// AGP ------------------------------------------------------------------------
inline double agp_xi(double xi, double xi1, double Qi, double Qi1, double lip) {
    return 0.5 * (xi1 + xi) - (Qi1 - Qi) / (2 * lip);
}

inline double agp_Ri(double xi, double xi1, double Qi, double Qi1, double lip) {
    return lip * (xi1 - xi) + pow(Qi1 - Qi, 2) / (lip * (xi1 - xi)) - 2 * (Qi1 + Qi);
}

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
    double x_tmp, x1_tmp, Q_tmp, Q1_tmp;
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
    double x_min;
    for(Points::const_iterator it = d.begin(); it != d.end(); it++) {
        if (it->second < Q_min) {x_min = it->first; Q_min = it->second;}
    }
    return x_min;
}

double agp_serach(double left, double right, double eps, double r) {
    double lip = r;

    Points data;
    data.insert(std::make_pair(left, func(left)));
    data.insert(std::make_pair(right, func(right)));

    double x_diff = right - left;
    double new_x = agp_xi(left, right, func(left), func(right), lip);

    while( x_diff > eps) {
        data.insert(std::make_pair(new_x, func(new_x)));
        lip = recalc_lip(data, r);
        update_data(data, new_x, x_diff, lip);
    }

    return get_global_min(data);
}

int main(int argc, char* argv[]) {
    double left = 0;
    double right = 1;
    double eps = 0.001;
    double r = 1.5;

    if (!parse_args(argc, argv, left, right, eps, r)) {
        print_usage(argv[0]);
        return 0;
    }

    //printf(" left: %.8lf\nright: %.8lf\n  eps: %.8lf\n    r: %.8lf\n", left, right, eps, r);
    printf("Global minimun at %.15lf\n", agp_serach(left, right, eps, r));
    return 0;
}