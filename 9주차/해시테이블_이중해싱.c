#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
int n, m, q;
int hash(int key) {
	return key % m;
}
int doublehash(int key, int r) {	// 이중해싱
	return r - (key % r);
}
int insertkey(int *table, int key) {
	int h = hash(key);
	int r = q;	// 서로소 지정
	int c = doublehash(key, r);
	for (int i = 0; i < m; i++) {
		int idx = (h + (i * c)) % m;
		if (table[idx] == 0) {
			table[idx] = key;
			return idx;
		}
		printf("C");
	}
}
void search(int *table, int key) {
	int h = hash(key);
	int r = q;	// 서로소 지정
	int c = doublehash(key, r);
	for (int i = 0; i < m; i++) {
		int idx = (h + (i * c)) % m;
		if (table[idx] == key) {
			printf("%d %d\n", idx, key);
			return;
		}
	}
	printf("-1\n");
}
void print(int* table) {
	for (int i = 0;i < m; i++) {
		printf(" %d", table[i]);
	}
	printf("\n");
}
void freeall(int *table) {
	free(table);
}
int main() {
	int key;
	scanf("%d %d %d", &m, &n, &q);
	int* table = malloc(sizeof(int) * m);
	for (int i = 0; i < m; i++) {	// 버켓 초기화
		table[i] = 0;
	}
	char c;
	while (1) {
		scanf(" %c", &c);
		if (c == 'i') {
			scanf("%d", &key);
			printf("%d\n", insertkey(table, key));
		}
		else if (c == 's') {
			scanf("%d", &key);
			search(table, key);
		}
		else if (c == 'p') {
			print(table);
		}
		else if (c == 'e') {
			freeall(table);
			exit(0);
		}
	}
	
	return 0;
}
