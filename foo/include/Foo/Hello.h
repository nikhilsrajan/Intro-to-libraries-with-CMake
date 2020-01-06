#ifndef HELLO_H
#define HELLO_H

#include "foo_export.h"

/*
    These things come after you run cmake once.
    - foo_export.h will be created, and we got to
      use it for to get access to hello function.
    - Prior to running cmake once, this file, in
      addition to header guards contained only
      "void hello();"
*/

void FOO_EXPORT hello();

#endif // HELLO_H