#ifndef C_ASSERT_H
#define C_ASSERT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* c_assert() macro inspired by the "JPL Institutional Coding Standard
   for the C Programming Language", Rule 16,
   (see https://lars-lab.jpl.nasa.gov/JPL_Coding_Standard_C.pdf).
   Recommended use:

   if (!c_assert(p >= 0)) {
     return ERROR;
   }

   Compile with -DNDEBUG for production and without for development and testing.
*/
#define c_assert(e) ((e) ? (true) : c_assert_handle(__FILE__, __LINE__, #e))

/* An assertion handler. Should return false to mark the assertion as failed.
   Should return true to ignore failed assertions completely. */
typedef bool c_assert_handler_func(const char *file, int line, const char *expr,
                                   void *data);

/* The assertion handler. The default is c_assert_default_handler. Set to NULL
   to disable logging of assertions. */
extern c_assert_handler_func *c_assert_handler;

/* Data pointer passed to the assertion handler. */
extern void *c_assert_handler_data;

/* The default assert handler, prints the failed assertion to stderr and then
   calls abort(3) if not compiled with NDEBUG. */
bool c_assert_default_handler(const char *file, int line, const char *expr,
                              void *data);

/* Internal function that calls the c_assert_handler, if not NULL. */
bool c_assert_handle(const char *file, int line, const char *expr);

#endif
