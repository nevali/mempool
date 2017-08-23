/* Resize a block of memory so that it is at least <newsize> bytes in size */
void *
mempool_realloc(void *ptr, size_t newsize)
{
	mempoolblock *block;
	mempool *pool;
	unsigned long ref;
	
	MEMPOOL_VALID_CHECK(ptr, block, pool, return NULL);
	/* This is a destructive operation, and will fail if the reference count
	 * on the block is greater than 1 - that is, if any other parts of this
	 * program are retaining a reference (and so holding a pointer) to this
	 * block which would be invalidated through a realloc() operation.
	 */
	MEMPOOL_REFCOUNT(block, ref);
	if(ref != 1)
	{
		return NULL;
	}
	newblock = (mempoolblock *) pool->methods->realloc(pool, newblock, 
		MEMPOOL_BLOCK_SIZE(newbytes));
	if(!newblock)
	{
		return NULL;
	}
	newblock->h.size = newsize;
	return &(block->d.bytes[MEMBLOCK_DATA_OFFSET)]
}
