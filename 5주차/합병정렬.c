#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
typedef struct node {
	struct node* next;
	int elem;
} node;
typedef struct set {
	node* L1;
	node* L2;
} set;

node* getnode(int elem) {
	node* newnode = malloc(sizeof(node));
	newnode->next = NULL;
	newnode->elem = elem;
	return newnode;
}
void addnode(node **L, int elem) {
	node* newnode = getnode(elem);
	node* p = *L;
	if (p == NULL) {
		*L = newnode;
		return;
	}
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = newnode;
}
set mg_partition(node *L, int m) {
	node* p = L;
	node* pre = NULL;
	for (int i = 0; i < m; i++) {
		pre = p;
		p = p->next;
	}
	pre->next = NULL;
	set s;
	s.L1 = L;
	s.L2 = p;
	return s;
}
node* merge(node *L1, node *L2) {
	if (L1 == NULL) return L2;
	else if (L2 == NULL) return L1;

	if (L1->elem <= L2->elem) {
		L1->next = merge(L1->next, L2);
		return L1;
	}
	else {
		L2->next = merge(L1, L2->next);
		return L2;
	}
}
node* mergesort(node *L, int n) {
	if (n <= 1) return L;

	int m = n / 2;
	set s = mg_partition(L, m);

	s.L1 = mergesort(s.L1, m);
	s.L2 = mergesort(s.L2, n-m);

	L = merge(s.L1, s.L2);
	return L;
}
void print(node* L) {
	node* p = L;
	while (p != NULL) {
		printf(" %d", p->elem);
		p = p->next;
	}
	printf("\n");
}
int main() {
	int n, elem;
	node* L = NULL;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &elem);
		addnode(&L, elem);
	}
	L = mergesort(L, n);
	print(L);
	return 0;
}
