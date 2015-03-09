test_func <- function(x) {
    3 * sin(2 * (x)) + 5 * cos(1 * (x)) + 0.5
}

prep_all <- function() {
    dyn.load("bin/libopt.so")
}

direct_search_pure_r <- function(a, b, n) {
    min_val <- test_func(a)
    min_arg <- a
    step <- (b - a) / n
    curr <- a;
    while(curr <= b) {
        curr <- curr + step
        tmp <- test_func(curr)
        if (tmp < min_val) {
                min_val <- tmp
                min_arg <- curr
            }
    }
    return(min_arg);
}

direct_search_pure_c <- function(a, b, n) {
    cmd <- paste("tests/direct_search.bin", sprintf("%d", a), sprintf("%d", b), sprintf("%d", n))
    # cat(cmd)
    system(cmd);
}

direct_search_r_c <- function(a, b, n) {
    .Call("direct_search", test_func, a, b, n, new.env())
}

# TODO:
run_one_test <- function(n) {
    cat("Pure C\n");
    system.time(direct_search_pure_c(0, 100, n))
    cat("Pure R\n");
    system.time(direct_search_pure_r(0, 100, n))
    cat("R & C\n");
    system.time(direct_search_r_c(0, 100, n))
}