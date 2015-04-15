# test function
wild1d <- function(x) {       ## 'Wild1d' function, global minimum at about -15.81515
    sum(10 * sin(0.3 * x) * sin(1.3 * x^2) + 0.00001 * x^4 + 0.2 * x + 80)/length(x)
}

sincos1d <- function(x) {     ## 'sincos1d' function, global minimum at about 2.78877
    sin(4 * x) + 2 * cos(x) + 0.01 * (x - 0.1)^2
}

rosenbrock2d <- function(x) { ## 'rosenbrock2d' function, global minimum  at (1,1)
    (1 - x[1])^2 + 100 * (x[2] - x[1]^2)^2
}