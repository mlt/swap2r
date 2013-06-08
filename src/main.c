#include <R.h>
#include <Rdefines.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

static SEXP ttutil_array = NULL;

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

SEXP rdread(SEXP xname0) {
  SEXP ret = R_NilValue;
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
    PROTECT(ret = NEW_INTEGER(no_el));
    if (isar) {
      F77_CALL(rdaint)(xname, INTEGER(ret), &no_el, &actual, strlen(xname));
      if (no_el != actual)
	REprintf("%d elements read for %s with %d elements\n", actual, xname, no_el);
    } else
      F77_CALL(rdsint)(xname, INTEGER(ret), strlen(xname));
    break;
  case 'F':
    PROTECT(ret = NEW_NUMERIC(no_el));
    if (isar) {
      F77_CALL(rdadou)(xname, REAL(ret), &no_el, &actual, strlen(xname));
      if (no_el != actual)
	REprintf("%d elements read for %s with %d elements\n", actual, xname, no_el);
    } else
      F77_CALL(rdsdou)(xname, REAL(ret), strlen(xname));
    break;
  case 'L':
    PROTECT(ret = NEW_LOGICAL(no_el));
    if (isar) {
      F77_CALL(rdalog)(xname, LOGICAL(ret), &no_el, &actual, strlen(xname));
      if (no_el != actual)
	REprintf("%d elements read for %s with %d elements\n", actual, xname, no_el);
    } else
      F77_CALL(rdslog)(xname, LOGICAL(ret), strlen(xname));
    break;
  case 'C':
    PROTECT(ret = NEW_CHARACTER(no_el));
    if (isar) {
      F77_CALL(rdacha)(xname, x, &no_el, &actual, strlen(xname), maxlen);
      if (no_el != actual)
	REprintf("%d elements read for %s with %d elements\n", actual, xname, no_el);
    } else
      F77_CALL(rdscha)(xname, x, strlen(xname), maxlen);

    for (int i=0; i<no_el; i++) {
      int j=maxlen;
      strncpy(buf, x[i], j);
      while (j>0 && ' ' == buf[--j]);
      buf[j+1] = 0;
      SET_STRING_ELT(ret, i, mkChar(buf));
    }
    break;
  case 'T':
    PROTECT(ret = NEW_NUMERIC(no_el));
    if (isar) {
      F77_CALL(rdatim)(xname, REAL(ret), &no_el, &actual, strlen(xname));
      if (no_el != actual)
	REprintf("%d elements read for %s with %d elements\n", actual, xname, no_el);
    } else
      F77_CALL(rdstim)(xname, REAL(ret), strlen(xname));
    for(int i=0; i<no_el; i++)
      REAL(ret)[i] -= 25568.d;
    SET_CLASS(ret, ScalarString(mkChar("Date")));
    break;
  case '-':
    REprintf("rdindt(""%s"") yielded '-'\n", xname);
    return R_NilValue;
  default:
    REprintf("Unexpected type was returned by rdindt for %s\n", xname);
    return R_NilValue;
  }
  if (isar && 1 == no_el)
    setAttrib(ret, ttutil_array, ScalarLogical(1));
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

SEXP wrwrite(SEXP xname0, SEXP x0) {
  SEXP e, attr;
  int no_el = 1;
  const char *xname = CHAR(STRING_ELT(xname0, 0));
  attr = getAttrib(x0, ttutil_array);
  int is_ar = isLogical(attr) ? asLogical(attr) : 0;
  no_el = LENGTH(x0);
  switch (TYPEOF(x0)) {
  case INTSXP:
    if (1 == no_el && !is_ar)
      F77_CALL(wrsint)(xname, INTEGER(x0), strlen(xname));
    else
      F77_CALL(wraint)(xname, INTEGER(x0), &no_el, &no_el, strlen(xname));
    break;
  case REALSXP:
    attr = getAttrib(x0, R_ClassSymbol);
    if (STRSXP == TYPEOF(attr) && 1 <= LENGTH(attr))
      if (0 == strcmp(CHAR(STRING_ELT(attr, 0)), "Date")) {
	for (int i=0; i<no_el; i++)
	  REAL(x0)[i] += 25568.d;
	if (1 == no_el && !is_ar)
	  F77_CALL(wrstim)(xname, REAL(x0), strlen(xname));
	else
	  F77_CALL(wratim)(xname, REAL(x0), &no_el, &no_el, strlen(xname));
      } else {
	REprintf("double with unknown class %s\n", CHAR(STRING_ELT(attr, 0)));
      }
    else {
      if (1 == no_el && !is_ar)
	F77_CALL(wrsdou)(xname, REAL(x0), strlen(xname));
      else
	F77_CALL(wradou)(xname, REAL(x0), &no_el, &no_el, strlen(xname));
    }
    break;
  case LGLSXP:
    if (1 == no_el && !is_ar)
      F77_CALL(wrslog)(xname, LOGICAL(x0), strlen(xname));
    else
      F77_CALL(wralog)(xname, LOGICAL(x0), &no_el, &no_el, strlen(xname));
    break;
  case STRSXP:
    if (1 == no_el && !is_ar) {
      const char *x = CHAR(STRING_ELT(x0, 0));
      F77_CALL(wrscha)(xname, x, strlen(xname), strlen(x));
    } else {
      size_t maxlen = 0;
      for (int i=0; i<no_el; i++)
	if (strlen(CHAR(STRING_ELT(x0, i))) > maxlen)
	  maxlen = strlen(CHAR(STRING_ELT(x0, i)));
      char x[no_el][maxlen];
      memset(x, ' ', no_el * maxlen);

      for (int i=0; i<no_el; i++) {
	memcpy(x[i], CHAR(STRING_ELT(x0, i)), strlen(CHAR(STRING_ELT(x0, i))));
      }
      F77_CALL(wracha)(xname, x, &no_el, &no_el, strlen(xname), maxlen);
    }
    break;
  case VECSXP:			/* generic lists such as data.frame */
    attr = getAttrib(x0, R_NamesSymbol);
    PROTECT(e = allocVector(STRSXP, 1));
    for (int i=0; i<no_el; i++) {
      SET_STRING_ELT(e, 0, STRING_ELT(attr, i));
      wrwrite(e, VECTOR_ELT(x0, i));
    }
    UNPROTECT(1);
    break;
  default:
    REprintf("Unexpected type %d of variable %s\n", TYPEOF(x0), xname);
  }
  return R_NilValue;
}

void
R_init_swap2r(DllInfo *info)
{
  ttutil_array = install("ttutil-array");
  /* Register routines,
     allocate resources. */
}

void
R_unload_swap2r(DllInfo *info)
{
  /* Release resources. */
}
