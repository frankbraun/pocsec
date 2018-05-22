#ifndef C_ASSERT_H
#define C_ASSERT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool c_assert_debug(const char *file, int line, const char *expr)
{
  /* TODO: use different logging mechanism for production? */
  fprintf(stderr, "%s,%d: assertion '%s' failed\n", file, line, expr);
#ifndef NDEBUG
  abort();
#endif
  return false;
}

/* c_assert() macro inspired by the "JPL Institutional Coding Standard
   for the C Programming Language", Rule 16,
   (see https://lars-lab.jpl.nasa.gov/JPL_Coding_Standard_C.pdf).
   Recommended use:

   if (!c_assert(p >= 0)) {
     return ERROR;
   }

   Compile with -DNDEBUG for production and without for development and testing.
*/
#define c_assert(e) ((e) ? (true) : c_assert_debug(__FILE__, __LINE__, #e))

#endif
