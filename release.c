/* Release a block of memory */
unsigned long
mempool_release(void *ptr)
{
	mempoolblock *block;
	mempool *pool;
	unsigned long ref;
	
	MEMPOOL_VALID_CHECK(ptr, block, pool, return 0);
	MEMPOOL_REFCOUNT_DEC(block, ref);
	/* If the reference count is still positive, the block is being
	 * retained elsewhere and so won't be freed yet.
	 */
	if(ref)
	{
		return ref;
	}
	if(block->hdr.dtor)
	{
		/* If a destructor function pointer was provided for the block,
		 * invoke it.
		 */
		block->hdr.dtor(ptr);
	}
	pool->methods->free(pool, block);
	return 0;
}
