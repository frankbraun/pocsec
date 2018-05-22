#include "sixbit.h"
#include "greatest.h"

TEST sixbit_test_encode_decode(void)
{
  const char *charset =
      "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_ !\"#$%&'()*+,-./0123456789:;<=>?";
  unsigned char enc[64];
  char dec[65];
  int i;
  ASSERT_EQ(0, sixbit_encode(enc, charset, sizeof enc));
  for (i = 0; i < 64; i++) {
    ASSERT_EQ(i, enc[i]);
  }
  ASSERT_EQ(0, sixbit_decode(dec, enc, sizeof enc));
  dec[64] = '\0';
  ASSERT_STR_EQ(charset, dec);
  PASS();
}

TEST sixbit_test_encode_char(void)
{
  unsigned char out;
  int ret = sixbit_encode_char(&out, '|');
  ASSERT_EQ(SIXBIT_ERR_ENCODE, ret);
  ASSERT_STR_EQ("sixbit: cannot encode character as 6-bit ASCII",
                sixbit_errstr(ret));
  PASS();
}

TEST sixbit_test_decode_char(void)
{
  char out;
  int ret = sixbit_decode_char(&out, 64);
  ASSERT_EQ(SIXBIT_ERR_DECODE, ret);
  ASSERT_STR_EQ("sixbit: cannot decode character (not 6-bit ASCII)",
                sixbit_errstr(ret));
  PASS();
}

SUITE(sixbit_suite)
{
  RUN_TEST(sixbit_test_encode_decode);
  RUN_TEST(sixbit_test_encode_char);
  RUN_TEST(sixbit_test_decode_char);
}
