#define _CRT_SECURE_NO_WARNINGS
#include"common.h"
#include"Stack.h"


void MergeArr1(int *a,int begin1,int end1,int begin2,int end2,int *temp) {
	int index = begin1;
	int left = begin1, right = end2;
	while (begin1 <= end1 && begin2 <= end2) {
		if (a[begin1] < a[begin2])temp[index++] = a[begin1++];
		else temp[index++] = a[begin2++];
	}
	while(begin1<=end1)temp[index++] = a[begin1++];
	while(begin2<=end2)temp[index++] = a[begin2++];
	for (int i = left; i <= right; i++) a[i] = temp[i];
}

void _MergeSortRecu(int *a,int left,int right,int *temp) {
	if (left >= right) return;
	int mid = (left + right) >> 1;
	_MergeSortRecu(a,left,mid,temp);
	_MergeSortRecu(a,mid+1,right,temp);
	MergeArr1(a,left,mid,mid+1,right,temp);
}

void MergeSortRecu(int *a,int n) {
	int* temp = (int*)malloc(sizeof(int) * n);
	_MergeSortRecu(a, 0, n - 1, temp);
	free(temp);
}
void MergeSortNonR1(int* a,int n) {
	assert(a);
	int* temp = (int*)malloc(sizeof(int)*n);
	int gap = 1;
	while (gap < n) {
		for (int i = 0; i < n; i += 2 * gap) {
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2=i + 2 * gap - 1;
			if (begin2 >= n)break;
			if (end2 >= n)end2 = n - 1;
			MergeArr1(a,begin1,end1,begin2,end2,temp);
		}
		gap*=2;
	}
	free(temp);
}
int getMindIndex(int* a,int begin,int end) {
	int mid = (begin + end) >>1;
	if (a[begin] < a[mid]) {
		if (a[end] > a[mid])return mid;
		else if (a[begin] > a[end])return begin;
		else return end;
	}
	else {//a[begin] < a[mid]
		if (a[mid] < a[end])return mid;
		else if (a[begin] > a[end])return begin;
		else return end;
	}
}
//前后指针法
int _PartSort01(int *a,int begin,int end) {
	int midIndex = getMindIndex(a,begin,end);
	swap(a+end,a+midIndex);
	int keyIndex = end;
	while (begin<end) {
		while (begin < end && a[begin]<=a[keyIndex])begin++;
		while (begin < end && a[end]>=a[keyIndex])end--;
		swap(a+begin,a+end);
	}
	swap(a+begin,a+keyIndex);
	return begin;
}
//挖坑法
int _PartSort02(int* a, int begin, int end) {
	int midIndex = getMindIndex(a, begin, end);
	swap(a+end,a+midIndex);
	int key = a[end];
	while (begin < end) {
		while (begin < end && a[begin] <=key)begin++;
		a[end] = a[begin];
		while (begin < end && a[end] >= key)end--;
		a[begin] = a[end];
	}
	a[begin] = key;
}
//前后指针法
int _PartSort03(int* a, int begin, int end) {
	int cur = begin, prev = begin - 1;
	int key = a[end];
	while (cur < end) {
		if (a[cur] <=key && ++prev != cur) swap(a+prev,a+cur);
		++cur;
	}
	swap(&a[++prev], &a[cur]);
	return prev;
}
void InsertSort1(int* a, int n) {
	for (int i = 0; i < n - 1; i++) {
		int end = i;
		int temp = a[i+1];
		while (end>=0) {
			if (temp < a[end]) {
				a[end + 1] = a[end];
				end--;
			}
			else break;
		}
		a[end + 1] = temp;
	}
}

void ShellSort1(int* a, int n) {
	int gap = n;
	while (gap > 1) {
		gap = gap / 3 + 1;
		for (int i = 0; i < n - gap; i++) {
			int end = i;
			int temp = a[end+gap];
			while (end>=0) {
				if (temp < a[end]) {
					a[end + gap] = a[end];
					end -= gap;
				}
				else break;
			}
			a[end + gap] = temp;
		}
	}
}

void QuickSortNonR(int *a,int left,int right) {
	Stack stk;
	StackInit(&stk);
	StackPush(&stk,right);
	StackPush(&stk, left);
	while (!StackEmpty(&stk)) {
		int begin = StackTop(&stk);
		StackPop(&stk);
		int end = StackTop(&stk);
		StackPop(&stk);
		int partition = _PartSort03(a,begin,end);
		if (begin < partition-1) {
			StackPush(&stk, partition - 1);
			StackPush(&stk, begin);
		}
		if (partition + 1 < end) {
			StackPush(&stk, end);
			StackPush(&stk, partition + 1);
		}
	}
	StackDestroy(&stk);
}
void QuickSort(int *a,int left,int right) {
	if (right - left + 1 > 10) {
		int partition = _PartSort03(a, left, right);
		QuickSort(a, left, partition - 1);
		QuickSort(a, partition + 1, right);
	}
	else {
		InsertSort1(a+left,right-left+1);
	}
}

