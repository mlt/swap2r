#include <R.h>
#include <Rdefines.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

/* TODO: Rewrite with .Call */
void rdinit(int* iunit, int* iulog, char** datfil) {
  F77_CALL(rdinit)(iunit, iulog, datfil[0], strlen(datfil[0]));
}

SEXP wrinit(SEXP iunit0, SEXP datfil0) {
  int iunit = asInteger(iunit0);
  const char* datfil = CHAR(STRING_ELT(datfil0, 0));
  F77_CALL(wrinit)(&iunit, datfil, strlen(datfil));
  return R_NilValue;
}

/* void rdsrea(char** xname, float* x) { */
/*   F77_CALL(rdsrea)(xname[0], x, strlen(xname[0])); */
/* } */

/* TODO: Convert me to .Call */
void rdsdou(char** xname, double* x) {
  F77_CALL(rdsdou)(xname[0], x, strlen(xname[0]));
}

/* void rdscha(char** xname, char** x) { */
/*   size_t xlen = 255; */
/*   F77_CALL(rdscha)(xname[0], x[0], strlen(xname[0]), xlen); */
/*   while (' ' == x[0][--xlen]); */
/*   x[0][xlen+1] = 0; */
/* } */

SEXP rdscha(SEXP xname0) {
  size_t xlen = 255;
  char x[xlen+1];
  SEXP ret;
  const char *xname = CHAR(STRING_ELT(xname0, 0));
  F77_CALL(rdscha)(xname, x, strlen(xname), xlen);
  while (' ' == x[--xlen]);
  x[xlen+1] = 0;

  PROTECT(ret = NEW_CHARACTER(1));
  SET_STRING_ELT(ret, 0, mkChar(x));
  UNPROTECT(1);
  return ret;
}

/* TODO: remove me */
/* SEXP rdarea(SEXP xname0) { */
/*   int ildec = 1024; */
/*   int ifnd; */
/*   float x[ildec]; */
/*   SEXP ret; */
/*   const char *xname = CHAR(STRING_ELT(xname0, 0)); */
/*   F77_CALL(rdarea)(xname, x, &ildec, &ifnd, strlen(xname)); */

/*   PROTECT(ret = NEW_NUMERIC(ifnd)); */
/*   for (int i=0; i<ifnd; i++) */
/*     REAL(ret)[i] = x[i]; */
/*   UNPROTECT(1); */
/*   return ret; */
/* } */

SEXP rdadou(SEXP xname0) {
  int ildec = 1024;
  int ifnd;
  double x[ildec];
  SEXP ret;
  const char *xname = CHAR(STRING_ELT(xname0, 0));
  F77_CALL(rdadou)(xname, x, &ildec, &ifnd, strlen(xname));

  PROTECT(ret = NEW_NUMERIC(ifnd));
  for (int i=0; i<ifnd; i++)
    REAL(ret)[i] = x[i];
  UNPROTECT(1);
  return ret;
}

SEXP rdinlv(SEXP setflag0) {
  const int maxlen = 31;
  int varlis_mn = 10240;
  int varlis_an;
  int setflag = asLogical(setflag0);
  char varlis[varlis_mn][maxlen];
  char buf[maxlen+1];
  SEXP ret;
  F77_CALL(rdinlv)(&setflag, varlis, &varlis_mn, &varlis_an, maxlen);

  PROTECT(ret = NEW_CHARACTER(varlis_an));
  for (int i=0; i<varlis_an; i++) {
    int j=maxlen;
    strncpy(buf, varlis[i], j);
    while (' ' == buf[--j]);
    buf[j+1] = 0;
    SET_STRING_ELT(ret, i, mkChar(buf));
  }
  UNPROTECT(1);
  return ret;
}

SEXP rdinne(SEXP xname0) {
  SEXP no_el;
  const char *xname = CHAR(STRING_ELT(xname0, 0));
  PROTECT(no_el = NEW_INTEGER(1));
  F77_CALL(rdinne)(xname, INTEGER(no_el), strlen(xname));
  UNPROTECT(1);
  return no_el;
}

SEXP rdindt(SEXP xname0) {
  SEXP ret;
  char buf[2];
  const char *xname = CHAR(STRING_ELT(xname0, 0));
  F77_CALL(rdindt)(xname, buf, strlen(xname), 1);
  buf[1] = 0;
  PROTECT(ret = NEW_CHARACTER(1));
  SET_STRING_ELT(ret, 0, mkChar(buf));
  UNPROTECT(1);
  return ret;
}

SEXP rdinar(SEXP xname0) {
  SEXP ret;
  int isar;
  const char *xname = CHAR(STRING_ELT(xname0, 0));
  PROTECT(ret = NEW_LOGICAL(1));
  LOGICAL(ret)[0] = F77_CALL(rdinar)(xname, strlen(xname));
  UNPROTECT(1);
  return ret;
}

SEXP rdsint(SEXP xname0) {
  SEXP ret;
  const char *xname = CHAR(STRING_ELT(xname0, 0));
  PROTECT(ret = NEW_INTEGER(1));
  F77_CALL(rdsint)(xname, INTEGER(ret), strlen(xname));
  UNPROTECT(1);
  return ret;
}

/* SEXP rdaint(SEXP xname0) { */
/*   SEXP ret; */
/*   const char *xname = CHAR(STRING_ELT(xname0, 0)); */
/*   PROTECT(ret = NEW_INTEGER(1)); */
/*   F77_CALL(rdsint)(xname, INTEGER(ret), strlen(xname)); */
/*   UNPROTECT(1); */
/*   return ret; */
/* } */

