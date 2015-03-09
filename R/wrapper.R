
direct_search <- function(func, left, right, steps=1000) {
    return(.Call("direct_search",func, left, right, steps, new.env()))
}

agp_search <- function(func, left, right, eps=0.001, r = 1.5) {
    return(.Call("agp_search",func, left, right, eps, r, new.env()))
}

broken_line_search <- function(func, left, right, eps=0.001, lip = 1.5) {
    return(.Call("broken_line_search_unsafe",func, left, right, eps, lip, new.env()))
}

wild <- function(x) {       ## 'Wild' function, global minimum at about -15.81515
    sum(10 * sin(0.3 * x) * sin(1.3 * x^2) + 0.00001 * x^4 + 0.2 * x + 80)/length(x)
}

sincos <- function(x) {
    sin(x) * cos(x)
}