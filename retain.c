/* Retain a block of memory - incrementing its reference count
 *
 * This should happen when a pointer is passed from one thread to another,
 * or an argument to a function is stored in a static local variable or a
 * global array or similar.
 */
unsigned long
mempool_retain(void *ptr)
{
	mempoolblock *block;
	mempool *pool;
	unsigned long ref;
	
	MEMPOOL_VALID_CHECK(ptr, block, pool, return 0);
	MEMPOOL_REFCOUNT_INC(block, ref);
	return ref;
}
