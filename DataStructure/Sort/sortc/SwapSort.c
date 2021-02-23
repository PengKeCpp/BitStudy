#include"common.h"
#include"Stack.h"

//冒泡排序
void BubbleSort(int *a,int n) {
	
	int end = n;
	while (end) {
		int exchage = 1;
		for (int i = 1; i < end; i++) {
			if (a[i - 1] > a[i]) {
				exchage = 0;
				swap(a + i - 1, a + i);
			}
		}
		if (exchage) break;
		end--;
	}
}

//三数取中，避免最坏情况
int getMinIndex(int *a,int begin,int end) {
	int mid = (begin + end) / 2;
	if (a[begin] < a[mid]) {
		if (a[mid]<a[end]) {
			return mid;
		}
		else if (a[begin] > a[end]) {
			return begin;
		}
		return end;
	}
	else {	//a[begin] >= a[mid]
		if (a[end] > a[begin]) {
			return begin;
		}
		else if (a[mid]>a[end]) {
			return mid;
		}
		else {
			return end;
		}
	}
}

//方法一: 左右指针法
int PartSort01(int *a,int begin,int end) {

	//实际中无法保证选key是中位数
	//那么我们是不是可以考虑到至少不要让最大或最小做key
	//三数取中保证不要选到最大或最小，让有序时变成最优
	int minIndex = getMinIndex(a,begin,end);
	swap(a+minIndex,a+end);
	int keyIndex = end;		//若选取最后一个数为key，那么要让begin先走。因为要找一个key大的，所以当循环到最后的时候，begin 先走就是找的比key大的下标
	while (begin < end) {   //若选取第一个数为key，那么要让end先走。因为要找一个key小的数，所以当循环到最后的时候，end 先走就是找的比key小的下标
		//一定要是a[keyIndex]>=a[begin]，a[end]>=a[begin]若是没有等于，当a[ketIndex]==a[begin]&&a[keyIndex]==a[end]的时候陷入死循环，begin和end一直没有变化
		while (begin < end && a[begin] <= a[keyIndex])begin++;
		while (begin < end && a[end] >= a[keyIndex]) end--;
		swap(a+begin,a+end);
	}
	swap(a+keyIndex,a+begin);
	return begin;
}

//方法二: 挖坑法
int PartSort02(int* a, int begin, int end) {
	//实际中无法保证选key是中位数
	//那么我们是不是可以考虑到至少不要让最大或最小做key
	//三数取中保证不要选到最大或最小，让有序时变成最优
	int minIndex = getMinIndex(a, begin, end);
	swap(a + minIndex, a + end);
	int key = a[end];
	//end是最开始的坑
	while (begin < end) {
		while (begin < end && a[begin] <= key)begin++;
		//左边找到比key大的坑，begin位置就形成了新的坑
		a[end] = a[begin];
		while (begin < end && a[end] >= key) end--;
		//右边找到比key小的坑，end就形成了新的坑
		a[begin] = a[end];
	}
	a[begin] = key;
	return begin;
}

//方法三:前后指针法
int PartSort03(int* a, int begin, int end) {
	int prev = begin - 1;
	int cur = begin;
	int keyIndex = end;
	while (cur < end) {
		if (a[cur] < a[keyIndex] && ++prev != cur) {
			swap(a+prev,a+cur);
		}
		++cur;
	}
	swap(&a[++prev],&a[keyIndex]);
	return prev;
}

//快速排序
void QuickSortRec(int* a, int left, int right) {
	assert(a);
	if (left < right) {
		int partion = PartSort03(a, left, right);
		QuickSortRec(a, left, partion - 1);
		QuickSortRec(a, partion + 1, right);
	}
}

//递归改非递归--1、该循环(斐波拉契数列求解) 一些简单递归才能改循环 2、栈模拟存储数据非递归
//非递归：1、提高效率（递归建立栈帧还是有消耗的，但是对于现代计算机，这个优化微乎其微可以忽略不计）
//	      2、递归最大缺陷是，如果栈帧的深度太深，可能会导致栈溢出。因为系统栈空间一般不大在M级别
//			数据结构模拟非递归，数据是存储在堆上的，堆是G级别的空间。

void QuickSortNRec(int* a, int left, int right) {
	Stack stk;
	StackInit(&stk);
	StackPush(&stk,right);
	StackPush(&stk, left);
	while (!StackEmpty(&stk)) {
		int begin=StackTop(&stk);
		StackPop(&stk);
		int end = StackTop(&stk);
		StackPop(&stk);
		int partition = PartSort02(a,begin,end);
		if (begin<partition-1) {
			StackPush(&stk, partition - 1);
			StackPush(&stk, begin);
		}
		if (partition+1 < end) {
			StackPush(&stk, end);
			StackPush(&stk, partition - 1);
		}
	}
	StackDestroy(&stk);
}

void testQS() {
	int a[] = { 10,26,62,2,1,26,98,-5,56,26 };
	printArray(a, sizeof(a) / sizeof(a[0]));
	QuickSortRec(a, 0, sizeof(a) / sizeof(a[0]) - 1);
	printArray(a, sizeof(a) / sizeof(a[0]));
}
void testBubbleSort() {
	int a[] = { 10,26,62,2,1,26,98,-5,56,26 };
	printArray(a, sizeof(a) / sizeof(a[0]));
	BubbleSort(a, sizeof(a) / sizeof(a[0]));
	printArray(a, sizeof(a) / sizeof(a[0]));
}
void testQuickSortNRec() {
	int a[] = { 10,26,62,2,1,26,98,-5,56,26 };
	printArray(a, sizeof(a) / sizeof(a[0]));
	QuickSortNRec(a, 0,sizeof(a) / sizeof(a[0])-1);
	printArray(a, sizeof(a) / sizeof(a[0]));
}

