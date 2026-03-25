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
	int max = 0;
	int maxindex = -1;
	for (int i = n-1; i >=0; i--) {
		for (int j = 0; j <= i; j++) {
			if (*(p + j) > max) {
				max = *(p + j);
				maxindex = j;
			}
		}
		swap(p + maxindex, p + i);
		max = 0; maxindex = -1;
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

/*
음수 포함 버전
void sort() {
	int max = 0;
	int index;
	for (int i = n-1; i > 0; i--) {
		max = p[0]; index = 0;	// 최대값을 p[0]으로
		for (int j = 1; j <= i; j++) {	// 1부터 시작
			if (max < p[j]) {
				max = p[j];
				index = j;
			}
		}
		swap(p + index, p + i);
	}
}
*/
