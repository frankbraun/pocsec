#include "fivebit.h"
#include "greatest.h"

TEST fivebit_test_encode_decode(void)
{
  const char *charset = "@ABCDEFGHIJKLMNOPQRSTUVWXYZ !,.?";
  unsigned char enc[32];
  char dec[33];
  int i;
  ASSERT_EQ(0, fivebit_encode(enc, charset, sizeof enc));
  for (i = 0; i < 32; i++) {
    ASSERT_EQ(i, enc[i]);
  }
  ASSERT_EQ(0, fivebit_decode(dec, enc, sizeof enc));
  dec[32] = '\0';
  ASSERT_STR_EQ(charset, dec);
  PASS();
}

TEST fivebit_test_encode_char(void)
{
  unsigned char out;
  int ret = fivebit_encode_char(&out, '|');
  ASSERT_EQ(FIVEBIT_ERR_ENCODE, ret);
  ASSERT_STR_EQ("fivebit: cannot encode character as 5-bit ASCII",
                fivebit_errstr(ret));
  PASS();
}

TEST fivebit_test_decode_char(void)
{
  char out;
  int ret = fivebit_decode_char(&out, 32);
  ASSERT_EQ(FIVEBIT_ERR_DECODE, ret);
  ASSERT_STR_EQ("fivebit: cannot decode character (not 5-bit ASCII)",
                fivebit_errstr(ret));
  PASS();
}

SUITE(fivebit_suite)
{
  RUN_TEST(fivebit_test_encode_decode);
  RUN_TEST(fivebit_test_encode_char);
  RUN_TEST(fivebit_test_decode_char);
}
