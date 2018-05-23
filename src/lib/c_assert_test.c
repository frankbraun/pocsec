#include "c_assert.h"
#include "greatest.h"

static bool c_assert_test_handler(const char *file, int line, const char *expr,
                                  void *data)
{
  bool *called = data;
  *called = true;
  return false;
}

TEST c_assert_test_success(void)
{
  bool called = false;
  c_assert_handler = c_assert_test_handler;
  c_assert_handler_data = &called;
  ASSERT_EQ(true, c_assert(true));
  ASSERT_EQ(false, called);
  PASS();
}

TEST c_assert_test_failure(void)
{
  bool called = false;
  c_assert_handler = c_assert_test_handler;
  c_assert_handler_data = &called;
  ASSERT_EQ(false, c_assert(false));
  ASSERT_EQ(true, called);
  PASS();
}
SUITE(c_assert_suite)
{
  RUN_TEST(c_assert_test_success);
  RUN_TEST(c_assert_test_failure);
}