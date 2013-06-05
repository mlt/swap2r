##' Read single double value
##' @aliases rdsrea
##' @title rdsdou
##' @param xname parameter name
##' @return a double value read
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export rdsdou rdsrea
##' @useDynLib swap2r
rdsdou <- function(xname) {
    .C("rdsdou", xname=xname, x=as.double(0))$x
}
rdsrea <- rdsdou

##' Read single character value
##' @title rdscha
##' @param xname parameter name
##' @return a string value
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
rdscha <- function(xname) {
    .Call("rdscha", xname=xname)
}

##' Read array of double values
##' @aliases rdarea
##' @title rdadou
##' @param xname parameter name
##' @return a double valued vector read
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export rdarea rdadou
rdadou <- function(xname) {
    .Call("rdadou", xname=xname)
}
rdarea <- rdadou

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

##' Reads a single integer
##' @title rdsint
##' @param xname Variable name
##' @return integer
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
rdsint <- function(xname) {
    .Call("rdsint", xname=xname)
}

##' Reads a single logical
##' @title rdslog
##' @param xname Variable name
##' @return logical
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
rdslog <- function(xname) {
    .Call("rdslog", xname=xname)
}

##' Reads a single date/time
##' @title rdstim
##' @param xname Variable name
##' @return POSIXct
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
rdstim <- function(xname) {
    as.Date("1899-12-31") + .Call("rdstim", xname=xname)
}

##' Reads date/time array
##' @title rdatim
##' @param xname Variable name
##' @return POSIXct
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
rdatim <- function(xname) {
    as.Date("1899-12-31") + .Call("rdatim", xname=xname)
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
  .Call("wrinit", iunit=iunit, datfil=datfil)
}

##' Close fortrain unit
##' @title wrclose
##' @param iunit unit to close
##' @return a \code{list} of formal arguments
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
wrclose <- function(iunit=50) {
  .Fortran("wrclose", iunit=iunit)
}

##' Writes a single character string
##' @title wrscha
##' @param xname parameter
##' @param x value
##' @return a \code{list} of formal arguments
##' @author Mikhail Titov (\email{mlt@@gmx.us})
##' @export
wrscha <- function(xname, x) {
  .Call("wrscha", xname=xname, x=x)
}
