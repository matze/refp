#include <stdlib.h>
#include <pthread.h>
#include "ref.h"


typedef struct {
    void *p;
    int count;
    RefPtrDestroyFunc func;
    pthread_mutex_t mutex;
} refp_real;


/**
 * Create a new reference pointer from `p`. If `func` is given, it is called
 * with `p` as an argument when the reference count reaches zero.
 */
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

/**
 * Create a new reference pointer and allocate memory with `size` bytes.
 */
refp *
ptr_alloc (size_t size)
{
    return ptr_new (malloc (size), free);
}

/**
 * Increase the reference counter.
 *
 * This function is thread-safe.
 */
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

/**
 * Decrease the reference counter. If it reaches zero, all associated resources
 * are freed and `func` is called when set.
 *
 * This function is thread-safe.
 */
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
