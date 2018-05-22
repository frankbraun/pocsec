#ifndef SIXBIT_H
#define SIXBIT_H

#include <stddef.h>

#ifndef SIXBIT_EXTERN
#define SIXBIT_EXTERN
#endif

#define SIXBIT_ERR_ASSERT -2 /* Assertion failed. */
#define SIXBIT_ERR_ENCODE -3 /* Cannot encode character. */
#define SIXBIT_ERR_DECODE -4 /* Cannot decode character. */

/* Encode a single character in to 6-bit ASCII stored in out.
   In case of error, SIXBIT_ERR_ENCODE is returned. */
SIXBIT_EXTERN int sixbit_encode_char(unsigned char *out, char in);

/* Decode a single 6-bit ASCII character in and store the result in out.
   In case of error, SIXBIT_ERR_DECODE is returned. */
SIXBIT_EXTERN int sixbit_decode_char(char *out, unsigned char in);

/* Encode character buffer in with given length in 6-bit ASCII and store the
   result in out. In case of error, SIXBIT_ERR_ENCODE is returned. */
SIXBIT_EXTERN int sixbit_encode(unsigned char *out, const char *in,
                                size_t length);

/* Decode 6-bit ASCII character buffer in (with given length) and store the
   result in out. In case of error, SIXBIT_ERR_DECODE is returned. */
SIXBIT_EXTERN int sixbit_decode(char *out, const unsigned char *in,
                                size_t length);

/* Return string decribing error code ret. */
SIXBIT_EXTERN const char *sixbit_errstr(int ret);

#endif
