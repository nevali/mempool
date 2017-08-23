/* Obtain the size, in bytes, of a previously-allocated block */
size_t mempool_size(void *ptr)
{
	mempoolblock *block;
	mempool *pool;
	unsigned long ref;
	size_t size;
	
	MEMPOOL_VALID_CHECK(ptr, block, pool, return 0);
	return block->hdr.size;
}