/* Memory pools are instances of one or more classes.
 *
 * Memory pool classes factories can be registered.
 *
 * The class is responsible for allocating and freeing the memory for a pool
 * itself, and providing implementations of operations which can be performed
 * upon it. The class factory must allocate a pool, initialise it (ensuring
 * it includes the pointer to the class's method table), and the pointer to it.
 *
 * Different classes may have different characteristics: for example, way that
 * allocations are grouped together or distributed. One pool might be optimised
 * for multi-gigabyte allocations, whilst another for string manipulation.
 *
 * The first pool class listed in the array below is used to create the
 * initial default pool, which is never destroyed, and is used for any internal
 * allocations.
 *
 * If this library is built with no pool implementations provided, it is up
 * to the application to provide one otherwise all allocations will fail.
 */

static mempoolreg registry[] =
{
	{ UUID_NULL, NULL }
};

/* Create a new pool */
mempool *
mempool_create(void)
{
	if(!registry[0].factory)
	{
		return NULL;
	}
	return registry[0].factory();
}

mempool *
mempool_create_class(const uuid_t classid)
{
	for(c = 0; registry[c].factory; c++)
	{
		if(!memcmp(classid, registry[c].classid, sizeof(uuid_t)))
		{
			return registry[c].factory();
		}
	}
	return NULL;
}

/* Destroy a pool */
int
mempool_destroy(mempool *pool)
{
	return pool->methods->release(pool);
}

/* Obtain a pointer to the default pool */
mempool *
mempool_default(void)
{
}

/* Begin and end an autorelease block */
int mempool_autorelease_begin(mempool *pool);
int mempool_autorelease_end(mempool *pool);


/* Mark a block as being autoreleaseable */
int
mempool_autorelease(void *ptr)
{
	mempoolblock *block;
	mempool *pool;
	
	MEMPOOL_VALID_CHECK(ptr, block, pool, return -1);
}


/* Return the pool a block was allocated from */
mempool *mempool_pool(void *ptr);

/* Set the destructor for a block */
int mempool_set_dtor(void *ptr, void (*dtor)(void *ptr));
