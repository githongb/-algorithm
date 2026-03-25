#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning (disable:4996)
int heap[100], k = 0;

void swap(int a, int b) {
	int c = heap[a];
	heap[a] = heap[b];
	heap[b] = c;
}
void upheap(int* heap, int i) {
	if (i == 1) {
		return;
	}
	if (heap[i] > heap[i / 2]) {
		swap(i, i / 2);
		upheap(heap, i / 2);
	}
}
void downheap(int* heap, int i) {
	if (k < i * 2) {	// 자식이 존재X
		return;
	}
	int max = i * 2;
	if (k >= i * 2 + 1 && heap[i*2] < heap[i*2+1]) {
		max = i * 2 + 1;
	}
	if (heap[max] > heap[i]) {
		swap(max, i);
		downheap(heap, max);
	}
}
void insertitem(int* heap, int key) {
	heap[++k] = key;
	upheap(heap, k);
	printf("0\n");
}
int removemax(int* heap) {
	swap(1, k);
	k--;
	downheap(heap, 1);
	return heap[k + 1];
}
void printheap(int* heap) {
	for (int i = 1; i <= k; i++) {
		printf(" %d", *(heap + i));
	}
	printf("\n");
}

void rbuildheap1(int i) {
	if (i > k) return;
	rbuildheap(i * 2);
	rbuildheap(i * 2 + 1);
	downheap(heap, i);
}
void rbuildheap2(int i) {
	if (i == 0) return; 
	downheap(heap, i); 
	rbuildheap(i - 1); 
}
void buildheap() {
	for (int i = k / 2; i >= 1; i--) {
		downheap(heap, i);
	}
}


int main() {
	scanf("%d", &k);
	for (int i = 1; i <= k; i++) {
		scanf("%d", &heap[i]);
	}
	// rbuildheap1(1);
	// rbuildheap2(k/2);
	buildheap();
	printheap(heap);
	return 0;
}
