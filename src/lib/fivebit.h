#ifndef FIVEBIT_H
#define FIVEBIT_H

#include <stddef.h>

#ifndef FIVEBIT_EXTERN
#define FIVEBIT_EXTERN
#endif

#define FIVEBIT_ERR_ASSERT -2 /* Assertion failed. */
#define FIVEBIT_ERR_ENCODE -3 /* Cannot encode character. */
#define FIVEBIT_ERR_DECODE -4 /* Cannot decode character. */

/* Encode a single character in to 5-bit ASCII stored in out.
   In case of error, FIVEBIT_ERR_ENCODE is returned. */
FIVEBIT_EXTERN int fivebit_encode_char(unsigned char *out, char in);

/* Decode a single 5-bit ASCII character in and store the result in out.
   In case of error, FIVEBIT_ERR_DECODE is returned. */
FIVEBIT_EXTERN int fivebit_decode_char(char *out, unsigned char in);

/* Encode character buffer in with given length in 5-bit ASCII and store the
   result in out. In case of error, FIVEBIT_ERR_ENCODE is returned. */
FIVEBIT_EXTERN int fivebit_encode(unsigned char *out, const char *in,
                                  size_t length);

/* Decode 5-bit ASCII character buffer in (with given length) and store the
   result in out. In case of error, FIVEBIT_ERR_DECODE is returned. */
FIVEBIT_EXTERN int fivebit_decode(char *out, const unsigned char *in,
                                  size_t length);

/* Return string decribing error code ret. */
FIVEBIT_EXTERN const char *fivebit_errstr(int ret);

#endif
