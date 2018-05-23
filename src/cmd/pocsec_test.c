#define FIVEBIT_EXTERN static
#define SIXBIT_EXTERN static

#include "c_assert.c"
#include "c_assert_test.c"
#include "fivebit.c"
#include "fivebit_test.c"
#include "sixbit.c"
#include "sixbit_test.c"

GREATEST_MAIN_DEFS();

int main(int argc, char *argv[])
{
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(c_assert_suite);
  RUN_SUITE(fivebit_suite);
  RUN_SUITE(sixbit_suite);
  GREATEST_MAIN_END();
}
