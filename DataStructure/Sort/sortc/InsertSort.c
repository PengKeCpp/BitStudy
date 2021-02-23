#include"common.h"

//ֱ�Ӳ�������

//˼·��
//���ŵ��ˣ������忼��
//[0,end]��������
//��end+1��λ����[0,end]������룬��������
//���ܣ�
//ʱ�临�Ӷȣ�O(N^2)
//�ռ临�Ӷȣ�O(1)
//�ܽ᣺���ӽ�����ʱ����ã��ӽ�����ʱ�����
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

//ϣ������
//˼·��
//1.Ԥ����
//2.ֱ�Ӳ�������
//gapԽ��ǰ�������ݿ��Ը���ĵ����棬����С���������Ը���ĵ�ǰ�档gapԽ��Խ���ӽ�����gapԽС��Խ�ӽ��������gap=1,����ֱ�Ӳ�������

//���ܣ�
//ʱ�临�Ӷȣ�Q(N^1.3-N^2)
void ShellSort(int *a,int n) {
	//	1.gap>1�൱��Ԥ����
	//  2.gap=1�൱��ֱ�Ӳ�������
	int gap = n;
	while (gap>1) {
		gap = gap / 3 + 1;	//+1��֤�����һ��һ��ҪΪ1
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
