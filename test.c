#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static struct header *memhead;

struct allocinfo {
  int free_size;
  int free_chunks;
  int largest_free_chunk_size;
  int smallest_free_chunk_size;
};

void main() {
    struct allocinfo *temp = malloc(sizeof(struct allocinfo));
    printf("%d", temp->free_size);
}