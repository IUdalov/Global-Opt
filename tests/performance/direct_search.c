#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define func(x) ( 3 * sin(2 * (x)) + 5 * cos(1 * (x)) + 0.5)

int main(int argc, char* argv[]) {
    double a, b, step, curr, min_val, min_arg, tmp;
    int steps;

    if( argc < 4) {
        printf("Error, too few args.\n");
        exit(1);
    }

    a = atof(argv[1]);
    b = atof(argv[2]);
    steps = atoi(argv[3]);
    step = (b - a) / (double)steps;
    min_arg = a;
    min_val = func(min_arg);

    for(curr = a + step; curr <= b; curr += step) {
        tmp = func(curr);
        if (tmp < min_val) {
            min_arg = curr;
            min_val = tmp;
        }
    }
    printf("%.15lf\n", min_arg);
    return 0;
}
