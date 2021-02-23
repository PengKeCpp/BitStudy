#include"common.h"


void MergeArr(int* a, int begin1, int end1, int begin2, int end2, int *temp) {
	int index = begin1;
	int left = begin1, right = end2;
	while (begin1 <= end1 && begin2 <= end2) {
		if (a[begin1] < a[begin2]) temp[index++] = a[begin1++];
		else temp[index++] = a[begin2++];
	}
	while(begin1<=end1)temp[index++] = a[begin1++];
	while(begin2<=end2)temp[index++] = a[begin2++];
	for (int i = left; i <= right;++i) a[i] = temp[i];
}
void _MergeSort(int *a,int left,int right,int *temp) {
	if (left >= right) return;
	int mid = (left + right) >> 1;
	_MergeSort(a,left,mid,temp);
	_MergeSort(a,mid+1,right,temp);
	MergeArr(a,left,mid,mid+1,right,temp);
}

//¹é²¢µÝ¹é
void MergeSort(int *a,int n) {
	assert(a);
	int* temp = (int*)malloc(sizeof(int)*n); 
	_MergeSort(a,0,n-1,temp);
	free(temp);
}
//¹é²¢·ÇµÝ¹é
void MergeSortNonR(int* a, int n) {
	assert(a);
	int* temp = (int*)malloc(sizeof(int)*n);
	int gap = 1;
	while (gap < n) {
		for (int i = 0; i < n; i += 2 * gap) {
			int begin1=i, end1 =i+gap-1;
			int begin2=i+gap, end2 =i+2*gap-1;
			if (begin2 >= n) break;
			if (end2 >= n) end2 = n - 1;
			MergeArr(a,begin1,end1,begin2,end2,temp);
		}
		gap *= 2;
	}
	free(temp);
}


void testMergeSort() {
	int a[] = { 10,26,62,2,1,26,98,-5,56,26 };
	printArray(a, sizeof(a) / sizeof(a[0]));
	MergeSortNonR(a, sizeof(a) / sizeof(a[0]));
	printArray(a, sizeof(a) / sizeof(a[0]));
}

