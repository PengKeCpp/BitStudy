#include "common.h"


void printArray(int* a, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}
void swap(int* n, int* m) {
	int temp = *n;
	*n = *m;
	*m = temp;
}
