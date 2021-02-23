#include "common.h"

//选择排序
void SelectSort(int *a,int n) {
	assert(a);
	int begin = 0, end = n - 1;
	while (begin<end) {
		int maxi = begin, mini = begin;
		for (int i = begin + 1; i <= end; i++) {
			if (a[i] > a[maxi]) maxi = i;
			if (a[i] < a[mini]) mini = i;
		}
		swap(a + mini, a + begin);
		//如果maxi和begin位置重叠，则maxi的位置需要修订，因为此时begin的值已经变成了mini的值
		if (begin == maxi)	maxi = mini;
		swap(a + maxi, a + end);
		begin++, end--;
	}
}

//堆排序
void down(int *a,int n,int root) {
	int child = root;
	if (root * 2 + 1 < n && a[2 * root + 1] > a[child]) child = 2 * root + 1;
	if (root * 2 + 2 < n && a[2 * root + 2] > a[child]) child = 2 * root + 2;
	if (root!=child) {
		swap(a+root,a+child);
		down(a,n,child);
	}
}

void down1(int *a,int n,int root) {
	int parent = root;
	int child = 2 * parent + 1;
	while (child<n) {
		if (child + 1 < n && a[child] < a[child + 1]) ++child;
		if (a[child] > a[parent]) {
			swap(a + child, a + parent);
			parent = child;
			child = 2 * parent + 1;
		}
		else break;
	}
}

void HeapSort(int *a,int n) {
	assert(a);
	for (int i = (n - 1 - 1) / 2; i >= 0; i--) {
		down1(a,n,i);
	}
	for (int i = n-1; i > 0; i--) {
		swap(a+i,a);
		down1(a,i,0);
	}
}

void testHeapSort() {
	int a[] = { 10,26,62,2,1,26,98,9,56,26 };
	printArray(a, sizeof(a) / sizeof(a[0]));
	HeapSort(a, sizeof(a) / sizeof(a[0]));
	printArray(a, sizeof(a) / sizeof(a[0]));
}
void testSelectSort() {
	int a[] = { 10,26,62,2,1,26,98,9,56,26 };
	printArray(a, sizeof(a) / sizeof(a[0]));
	SelectSort(a, sizeof(a) / sizeof(a[0]));
	printArray(a, sizeof(a) / sizeof(a[0]));
}
