#include "bits/stdc++.h"
#include "stdint.h"
#include "heap_4.h"
#include "vector_impl.hpp"
void allocateMemoryWithHeap4();

int main() {
#if 0
	Vector< Vector<uint8_t> >vec;
	// uint8_t bytes[] = {10, 20, 30, 40, 50, 100, 11, 12, 33, 22, 33, 98, 100, 22, 12, 12, 12,3 ,123, 12, 11, 2};
	uint8_t bytes[256] = {0};
	size_t nBytes = sizeof(bytes) / sizeof(bytes[0]);
	memset(bytes, 10, nBytes);
	printf("%d\n", bytes[100]);

	printf("Free Heap Size: %d\n", xPortGetFreeHeapSize() );
	for( int i = 0; i < 10; i++) {
		printf("%d\t", i);
		vec.push_back(Vector<uint8_t>(bytes, bytes + nBytes));
	}
	printf("Free Heap Size: %d\n", xPortGetFreeHeapSize() );

	for( int i = 0; i < 10; i++) {
		printf("%d\t", i);
		vec.push_back(Vector<uint8_t>(bytes, bytes + nBytes));
	}
	printf("Free Heap Size: %d\n", xPortGetFreeHeapSize() );

	for( int i = 0; i < 10; i++) {
		printf("%d\t", i);
		vec.push_back(Vector<uint8_t>(bytes, bytes + nBytes));
	}
	printf("Free Heap Size: %d\n", xPortGetFreeHeapSize() );
	

	for( int i = 0; i < 10; i++) {
		printf("%d\t", i);
		vec.push_back(Vector<uint8_t>(bytes, bytes + nBytes));
	}
	printf("Free Heap Size: %d\n", xPortGetFreeHeapSize() );

	for( int i = 0; i < 10; i++) {
		printf("%d\t", i);
		vec.push_back(Vector<uint8_t>(bytes, bytes + nBytes));
	}
	printf("Free Heap Size: %d\n", xPortGetFreeHeapSize() );

	for( int i = 0; i < 10; i++) {
		vec.push_back(Vector<uint8_t>(bytes, bytes + nBytes));
	}
	printf("Free Heap Size: %d\n", xPortGetFreeHeapSize() );

	// vec.print(); // In ra: 10 20 30 40

	printf("Before Capacity: %d\n", vec.capacity());
	printf("Before Size: %d\n", vec.size());

	// std::cout << vec.begin() << " " << vec.end() << std::endl;
	printf("%d - %d\n", vec.begin(), vec.end());

	for (size_t i = 0; i < vec.size(); i++) {
		vec[i].clear();
		vec[i].shrink_to_fit();
	}

	vec.erase(vec.begin(), vec.end());
	// vec.pop_back();
	// vec.print(); // In ra: 10 20 30

	vec.shrink_to_fit();
	printf("After Capacity: %d\n", vec.capacity());
	printf("After Size: %d\n", vec.size());

	printf("Free Heap Size: %d\n", xPortGetFreeHeapSize() );
#else 
	// allocateMemoryWithHeap4();

	uint8_t *ptr = NULL;
	uint8_t *pBlock[13] = {NULL};
	pBlock[0] = (uint8_t*) pvPortMalloc(56074 * sizeof(uint8_t));
	for (int i = 1; i < 13; i++) {
		pBlock[i] = (uint8_t*) pvPortMalloc(7000 * sizeof(uint8_t));
	}
	// uint8_t *pBlock1 = (uint8_t*) pvPortMalloc(3923 * sizeof(uint8_t));
	// uint8_t *pBlock2 = (uint8_t*) pvPortMalloc(3997 * sizeof(uint8_t));
	// uint8_t *pBlock3 = (uint8_t*) pvPortMalloc(3587 * sizeof(uint8_t));
	// uint8_t *pBlock4 = (uint8_t*) pvPortMalloc(3587 * sizeof(uint8_t));
	// uint8_t *pBlock5 = (uint8_t*) pvPortMalloc(3587 * sizeof(uint8_t));
	// uint8_t *pBlock6 = (uint8_t*) pvPortMalloc(3587 * sizeof(uint8_t));
	// uint8_t *pBlock7 = (uint8_t*) pvPortMalloc(3923 * sizeof(uint8_t));
	// uint8_t *pBlock8 = (uint8_t*) pvPortMalloc(3923 * sizeof(uint8_t));
	// uint8_t *pBlock9 = (uint8_t*) pvPortMalloc(3997 * sizeof(uint8_t));
	// uint8_t *pBlock10 = (uint8_t*) pvPortMalloc(3587 * sizeof(uint8_t));
	// uint8_t *pBlock11 = (uint8_t*) pvPortMalloc(3587 * sizeof(uint8_t));
	// uint8_t *pBlock12 = (uint8_t*) pvPortMalloc(3587 * sizeof(uint8_t));
	// memset(pBlock, 10, 100);
	for (int i = 0; i < 100; i++) {
		pBlock[0][i] = i;
	}
	ptr = &pBlock[0][0];

	printf("%d\n", ptr[56]);
	printf("free heap size: %d bytes\n", xPortGetFreeHeapSize());
	vPortFree((void**) &pBlock);
	printf("free heap size: %d bytes\n", xPortGetFreeHeapSize());
#endif
	return 0;
}


void* pvAllocatedBlocks[10];

void allocateMemoryWithHeap4() {
    // Inital heap status
    printf("Initial free heap size: %d bytes\n", xPortGetFreeHeapSize());

    // Step 1: Allocate 5 blocks of 2KB each (Total 10KB)
    for (int i = 0; i < 5; i++) {
        pvAllocatedBlocks[i] = pvPortMalloc(2048);  // Allocate 2KB per block
        if (pvAllocatedBlocks[i] == NULL) {
            printf("Allocation failed for block %d\n", i);
        }
    }
    printf("Free heap size after 10KB allocation: %d bytes\n", xPortGetFreeHeapSize());

    // Step 2: Free 2 blocks of 2KB each (4KB freed)
    vPortFree(&pvAllocatedBlocks[1]);  // Free block 1 (2KB)
	// pvAllocatedBlocks[1] = NULL;
    vPortFree(&pvAllocatedBlocks[3]);  // Free block 3 (2KB)
	// pvAllocatedBlocks[3] = NULL;
    printf("Free heap size after freeing 4KB: %d bytes\n", xPortGetFreeHeapSize());

    // Step 3: Try to allocate a large block of 50KB
    void* largeBlock = pvPortMalloc(51200);  // Try to allocate 50KB
    if (largeBlock == NULL) {
        printf("Failed to allocate 50KB.\n");
    } else {
        printf("Successfully allocated 50KB.\n");
    }
    printf("Free heap size after 50KB allocation attempt: %d bytes\n", xPortGetFreeHeapSize());

    // Clean up: Free remaining memory
    for (int i = 0; i < 5; i++) {
		printf("Block :%d\n", i);
        if (pvAllocatedBlocks[i] != NULL) {
            vPortFree(&pvAllocatedBlocks[i]);
        }
    }
    if (largeBlock != NULL) {
        vPortFree(&largeBlock);
    }
    printf("Free heap size after cleanup: %d bytes\n", xPortGetFreeHeapSize());
}