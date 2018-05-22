#include <string.h>

#include "c_assert.h"
#include "sixbit.h"

SIXBIT_EXTERN int sixbit_encode_char(unsigned char *out, char in)
{
  int ret = 0;
  if (!c_assert(out)) {
    return SIXBIT_ERR_ASSERT;
  }
  if (32 <= in && in < 64) {
    *out = in;
  } else if (64 <= in && in <= 95) {
    *out = in - 64;
  } else {
    ret = SIXBIT_ERR_ENCODE;
  }
  return ret;
}

SIXBIT_EXTERN int sixbit_decode_char(char *out, unsigned char in)
{
  int ret = 0;
  if (!c_assert(out)) {
    return SIXBIT_ERR_ASSERT;
  }
  if (in < 32) {
    *out = in + 64;
  } else if (in < 64) {
    *out = in;
  } else {
    ret = SIXBIT_ERR_DECODE;
  }
  return ret;
}

SIXBIT_EXTERN int sixbit_encode(unsigned char *out, const char *in,
                                size_t length)
{
  int i, ret = 0;
  if (!c_assert(out && in)) {
    return SIXBIT_ERR_ASSERT;
  }
  for (i = 0; !ret && i < length; i++) {
    ret = sixbit_encode_char(out + i, in[i]);
  }
  return ret;
}

SIXBIT_EXTERN int sixbit_decode(char *out, const unsigned char *in,
                                size_t length)
{
  int i, ret = 0;
  if (!c_assert(out && in)) {
    return SIXBIT_ERR_ASSERT;
  }
  for (i = 0; !ret && i < length; i++) {
    ret = sixbit_decode_char(out + i, in[i]);
  }
  return ret;
}

SIXBIT_EXTERN const char *sixbit_errstr(int ret)
{
  if (!ret)
    return "";
  switch (ret) {
  case SIXBIT_ERR_ASSERT:
    return "sixbit: assertion failed";
  case SIXBIT_ERR_ENCODE:
    return "sixbit: cannot encode character as 6-bit ASCII";
  case SIXBIT_ERR_DECODE:
    return "sixbit: cannot decode character (not 6-bit ASCII)";
  }
  return "sixbit: unkown error";
}
