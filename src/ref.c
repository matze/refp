#include <stdlib.h>
#include <pthread.h>
#include "ref.h"


typedef struct {
    void *p;
    int count;
    RefPtrDestroyFunc func;
    pthread_mutex_t mutex;
} refp_real;


refp *
ptr_new (void *p, RefPtrDestroyFunc func)
{
    refp_real *real;

    real = malloc (sizeof (refp_real));
    real->p = p;
    real->count = 1;
    real->func = func;

    pthread_mutex_init (&real->mutex, NULL);

    return (refp *) real;
}

refp *
ptr_alloc (size_t size)
{
    return ptr_new (malloc (size), free);
}

refp *
ptr_ref (refp *ref)
{
    refp_real *real;

    if (ref == NULL) 
        return NULL;

    pthread_mutex_lock (&real->mutex);
    real = (refp_real *) ref;
    real->count++;
    pthread_mutex_unlock (&real->mutex);

    return ref;
}

refp *
ptr_unref (refp *ref)
{
    refp_real *real;

    if (ref == NULL) 
        return NULL;

    real = (refp_real *) ref;

    pthread_mutex_lock (&real->mutex);
    real->count--;

    if (real->count == 0) {
        if (real->func)
            real->func (real->p);

        free (ref);
        ref = NULL;
    }

    pthread_mutex_unlock (&real->mutex);
    return ref;
}