void testMergeSort1() {
	int a[] = {16,56,95,3,6,5,4,87,2,9,23,12,21,45,44,66,8,7};
	int length = sizeof(a) / sizeof(a[0]);
	printArray(a,length);
	MergeSortNonR1(a,length);
	printArray(a, length);
}

void testQuickSort() {
	int a[] = { 16,56,95,3,6,5,4,87,2,9,23,12,21,45,44,66,8,7 };
//	int a[] = {5,5,2,7,9,3,4,8,10,5};
	int length = sizeof(a) / sizeof(a[0]);
	printArray(a, length);
	QuickSort(a,0,length-1);
	printArray(a, length);
}

void MergeFile(const char*sin1,const char *sin2,const char*sout) {
	FILE* file1 = fopen(sin1,"r");
	if (file1 == NULL) {
		printf("file1打开文件失败！！\n");
		exit(-1);
	}
	FILE* file2 = fopen(sin2, "r");
	if (file2 == NULL) {
		printf("file2打开文件失败！！\n");
		exit(-1);
	}
	FILE* fout = fopen(sout,"w");
	if (fout == NULL) {
		printf("fout打开文件失败！！\n");
		exit(-1);
	}
	int num1, num2;
	int flag1 = fscanf(file1,"%d ",&num1);
	int flag2 = fscanf(file2, "%d ", &num2);
	while (flag1!=EOF&&flag2!= EOF) {
		if (num1 < num2) {
			fprintf(fout,"%d ",num1);
			flag1 = fscanf(file1, "%d ", &num1);
		}
		else {
			fprintf(fout, "%d ", num2);
			flag2 = fscanf(file2, "%d ", &num2);
		}
	}
	while (flag1 != EOF) {
		fprintf(fout, "%d ", num1);
		flag1 = fscanf(file1, "%d ", &num1);
	}
	while (flag2 != EOF) {
		fprintf(fout, "%d ", num2);
		flag2 = fscanf(file2, "%d ", &num2);
	}
	fclose(file1);
	fclose(file2);
	fclose(fout);
}
void MergeSortFile(const char* file, const int N, const int Nnum) {
	FILE* fout = fopen(file, "r");
	int* temp = (int*)malloc(sizeof(int) * Nnum);
	if (temp == NULL) {
		printf("内存不足、申请失败!!\n");
		exit(-1);
	}
	char subfile[20];
	int i = 0, filei = 1;
	int num;
	while (fscanf(fout, "%d ", &num) != EOF) {
		if (i < Nnum - 1) {
			temp[i++] = num;
		}
		else {
			temp[i] = num;
			QuickSortNonR(temp, 0, Nnum - 1);
			sprintf(subfile, "sub\\subsort%d", filei++);
			FILE* fin = fopen(subfile, "w");
			if (fin == NULL) {
				printf("打开文件失败！！！");
				exit(-1);
			}
			for (int j = 0; j < Nnum; j++) {
				fprintf(fin, "%d ", temp[j]);
			}
			fclose(fin);
			i = 0;
			printf("subsort%d已完成排序！！！！\n",filei-1);
		}
	}
	printf("小文件排序完成！！！！\n");
	const char prefixout[50] = "sub\\mergefile";
	const char prefixin[50] = "sub\\subsort";
	char fmout[50]="sub\\mergefile1";
	char fin1[50]="sub\\subsort1";
	char fin2[50]="sub\\subsort2";
	for (int i = 2; i <= N; i++) {
		MergeFile(fin1,fin2, fmout);
		printf("%s合并完毕\n", fmout);
		strcpy(fin1, fmout);
		strcpy(fmout, prefixout);
		strcpy(fin2, prefixin);
		sprintf(fmout,"%s%d%s",fmout,i);
		sprintf(fin2,"%s%d%s",fin2,i+1);
	}
	fclose(fout);
}

int main() {
	srand(time(0));
	char sfile[30] = "e:\\random.txt";	
	const int N=10,Nnum= 500000;
	FILE* file = fopen(sfile, "w");
	if (file == NULL) {
		printf("open error\n");
		exit(-1);
	}
	else {
		for (int i = 0; i < N; i++) {
			printf("%d\n", i);
			for (int j = 0; j < Nnum; j++) {
				fprintf(file, "%d ", rand());
				if(j!=0&&j%200==0)fprintf(file, "\n");
			}
		}
		fclose(file);
	}
	printf("生成随机数完成！！！！\n");
	printf("小文件开始分解排序！！！！\n");
	MergeSortFile(sfile,N,Nnum);
	printf("小文件合并完成！！！！\n");
	return 0;
}