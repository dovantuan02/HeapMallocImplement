#include "bits/stdc++.h"
#include "stdint.h"
#include "heap_4.h"
#include "vector_impl.hpp"
void allocateMemoryWithHeap4();

struct Malloc_implement
{
	uint8_t **pBuffer;
	uint32_t *pSize;
	size_t totalRows;
	size_t idxRowNow = 0;
	void mallocRows(size_t rows) {
		pBuffer = (uint8_t**) pvPortMalloc(rows * sizeof(uint8_t*));
		pSize = (uint32_t*) pvPortMalloc(rows * sizeof(uint32_t));
		totalRows = rows;
	}

	void insertDataToRow(uint8_t *buff, uint32_t length) {
		pBuffer[idxRowNow] = (uint8_t*) pvPortMalloc(length * sizeof(uint8_t));
		memcpy(pBuffer[idxRowNow], buff, length);
		pSize[idxRowNow] = length;
		idxRowNow++;
	}

	size_t getTotalRows() {
		return totalRows;
	}

	size_t size() {
		return idxRowNow;
	}

	uint8_t at(size_t idxRow, size_t idxCol) {
		return pBuffer[idxRow][idxCol];
	}

	/* get buffer at index*/
	uint8_t* at(size_t i) {
		return pBuffer[i];
	}

	void free_all() {
		for (size_t i = 0; i < totalRows; i++) {
			vPortFree((void**) & pBuffer[i]) ;
		}
		vPortFree( (void**) &pBuffer );
	}

	void erase(size_t start, size_t end)
	{
		if (start >= idxRowNow || end >= idxRowNow || start > end)
		{
			printf("Invalid range\n");
			return;
		}
		for (size_t i = start; i <= end; i++)
		{
			if (pBuffer[i] != nullptr)
			{
				vPortFree( (void**) & pBuffer[i]);
				pBuffer[i] = nullptr;
				pSize[i] = 0;
			}
		}

		size_t shiftAmount = end - start + 1;
		for (size_t i = end + 1; i < idxRowNow; i++)
		{
			if (pBuffer[i - shiftAmount] != nullptr)
			{
				vPortFree( (void**) & pBuffer[i - shiftAmount]);
				pSize[i - shiftAmount] = 0;
			}

			pBuffer[i - shiftAmount] = (uint8_t*) pvPortMalloc(pSize[i] * sizeof(uint8_t));

			if (pBuffer[i - shiftAmount] != nullptr)
			{
				memcpy(pBuffer[i - shiftAmount], pBuffer[i], pSize[i]);
				pSize[i - shiftAmount] = pSize[i];
			}
			vPortFree( (void**) & pBuffer[i]);
			pSize[i] = 0;
		}

		idxRowNow -= shiftAmount;
		for (size_t i = idxRowNow; i < idxRowNow + shiftAmount; i++)
		{
			pBuffer[i] = nullptr;
			pSize[i] = 0;
		}

		printf("Elements erased from index %ld to %ld\n", start, end);
	}
};



int main() {
	Malloc_implement pMan;

	pMan.mallocRows(455);
	
	uint8_t buff1[66000] = {0};
	uint8_t buff2[7000] = {10};

	size_t nBuff1 = sizeof(buff1) / sizeof(buff1[0]);
	size_t nBuff2 = sizeof(buff2) / sizeof(buff2[0]);

	size_t totalBytes = 0;

	for (size_t idx = 0; idx < 35; idx++) {
		pMan.insertDataToRow(buff1, nBuff1);
		totalBytes += nBuff1;
		printf("free heap size 1: %ld bytes\n", xPortGetFreeHeapSize());
		for (size_t i = 1; i < 13; i++) {
			pMan.insertDataToRow(buff2, nBuff2);
			totalBytes += nBuff2;
		}
	}
	printf("Total Rows Nows: %ld\n", pMan.getTotalRows());
	printf("Index Rows Nows: %ld\n", pMan.size());
	pMan.erase(0, 454);
	printf("free heap size 2: %ld bytes\n", xPortGetFreeHeapSize());

	for (size_t idx = 0; idx < 35; idx++) {
		pMan.insertDataToRow(buff1, nBuff1);
		totalBytes += nBuff1;
		printf("free heap size 1: %ld bytes\n", xPortGetFreeHeapSize());
		for (size_t i = 1; i < 13; i++) {
			pMan.insertDataToRow(buff2, nBuff2);
			totalBytes += nBuff2;
		}
	}
	printf("Total Rows Nows: %ld\n", pMan.getTotalRows());
	printf("Index Rows Nows: %ld\n", pMan.size());
	pMan.erase(0, 454);
	printf("free heap size 2: %ld bytes\n", xPortGetFreeHeapSize());

	for (size_t idx = 0; idx < 35; idx++) {
		pMan.insertDataToRow(buff1, nBuff1);
		totalBytes += nBuff1;
		printf("free heap size 1: %ld bytes\n", xPortGetFreeHeapSize());
		for (size_t i = 1; i < 13; i++) {
			pMan.insertDataToRow(buff2, nBuff2);
			totalBytes += nBuff2;
		}
	}
	printf("Total Rows Nows: %ld\n", pMan.getTotalRows());
	printf("Index Rows Nows: %ld\n", pMan.size());
	pMan.erase(0, 454);
	printf("free heap size 2: %ld bytes\n", xPortGetFreeHeapSize());

	for (size_t idx = 0; idx < 35; idx++) {
		pMan.insertDataToRow(buff1, nBuff1);
		totalBytes += nBuff1;
		printf("free heap size 1: %ld bytes\n", xPortGetFreeHeapSize());
		for (size_t i = 1; i < 13; i++) {
			pMan.insertDataToRow(buff2, nBuff2);
			totalBytes += nBuff2;
		}
	}
	printf("Total Rows Nows: %ld\n", pMan.getTotalRows());
	printf("Index Rows Nows: %ld\n", pMan.size());
	pMan.erase(0, 454);
	printf("free heap size 2: %ld bytes\n", xPortGetFreeHeapSize());

	printf("Byte used: %ld\n", totalBytes);
	return 0;
}
