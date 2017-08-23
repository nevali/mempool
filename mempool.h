#ifndef MEMPOOL_H_
# define MEMPOOL_H_                    1

# undef BEGIN_DECLS_
# undef END_DECLS_
# if defined(__cplusplus)
#  define BEGIN_DECLS_                 extern "C" {
#  define END_DECLS_                   }
# else
#  define BEGIN_DECLS_                 /* */
#  define END_DECLS_                   /* */
# endif

BEGIN_DECLS_;

/* Create a new pool */
mempool *mempool_create(void);
mempool *mempool_create_class(const uuid_t *class);

/* Destroy a pool */
int mempool_destroy(mempool *pool);

/* Obtain a pointer to the default pool */
mempool *mempool_default(void);

/* Begin and end an autorelease block */
int mempool_autorelease_begin(mempool *pool);
int mempool_autorelease_end(mempool *pool);

/* Allocate a block of memory */
void *mempool_alloc(mempool *pool, size_t nbytes);

/* Resize a block of memory */
int mempool_realloc(void *ptr);

/* Retain a block of memory */
int memppool_retain(void *ptr);

/* Release a block of memory */
int mempool_release(void *ptr);

/* Mark a block as being autoreleaseable */
int mempool_autorelease(void *ptr);

/* Obtain the size, in bytes, of a block */
size_t mempool_size(void *ptr);

/* Return the pool a block was allocated from */
mempool *mempool_pool(void *ptr);

/* Set the destructor for a block */
int mempool_set_dtor(void *ptr, void (*dtor)(void *ptr));

END_DECLS_;

#endif /*!MEMPOOL_H_*/