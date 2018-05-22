#include <string.h>

#include "c_assert.h"
#include "fivebit.h"

FIVEBIT_EXTERN int fivebit_encode_char(unsigned char *out, char in)
{
  const char *charset = "@ABCDEFGHIJKLMNOPQRSTUVWXYZ !,.?";
  int ret = 0;
  char *r;
  if (!c_assert(out)) {
    return FIVEBIT_ERR_ASSERT;
  }
  r = strchr(charset, in);
  if (!r) {
    ret = FIVEBIT_ERR_ENCODE;
  } else {
    *out = r - charset;
  }
  return ret;
}

/* 64-90 "@ABCDEFGHIJKLMNOPQRSTUVWXYZ"
   32 ' '
   33 '!'
   44 ','
   46 '.'
   63 '?' */
FIVEBIT_EXTERN int fivebit_decode_char(char *out, unsigned char in)
{
  int ret = 0;
  if (!c_assert(out)) {
    return FIVEBIT_ERR_ASSERT;
  }
  if (in < 27) {
    *out = in + 64;
  } else {
    switch (in) {
    case 27:
      *out = ' ';
      break;
    case 28:
      *out = '!';
      break;
    case 29:
      *out = ',';
      break;
    case 30:
      *out = '.';
      break;
    case 31:
      *out = '?';
      break;
    default:
      ret = FIVEBIT_ERR_DECODE;
    }
  }
  return ret;
}

FIVEBIT_EXTERN int fivebit_encode(unsigned char *out, const char *in,
                                  size_t length)
{
  int i, ret = 0;
  if (!c_assert(out && in)) {
    return FIVEBIT_ERR_ASSERT;
  }
  for (i = 0; !ret && i < length; i++) {
    ret = fivebit_encode_char(out + i, in[i]);
  }
  return ret;
}

FIVEBIT_EXTERN int fivebit_decode(char *out, const unsigned char *in,
                                  size_t length)
{
  int i, ret = 0;
  if (!c_assert(out && in)) {
    return FIVEBIT_ERR_ASSERT;
  }
  for (i = 0; !ret && i < length; i++) {
    ret = fivebit_decode_char(out + i, in[i]);
  }
  return ret;
}

FIVEBIT_EXTERN const char *fivebit_errstr(int ret)
{
  if (!ret)
    return "";
  switch (ret) {
  case FIVEBIT_ERR_ASSERT:
    return "fivebit: assertion failed";
  case FIVEBIT_ERR_ENCODE:
    return "fivebit: cannot encode character as 5-bit ASCII";
  case FIVEBIT_ERR_DECODE:
    return "fivebit: cannot decode character (not 5-bit ASCII)";
  }
  return "fivebit: unkown error";
}
