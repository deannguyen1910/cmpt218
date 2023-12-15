#include "alloc.h"
#include <assert.h>
#include<stdio.h>
static enum algs varAlgorithm = -1;
static int maxHeapSize = -1;
static int heapSize = -1;
static struct allocinfo heapinfo;
static struct header* memhead = NULL;
static void* startHeap;
static void* endHeap;
#define HEADER_SIZE (sizeof(struct header))

/**
    * @brief 
    * Return the pointer of the program break
    * @param size size of added array
    * @param tailPtr pointer of tail 
    * @return void* 
*/
void *increHeap(int size, void* tailPtr){
    //write(STDOUT_FILENO, "-----------------------\n", 24);
    struct header *temp = tailPtr;
    
    int sumSize = HEADER_SIZE + size;
    int incHeap = ((sumSize - 1) / INCREMENT + 1) * INCREMENT;

    if (heapSize + incHeap <= maxHeapSize){
        heapSize += incHeap;
        if (sbrk(incHeap) == NULL){
            return NULL;
        }else{
            heapinfo.free_size += incHeap;
            //write(STDOUT_FILENO, "incr\n", 5);
            return sbrk(0);
        }
    }else{
        return NULL;
    }

}

/** 
    * Return value 0 if it IS NOT tail
    * * Return value 1 if it IS tail
    * @param return int 
*/
int isTail(void* ptr){
    struct header *temp = ptr;
    if (temp->next != NULL){
        return 0;
    }else{
        return 1;
    }
}

/**
 * @brief 
 * Return value 0 if it DOESN'T NOT require increment Heap
 * Return value 1 if it DOES require increment Heap
 * @param return int
 */
int isRequireIncrHeap(int size, void *tailPtr){
    if (sbrk(0) - tailPtr >= size + HEADER_SIZE){
        return 0;
    }else{
        return 1;
    }
}

/*
Return value of pointer of the next available using first-fit algorithm.
*/
void *first_fit(int size){
    // 
    // start with mem head
    if ((char *)memhead - (char*)startHeap >= size + HEADER_SIZE){
        return startHeap;
    }
    struct header *tempNode = memhead;
    while (tempNode->next != NULL){
        if((char *)tempNode->next - ((char *)tempNode + tempNode->size) >= size + HEADER_SIZE){
            return tempNode;
        }
        tempNode = tempNode->next;
    }
    return tempNode;
}

void *worst_fit(int size){

}

void *best_fit(int size){

}

void *initializeSpace(struct header *mem, int size){
    if (mem == startHeap && memhead != startHeap){
        struct header* tempNode = (char *)startHeap;
        tempNode->size = size + HEADER_SIZE;
        tempNode->next = memhead;
        memhead = tempNode;
        heapinfo.free_size -= memhead->size;
        return (char*)memhead + HEADER_SIZE;
    }

    if (mem->next != NULL){
        struct header *tempNode = (char*)mem + mem->size;
        tempNode->size = size + HEADER_SIZE;
        tempNode->next = mem->next;
        mem->next = tempNode;
        heapinfo.free_size -= mem->size;
        return (char *)tempNode + HEADER_SIZE;
    }else{
        struct header *tempNode = (char*)mem + HEADER_SIZE + size;
        mem->size = size + HEADER_SIZE;
        mem->next = tempNode;
        heapinfo.free_size -= mem->size;
        return (char *)mem + HEADER_SIZE;
    }
}

void *alloc(int size) {
    void *ptr;

    //Initialize the memhead - case no heap
    if (memhead == NULL && size > 1) {
        ptr = sbrk(0);
        sbrk(INCREMENT);
        heapSize += INCREMENT;
        
        //Initialize the memhead
        memhead = ptr;
        memhead->size = -1;
        memhead->next = NULL;
        heapinfo.free_size -= HEADER_SIZE;
    }

    // choose hole - algorithms
    switch(varAlgorithm){
        case FIRST_FIT:
            ptr = first_fit(size);
            break;
        case WORST_FIT:
            break;
        case BEST_FIT:
            break;
        default:
            //write(STDOUT_FILENO, "wrong\n", 6);
            break;
    }
    
    if (isTail(ptr) == 1){
        if (isRequireIncrHeap(size, ptr) == 1){
            if (NULL == increHeap(size, ptr)){
                return NULL;
            }
        }
    }
    
    return initializeSpace(ptr, size);
}

void dealloc(void *ptr){
    if (ptr - HEADER_SIZE != memhead){
        struct header* tempNode = memhead;
        while (tempNode->next != NULL){
            if (tempNode->next == ptr - HEADER_SIZE){
                heapinfo.free_size -= tempNode->next->size;
                tempNode->next->size = 0;
                tempNode->next = tempNode->next->next;
                break;
            }
            tempNode = tempNode->next;
        }
    }
    else{ 
        heapinfo.free_size += memhead->size;
        memhead->size = 0;
        memhead = memhead->next;
    }
}

struct allocinfo allocinfo(void){
    return heapinfo;
}

void allocopt(enum algs algorithm, int maxSize){
    //reset 
    varAlgorithm = -1;
    maxHeapSize = -1;
    heapSize = -1;
    heapinfo.free_chunks = -1;
    heapinfo.free_size = -1;
    heapinfo.largest_free_chunk_size = -1;
    heapinfo.smallest_free_chunk_size = -1;
    memhead = NULL;
    brk(startHeap);
    startHeap = NULL;
    ///////////


    varAlgorithm = algorithm;
    maxHeapSize = maxSize;
    endHeap = sbrk(0);
    startHeap = 
    heapinfo.free_size = maxSize;
}