agp_search <- function(func, left, right, eps=0.001, r = 1.5) {
    if (!is.function(func) && !is.double(left) && !is.double(right) && !is.double(eps) && !is.double(r)) {
        return ("Wrong args type!\n")
    }
    if (right <= left) {
        return("Error: Left border are greater then right!\n")
    }
    if (r < 1) {
        return("Error: r should be equal or greater then 1!")
    }
    return(.Call("agp_search",func, left, right, eps, r, new.env()))
}

agp_search_n <- function(func, left = 0, right = 1) {
    return(.Call("agp_search_n", func, left, right, new.env()))
}