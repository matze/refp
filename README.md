# refp

Create reference counted pointers.


## Usage

In the simplest case, create a reference counted pointer by passing an existing
pointer and a destroy function to `ptr_new`:

```c
refp *ref = ptr_new (strdup ("foobar"), free);

/* access the actual pointer by ref->p */
printf ("Who are you? %s\n", (char *) ref->p);
```

Each receiver of a reference pointer must call `ptr_ref` before usage and
`ptr_unref` when not in use anymore:

```c
typedef struct {
    refp *foo;
} Data;

void
data_new (Data *data, refp *ref_string)
{
    data->foo = ptr_ref (ref_string);
}

void
data_free (Data *data)
{
    ptr_unref (data->foo);
}
```

For simple use cases, one can use the `ptr_alloc` convenience function which
allocates memory and uses `free` as the destroy function:

```c
refp *ref = ptr_alloc (4096);
```

To reduce the amount of casting boiler plate one can also use the `ptr_type`
macros for primitive data types:

```c
printf ("%s needs %f EUR\n", ptr_char (r1), *ptr_double (r2));
```
