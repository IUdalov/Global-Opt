agp_search <- function(func, left, right, eps=0.001, r = 1.5) {
    if (!is.function(func) && !is.double(left) && !is.double(right) && !is.double(eps) && !is.double(r)) {
        return ("Wrong args type!")
    }
    if (right <= left) {
        return("Error: Left border are greater then right!")
    }
    if (r < 1) {
        return("Error: r should be equal or greater then 1!")
    }
    return(.Call("agp_search",func, left, right, eps, r, new.env()))
}

# TODO: check args
agp <- function(func, left = c(0,0), right = c(1,1)) {
    if (length(left) != length(right) || length(left) < 1) {
        return ("Error! Wrong bounds!")
    }
    return(.Call("agp_search_n", func, length(left), left, right, new.env()))
}

agp <- agp_search_n