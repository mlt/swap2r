##' Initializes TTUTIL for reading
##'
##' Supply FORTRAN file descriptors
##' @title rdinit
##' @param datfil name of configuration file to read
##' @param iunit
##' @param iulog
##' @return a \code{list} of formal arguments
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
rdinit <- function(datfil, iunit=30, iulog=40) {
  .C("rdinit", iunit=as.integer(iunit), iulog=as.integer(iulog), datfil=datfil)
}
