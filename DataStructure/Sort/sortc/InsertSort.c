#include"common.h"

//直接插入排序

//思路：
//先排单趟，在整体考虑
//[0,end]区间有序
//把end+1的位置往[0,end]区间插入，保持有序
//性能：
//时间复杂度：O(N^2)
//空间复杂度：O(1)
//总结：当接近有序时，最好，接近逆序时，最坏。
void InsertSort(int *a,int n) {
	assert(a);
	for (int i = 0; i < n - 1; i++) {
		int end=i;
		int temp = a[end + 1];
		while (end >= 0) {
			if (temp < a[end]) {
				a[end + 1] = a[end];
				end--;
			}
			else break;
		}
		a[end + 1] = temp;
	}
}

//希尔排序
//思路：
//1.预排序
//2.直接插入排序
//gap越大，前面大的数据可以更快的到后面，后面小的数，可以更快的到前面。gap越大，越不接近有序，gap越小，越接近有序。如果gap=1,就是直接插入排序。

//性能：
//时间复杂度：Q(N^1.3-N^2)
void ShellSort(int *a,int n) {
	//	1.gap>1相当于预排序
	//  2.gap=1相当于直接插入排序
	int gap = n;
	while (gap>1) {
		gap = gap / 3 + 1;	//+1保证了最后一次一定要为1
		for (int i = 0; i < n - gap;i++) {
			int end = i;
			int temp = a[end + gap];
			while (end >= 0) {
				if (a[end] > temp) {
					a[end+gap] = a[end];
					end -= gap;
				}
				else break;
			}
			a[end + gap] = temp;
		}
	}
}

void testInsertSort() {
	int a[] = { 10,26,62,2,1,26,98,9,56,26 };
	printArray(a, sizeof(a) / sizeof(a[0]));
	InsertSort(a, sizeof(a) / sizeof(a[0]));
	printArray(a, sizeof(a) / sizeof(a[0]));
} 
void testShellShort() {
	int a[] = { 10,26,62,2,1,26,98,9,56,26 };
	printArray(a, sizeof(a) / sizeof(a[0]));
	ShellSort(a, sizeof(a) / sizeof(a[0]));
	printArray(a, sizeof(a) / sizeof(a[0]));
}
