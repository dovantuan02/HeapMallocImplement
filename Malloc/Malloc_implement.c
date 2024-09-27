#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"

#include "config.h"

void push_back(uint8_t *matrix, size_t value) {
	
}

uint8_t ** allocateMatrix(size_t rows, size_t cols) {
	
}

uint8_t * allocatMatrixToArray(size_t row, size_t cols) {
	return (uint8_t*) pvPortCalloc(row * cols * sizeof(uint8_t));
}

int main() {
    size_t rows = 400;
    size_t cols = 4;

    uint8_t* vRcMotionVideo = allocatMatrixToArray(rows, cols);
    if (vRcMotionVideo == NULL) {
        return -1;
    }

    
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            vRcMotionVideo[i  * cols + j] = j;
        }
    }

	for (size_t a = 0; a < rows; a++) {
        for (size_t b = 0; b < cols; b++) {
			printf("%d\t", vRcMotionVideo[a * cols + b]);
		}
		printf("\n");
	}


	vPortFree(vRcMotionVideo);
	return 0;
}