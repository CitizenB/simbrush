#include "bail.h"

/* FIXME: #define _BSD_SOURCE to get sys_errlist? */

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
  This function is a replacement for the (mis)use of the "perror(strcat(x, y))" idiom throughout
  simbrush.  It basically perrors with the concatenation of msg1 and msg2, then exits with the
  given exit code.  FIXME: This should perhaps be replaced by a printf-style version, but this at
  least avoids the segfaults for now.

  Does not return.
 */
void bail(int exit_code, char const* const msg1, char const* const msg2) {
  int errno_saved = errno; // quick, catch it before it gets away!
  bail_with_errno(exit_code, errno_saved, msg1, msg2);
}

void bail_with_errno(int exit_code, int errno_saved, char const* const msg1, char const* const msg2) {
  fprintf(stderr, "%s%s", msg1, msg2);

  if (errno_saved > 0)
    fprintf(stderr, ": %s\n", strerror(errno_saved));

  exit(exit_code);
}