SEXP rdslog(SEXP xname0) {
  SEXP ret;
  const char *xname = CHAR(STRING_ELT(xname0, 0));
  PROTECT(ret = NEW_LOGICAL(1));
  F77_CALL(rdslog)(xname, LOGICAL(ret), strlen(xname));
  UNPROTECT(1);
  return ret;
}

SEXP rdstim(SEXP xname0) {
  SEXP ret;
  const char *xname = CHAR(STRING_ELT(xname0, 0));
  PROTECT(ret = NEW_NUMERIC(1));
  F77_CALL(rdstim)(xname, REAL(ret), strlen(xname));
  UNPROTECT(1);
  return ret;
}

SEXP rdatim(SEXP xname0) {
  int ildec = 1024;
  int ifnd;
  double x[ildec];
  SEXP ret;
  const char *xname = CHAR(STRING_ELT(xname0, 0));
  F77_CALL(rdatim)(xname, x, &ildec, &ifnd, strlen(xname));

  PROTECT(ret = NEW_NUMERIC(ifnd));
  for (int i=0; i<ifnd; i++)
    REAL(ret)[i] = x[i];
  UNPROTECT(1);
  return ret;
}

SEXP rdread(SEXP xname0) {
  SEXP e, ret = R_NilValue;
  char cType;
  int isar = 0;
  int no_el = 1;
  int actual, errorOccurred;
  size_t maxlen = 255;		/* max char length */
  size_t xlen = 255;		/* max char elements */
  char buf[maxlen+1];
  char x[xlen][maxlen];
  const char *xname = CHAR(STRING_ELT(xname0, 0));
  F77_CALL(rdindt)(xname, &cType, strlen(xname), 1);
  isar = F77_CALL(rdinar)(xname, strlen(xname));
  if (isar) {
    F77_CALL(rdinne)(xname, &no_el, strlen(xname));
  }
  switch (cType) {
  case 'I':
    /* Rprintf("Allocating integer vector with %d elements\n", no_el); */
    PROTECT(ret = NEW_INTEGER(no_el));
    if (isar) {
      F77_CALL(rdaint)(xname, INTEGER(ret), &no_el, &actual, strlen(xname));
      if (no_el != actual)
	REprintf("Wrong number of elements read\n");
    } else
      F77_CALL(rdsint)(xname, INTEGER(ret), strlen(xname));
    break;
  case 'F':
    PROTECT(ret = NEW_NUMERIC(no_el));
    if (isar) {
      F77_CALL(rdadou)(xname, REAL(ret), &no_el, &actual, strlen(xname));
      if (no_el != actual)
	REprintf("Wrong number of elements read\n");
    } else
      F77_CALL(rdsdou)(xname, REAL(ret), strlen(xname));
    break;
  case 'L':
    PROTECT(ret = NEW_LOGICAL(no_el));
    if (isar) {
      F77_CALL(rdalog)(xname, LOGICAL(ret), &no_el, &actual, strlen(xname));
      if (no_el != actual)
	REprintf("Wrong number of elements read\n");
    } else
      F77_CALL(rdslog)(xname, LOGICAL(ret), strlen(xname));
    break;
  case 'C':
    PROTECT(ret = NEW_CHARACTER(no_el));
    if (isar) {
      F77_CALL(rdacha)(xname, x, &no_el, &actual, strlen(xname), maxlen);
      if (no_el != actual)
	REprintf("Wrong number of elements read\n");
    } else
      F77_CALL(rdscha)(xname, x, strlen(xname), maxlen);

    for (int i=0; i<no_el; i++) {
      int j=maxlen;
      strncpy(buf, x[i], j);
      while (' ' == buf[--j]);
      buf[j+1] = 0;
      SET_STRING_ELT(ret, i, mkChar(buf));
    }
    break;
  case 'T':
    PROTECT(ret = NEW_NUMERIC(no_el));
    if (isar) {
      F77_CALL(rdatim)(xname, REAL(ret), &no_el, &actual, strlen(xname));
      if (no_el != actual)
	REprintf("Wrong number of elements read\n");
    } else
      F77_CALL(rdstim)(xname, REAL(ret), strlen(xname));
    PROTECT(e = allocVector(LANGSXP, 3));
    SETCAR(e, Rf_install("as.Date"));
    SETCADR(e, ret); /* e = CDR(e); */
    SETCADDR(e, ScalarString(mkChar("1899-12-31")));
    SET_TAG(CDDR(e), install("origin"));
    ret = R_tryEval(e, NULL, &errorOccurred);
    UNPROTECT(1);
    break;
  case '-':
    REprintf("Uknown type was returned by rdindt\n");
    break;
  default:
    REprintf("Unexpected type was returned by rdindt\n");
  }
  UNPROTECT(1);
  return ret;
}

/***********************************************************/
SEXP wrscha(SEXP xname0, SEXP x0) {
  const char *xname = CHAR(STRING_ELT(xname0, 0));
  const char *x = CHAR(STRING_ELT(x0, 0));
  F77_CALL(wrscha)(xname, x, strlen(xname), strlen(x));
  return R_NilValue;
}


void
R_init_swap2r(DllInfo *info)
{
  /* Register routines,
     allocate resources. */
}

void
R_unload_swap2r(DllInfo *info)
{
  /* Release resources. */
}
