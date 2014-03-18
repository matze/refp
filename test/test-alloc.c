#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ref.h"


int
main (int argc, char const* argv[])
{
    refp *ref;
    char *data;

    ref = ptr_alloc (4);
    data = (char *) ref->p;

    data[0] = data[1] = data[2] = data[3] = 0;
    ptr_unref (ref);

    return 0;
}
