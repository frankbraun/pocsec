#define FIVEBIT_EXTERN static

#include "fivebit.c"
#include "fivebit_test.c"
#include "sixbit.c"
#include "sixbit_test.c"

GREATEST_MAIN_DEFS();

int main(int argc, char *argv[])
{
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(fivebit_suite);
  RUN_SUITE(sixbit_suite);
  GREATEST_MAIN_END();
}
