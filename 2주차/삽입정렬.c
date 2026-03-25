#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning (disable:4996)
void swap(int *a, int *b) {
	int c = *a;
	*a = *b;
	*b = c;
}
void sort(int *p, int n) {
	for (int i = 1; i < n; i++) {
		for (int j = i; j > 0; j--){
			if (*(p + j) < *(p + j - 1)) {
				swap(p + j, p + j - 1);
			}
			else break;
		}
		for (int i = 0; i < n; i++) {	// 과정 확인
			printf(" %d", *(p + i));
		}
		printf("\n");
	}
}
int main() {
	int n, *p;
	scanf("%d", &n);
	p = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf("%d", p + i);
	}
	sort(p, n);
	for (int i = 0; i < n; i++) {
		printf(" %d", *(p + i));
	}
	return 0;
}

/* 밀기(shift) 버전
void sort() {
	for (int i = 1; i < n; i++) {
		int key = p[i];
		int j = i - 1;
		while (j >= 0 && p[j] > key) {
			p[j + 1] = p[j];
			j--;
		}
		p[j + 1] = key;
	}
}
*/
