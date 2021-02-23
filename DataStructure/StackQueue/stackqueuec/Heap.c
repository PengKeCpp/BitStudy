#include"Heap.h"

void swap1(HPDataType* p, HPDataType* q) {
	HPDataType temp = *p;
	*p = *q;
	*q = temp;
}

//向下调整算法
void down(HPDataType* heap, int n, int root) {
	assert(heap);
	int child = root;
	if (2 * root + 1 < n && heap[child] > heap[2 * root + 1])child = 2 * root + 1;
	if (2 * root + 2 < n && heap[child] > heap[2 * root + 2])child = 2 * root + 2;
	if (child != root) {
		swap1(heap + root, heap + child);
		down(heap,n,child);
	}
}
void up(HPDataType* heap, int child) {
	while ((child - 1) / 2 >= 0 && heap[child] < heap[(child - 1) / 2]) {
		swap1(heap + child, heap + (child - 1) / 2);
		child = (child - 1) / 2;
	}
}
// 堆的构建
void HeapCreate(Heap* hp, HPDataType* a, int n) {
	assert(hp);
	hp->_a = (HPDataType*)malloc(sizeof(int)*n);
	memcpy(hp->_a,a,sizeof(int)*n);
	hp->_size = n;
	hp->_capacity = n;
	for (int i = (n - 1 - 1) / 2; i >= 0; i--) {
		down(hp->_a,n,i);
	}
}


// 堆的销毁
void HeapDestory(Heap* hp) {
	assert(hp);
	free(hp->_a);
	hp->_capacity = hp->_size = 0;
}

// 堆的插入
void HeapPush(Heap* hp, HPDataType x) {
	assert(hp&&hp->_a);
	if (hp->_capacity == hp->_size) {
		hp->_capacity *= 2;
		 HPDataType* temp= (HPDataType*)realloc(hp->_a, sizeof(HPDataType)*hp->_capacity);
		 if (temp != NULL) {
			 hp->_a = temp;
		 }
		 else {
			 printf("内存不足\n");
			 exit(-1);
		 }
	}
	hp->_a[hp->_size] = x;
	up(hp->_a,hp->_size);	
	++hp->_size;
}
// 堆的删除
void HeapPop(Heap* hp) {
	assert(hp);
	hp->_size -= 1;
	swap1(&hp->_a[0],&hp->_a[hp->_size]);
	down(hp->_a,hp->_size,0);
}
// 取堆顶的数据
HPDataType HeapTop(Heap* hp) {
	assert(hp);
	return hp->_a[0];
}
// 堆的数据个数
int HeapSize(Heap* hp) {
	assert(hp);
	return hp->_size;
}
// 堆的判空
int HeapEmpty(Heap* hp) {
	assert(hp);
	return !hp->_size;
}

// 对数组进行堆排序，从大到小排序
void HeapSort1(int* a, int n) {
	//先从最后一个非叶子节点开始建堆
	for (int i = (n - 1 - 1) / 2; i >= 0;i--) {
		down(a, n, i);
	}
	for (int i = n - 1; i >= 0; i--) {
		//将第一个元素于剩余数组得最后一个元素减一
		swap1(&a[i],&a[0]);
		//执行down操作，数组大小减一
		down(a,i,0);
	}
}


// TopK问题：找出N个数里面最大/最小的前K个问题。
// 比如：未央区排名前10的泡馍，西安交通大学王者荣耀排名前10的韩信，全国排名前10的李白。等等问题都是Topk问题，
// 需要注意：
// 找最大的前K个，建立K个数的小堆
// 找最小的前K个，建立K个数的大堆
void PrintTopK(int* a, int n, int k) {
	//找最大得前K个，建立K个数得小堆，时间复杂度为 logK
	Heap hp;
	HeapCreate(&hp, a, k);
	
	for (size_t i = k; i < n; ++i)  // N
	{
		//每次和堆顶元素比较，大于堆顶元素，则删除堆顶元素，插入新的元素
		if (a[i] > HeapTop(&hp)) // LogK
		{
			HeapPop(&hp);
			HeapPush(&hp, a[i]);
		}
	}
	printf("排序后的前10大数：");
	for (int i = 0; i < k; ++i) {
		printf("%d ", HeapTop(&hp));
		HeapPop(&hp);
	}
}

void TestTopk() {

	int n = 100000;
	int* a = (int*)malloc(sizeof(int) * n);
	if (a == NULL) {
		exit(-1);
	}
	srand(time(0));
	//随机生成10000个数存入数组，保证元素都小于1000000
	for (size_t i = 0; i < n; ++i) {
		a[i] = rand() % 1000000;
	}
	//确定10个最大的数
	a[5] = 1000000 + 1;
	a[1231] = 1000000 + 2;
	a[531] = 1000000 + 3;
	a[5121] = 1000000 + 4;
	a[115] = 1000000 + 5;
	a[2335] = 1000000 + 6;
	a[9999] = 1000000 + 7;
	a[76] = 1000000 + 8;
	a[423] = 1000000 + 9;
	a[3144] = 1000000 + 10;
	PrintTopK(a, n, 10);
}

