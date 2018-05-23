#include "c_assert.h"

c_assert_handler_func *c_assert_handler = c_assert_default_handler;

void *c_assert_handler_data = NULL;

bool c_assert_default_handler(const char *file, int line, const char *expr,
                              void *data)
{
  fprintf(stderr, "%s,%d: assertion '%s' failed\n", file, line, expr);
#ifndef NDEBUG
  abort();
#endif
  return false;
}

bool c_assert_handle(const char *file, int line, const char *expr)
{
  if (c_assert_handler) {
    return c_assert_handler(file, line, expr, c_assert_handler_data);
  }
  return false;
}