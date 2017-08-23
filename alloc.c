/* Allocate a block of memory <nbytes> in size. If <pool> is NULL, the default
 * pool will be used instead.
 *
 * The MEMPOOL_BLOCK_SIZE() macro adds the size of our header to the requested
 * size, ensuring the user pointer returned is properly aligned.
 *
 * The MEMBLOCK_DATA_OFFSET macro expands to the offset of the first byte
 * of user data within the allocated block.
 */
void *
mempool_alloc(mempool *pool, size_t nbytes)
{
	mempoolblock *block;
	
	if(!pool)
	{
		pool = mempool_default();
		if(!pool)
		{
			return NULL;
		}
	}
	block = (mempoolblock *) pool->methods->alloc(pool, MEMPOOL_BLOCK_SIZE(nbytes));
	if(!block)
	{
		return NULL;
	}
	block->h.magic = MEMPOOL_MAGIC;
	block->h.pool = pool;
	block->h.refcount = 1;
	block->h.size = nbytes;
	return &(block->d.bytes[MEMBLOCK_DATA_OFFSET)]
}
