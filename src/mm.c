#include <mm.h>
#include <printf.h>

void heap_init(struct heap_t *heap, void *head, unsigned int size)
{
    size = size & CHUNK_SIZE_MASK;
    heap->head = head;
    heap->tail = head + size;
    heap->inuse = 0; /* TODO: make use of `inuse' */
    chunk_t chunk = heap->head;
    *chunk = size;
/* Poor man's memset */
    unsigned char *p = head;
    while(size--) *p++ = 0;
}

static chunk_t next_free_chunk(chunk_t chunk)
{
    chunk_t next_chunk = CHUNK_NEXT(chunk);
    while (CHUNK_ALLOCATED_P(next_chunk)) next_chunk = CHUNK_NEXT(next_chunk);
    return chunk;
}

static chunk_t find_chunk(struct heap_t heap, unsigned int size)
{
    for (chunk_t chunk = heap.head;
         chunk < (chunk_t)heap.tail;
         chunk = next_free_chunk(chunk)) {
        if (CHUNK_SIZE(chunk) >= size) {
            return chunk;
        }
    }
    return NULL;
}

static void partition_chunk(chunk_t chunk, unsigned int size)
{
    int prev_size = *chunk;
    *chunk = size | O_CHUNK_ALLOCATED;
    chunk_t next_chunk = CHUNK_NEXT(chunk);
    *next_chunk = (prev_size - size) & CHUNK_SIZE_MASK;
}

void* __kalloc(struct heap_t heap, int size)
{
    chunk_t chunk = find_chunk(heap, size);
    if (chunk == NULL) return chunk;
    partition_chunk(chunk, size);    
    return chunk;
}

void free(void *mem)
{
    chunk_t chunk = mem;
    *chunk = *chunk | ~O_CHUNK_ALLOCATED;
    /* TODO: Add joining of consecutive chunks */
}

void print_heap_info(struct heap_t heap)
{
    unsigned int size = heap.tail - heap.head;
    kprintf("Heap at 0x%X, size: %d, inuse: %d\n",
            (unsigned int)heap.head, size, heap.inuse);
    int i = 1;
    for (chunk_t chunk = heap.head;
         chunk <= (unsigned int *)heap.tail;
         chunk = CHUNK_NEXT(chunk)) {
        kprintf("Chunk %d, start: 0x%X, size: %d, alloc: %s\n",
                i++,
                (unsigned int)chunk,
                CHUNK_SIZE(chunk),
                CHUNK_ALLOCATED_P(chunk) ? "true" : "false");
    }
}
