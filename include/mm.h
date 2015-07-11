#ifndef _MM_H
#define _MM_H

/*
 * This is a simple linked-list based memory allocator.
 * Memory is split into chunks with each allocation, and chunks are joined with
 * each free.
 *
 * This is not in any way thread safe, but we don't have threads yet, so we're
 * good.
 * TODO: Add thread safety
 */

/*
 * Our memory chunks:
 * +----------+-------------------+
 * | metadata | data ...          |
 * +----------+-------------------+
 *
 * Chunk metadata is a 32 bit integer, aligned to 30 bits. The integer
 * represents the chunk's size, the last bit is used to determine if the chunk
 * is allocated or not. The second to last bit is reserved for future use.
 *
 */

#define O_CHUNK_ALLOCATED 0x1
#define CHUNK_SIZE_MASK   0xFFFFFFFC
#define CHUNK_ALLOCATED_P(chunk) (*(chunk) & O_CHUNK_ALLOCATED)
#define CHUNK_SIZE(chunk) (*(chunk) & CHUNK_SIZE_MASK)
#define CHUNK_NEXT(chunk) ((chunk) + CHUNK_SIZE(chunk))

#define NULL ((void *)0)

typedef unsigned int * chunk_t;

struct heap_t {
    void *head;
    void *tail;
    int inuse;
};

/* Initialize a heap at a certain point in memory */
void heap_init(struct heap_t *heap, void *head, unsigned int size);
/* Allocate memory on a heap */
void* __kalloc(struct heap_t heap, int size);
/* Free an allocated chunk of memory */
void free(void *mem);

/* A debug function to print information about the heap */
void print_heap_info(struct heap_t heap);

#endif /* ! defined(_MM_H) */
