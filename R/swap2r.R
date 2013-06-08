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
##' @useDynLib swap2r
rdinit <- function(datfil, iunit=30, iulog=0) {
  .C("rdinit", iunit=as.integer(iunit), iulog=as.integer(iulog), datfil=datfil)
}

##' Return list of variables
##' @title rdinlv
##' @param setflag Flag through which is indicated whether information
##' from a possibly active rerun set is wanted
##' @return a vector of variables
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
rdinlv <- function(setflag=FALSE) {
    .Call("rdinlv", setflag=setflag)
}

##' Return # of elements of a variable
##' @title rdinne
##' @param xname Variable name
##' @return # of elements
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
rdinne <- function(xname) {
    .Call("rdinne", xname=xname)
}

##' Return data type of a variable
##' @title rdindt
##' @param xname Variable name
##' @return character
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
rdindt <- function(xname) {
    .Call("rdindt", xname=xname)
}

##' Check whether variable is an array
##' @title rdinar
##' @param xname Variable name
##' @return logical
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
rdinar <- function(xname) {
    .Call("rdinar", xname=xname)
}

##' Universal read function
##' @title rdread
##' @param xname parameter
##' @return a value read
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
rdread <- function(xname) {
  .Call("rdread", xname=xname)
}

##' Read all parameters from the file into a list.
##' @title read.tt
##' @param fname file name to read data from
##' @return \code{list} with parameters read.
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
read.tt <- function(fname) {
    rdinit(fname, 30)
    out <- sapply(rdinlv(), rdread)
    wrclose(30)
    out
}

#############################################################

##' Initializes TTUTIL for writing
##'
##' Supply FORTRAN file descriptor
##' @title wrinit
##' @param datfil name of configuration file to write
##' @param iunit some unit number to associate
##' @return a \code{list} of formal arguments
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
wrinit <- function(datfil, iunit=50) {
  .Call("wrinit", iunit=as.integer(iunit), datfil=datfil)
}

##' Close fortrain unit
##' @title wrclose
##' @param iunit unit to close
##' @return a \code{list} of formal arguments
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
wrclose <- function(iunit=50) {
  .Fortran("wrclose", iunit=as.integer(iunit))
}

##' Universal writes function
##' @title wrwrite
##' @param xname parameter
##' @param x value
##' @return a \code{list} of formal arguments
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
wrwrite <- function(xname, x) {
  .Call("wrwrite", xname=xname, x=x)
}

##' Write list with parameters to a file.
##'
##' List will be flattened.
##' @title write.tt
##' @param x list with parameters to write
##' @param fname file name to read data from
##' @return Nothing
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
write.tt <- function(x, fname) {
    wrinit(fname, 60)
    wrwrite("dummy", x)
    wrclose(60)
    NULL
}
