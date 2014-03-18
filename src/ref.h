#ifndef REF_H
#define REF_H

#define ptr_char(x) ((char *) x->p)
#define ptr_int(x) ((int  *) x->p)
#define ptr_uint(x) ((unsigned int  *) x->p)
#define ptr_long(x) ((long  *) x->p)
#define ptr_ulong(x) ((unsigned long  *) x->p)
#define ptr_float(x) ((float  *) x->p)
#define ptr_double(x) ((double  *) x->p)


typedef void (*RefPtrDestroyFunc)(void *);

typedef struct {
    void *p;
} refp;


refp *ptr_new     (void *p, RefPtrDestroyFunc func);
refp *ptr_alloc   (size_t size);
refp *ptr_ref     (refp *ref);
refp *ptr_unref   (refp *ref);

#endif
