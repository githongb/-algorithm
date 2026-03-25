#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning (disable:4996)
int h[100], n = 0;

void swap(int a, int b) {	//스왑
	int c = h[a];
	h[a] = h[b];
	h[b] = c;
}
void upheap(int i) {	//업힙
	if (i == 1) {
		return;
	}
	if (h[i] <= h[i / 2]) {
		return;
	}
	swap(i, i / 2);
	upheap(i/2);
}
void downheap(int i) {	//다운힙
	int l = i*2;
	int r = i*2+1;
	int larger;
	if (l > n) {
		return;
	}
	if (r <= n && h[r] >= h[l]) {
		larger = r;
	}
	else larger = l;
	if (h[larger] > h[i]) {
		swap(larger, i);
		downheap(larger);
	}
}
void insertkey(int key) {	//삽입
	h[++n] = key;
	upheap(n);
}
void sort() {	//정렬
	while (n >= 2) {
		swap(1, n);
		n--;
		downheap(1);
	}
}
void printheap() {	//출력
	for (int i = 1; i <= n; i++) {
		printf(" %d", h[i]);
	}
	printf("\n");
}
void rbuildheap(int i) {
	if (i > n) {	// 외부노드
		return;
	}
	rbuildheap(i * 2);	// 왼쪽
	rbuildheap(i * 2 + 1);	// 오른쪽
	downheap(i);	// 자기자신(후위순회)
}
int main(){
	int key;
	int m;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d", &key);
		insertkey(key);
	}
	/* 상향식 힙
	for (int i = 1; i <= m; i++) {
		scanf("%d", &h[i]);
	}
	n = m;
	rbuildheap(1);
	*/
	sort();
	n = m;	//sort에서 n을 감소시켰으므로 초기화
	printheap();

	return 0;
}
