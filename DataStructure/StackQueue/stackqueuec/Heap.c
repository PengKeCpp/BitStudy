#include"Heap.h"

void swap1(HPDataType* p, HPDataType* q) {
	HPDataType temp = *p;
	*p = *q;
	*q = temp;
}

//���µ����㷨
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
// �ѵĹ���
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


// �ѵ�����
void HeapDestory(Heap* hp) {
	assert(hp);
	free(hp->_a);
	hp->_capacity = hp->_size = 0;
}

// �ѵĲ���
void HeapPush(Heap* hp, HPDataType x) {
	assert(hp&&hp->_a);
	if (hp->_capacity == hp->_size) {
		hp->_capacity *= 2;
		 HPDataType* temp= (HPDataType*)realloc(hp->_a, sizeof(HPDataType)*hp->_capacity);
		 if (temp != NULL) {
			 hp->_a = temp;
		 }
		 else {
			 printf("�ڴ治��\n");
			 exit(-1);
		 }
	}
	hp->_a[hp->_size] = x;
	up(hp->_a,hp->_size);	
	++hp->_size;
}
// �ѵ�ɾ��
void HeapPop(Heap* hp) {
	assert(hp);
	hp->_size -= 1;
	swap1(&hp->_a[0],&hp->_a[hp->_size]);
	down(hp->_a,hp->_size,0);
}
// ȡ�Ѷ�������
HPDataType HeapTop(Heap* hp) {
	assert(hp);
	return hp->_a[0];
}
// �ѵ����ݸ���
int HeapSize(Heap* hp) {
	assert(hp);
	return hp->_size;
}
// �ѵ��п�
int HeapEmpty(Heap* hp) {
	assert(hp);
	return !hp->_size;
}

// ��������ж����򣬴Ӵ�С����
void HeapSort1(int* a, int n) {
	//�ȴ����һ����Ҷ�ӽڵ㿪ʼ����
	for (int i = (n - 1 - 1) / 2; i >= 0;i--) {
		down(a, n, i);
	}
	for (int i = n - 1; i >= 0; i--) {
		//����һ��Ԫ����ʣ����������һ��Ԫ�ؼ�һ
		swap1(&a[i],&a[0]);
		//ִ��down�����������С��һ
		down(a,i,0);
	}
}


// TopK���⣺�ҳ�N�����������/��С��ǰK�����⡣
// ���磺δ��������ǰ10�����ɣ�������ͨ��ѧ������ҫ����ǰ10�ĺ��ţ�ȫ������ǰ10����ס��ȵ����ⶼ��Topk���⣬
// ��Ҫע�⣺
// ������ǰK��������K������С��
// ����С��ǰK��������K�����Ĵ��
void PrintTopK(int* a, int n, int k) {
	//������ǰK��������K������С�ѣ�ʱ�临�Ӷ�Ϊ logK
	Heap hp;
	HeapCreate(&hp, a, k);
	
	for (size_t i = k; i < n; ++i)  // N
	{
		//ÿ�κͶѶ�Ԫ�رȽϣ����ڶѶ�Ԫ�أ���ɾ���Ѷ�Ԫ�أ������µ�Ԫ��
		if (a[i] > HeapTop(&hp)) // LogK
		{
			HeapPop(&hp);
			HeapPush(&hp, a[i]);
		}
	}
	printf("������ǰ10������");
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
	//�������10000�����������飬��֤Ԫ�ض�С��1000000
	for (size_t i = 0; i < n; ++i) {
		a[i] = rand() % 1000000;
	}
	//ȷ��10��������
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

