#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ref.h"

static int destroy_ran = 0;

static void
destroy (void *p)
{
    free (p);
    destroy_ran = 1;
}

int
main (int argc, char const* argv[])
{
    refp *ref;

    ref = ptr_new (strdup ("foobar"), destroy);
    ptr_ref (ref);

    if (destroy_ran)
        return 1;

    ptr_unref (ref);

    if (destroy_ran)
        return 1;

    ptr_unref (ref);

    return destroy_ran ? 0 : 1;
}
