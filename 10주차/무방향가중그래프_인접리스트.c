#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
typedef struct node {
	int vertex; // 정점
	int weight; // 가중치
	struct node* next; // 연결
} node;
typedef struct graph {
	int vertices;	// 정점 수
	node** adj;	// 배열
} graph;
node* getnode(int v, int w) {
	node* newnode = malloc(sizeof(node));
	newnode->vertex = v;
	newnode->weight = w;
	newnode->next = NULL;
	return newnode;
}
void addnode(graph* g, int start, int end, int w) {
	node* check = g->adj[end];;
	while (check != NULL) {	// 중복 체크
		if (check->vertex == start) {
			return;
		}
		check = check->next;
	}
	node* newnode = getnode(start, w);
	node* p = g->adj[end];
	node* pre = NULL;

	while (p != NULL && p->vertex < start) {	// p == null 또는 (정점 > start)일 경우 중단
		pre = p;
		p = p->next;
	}
	if (pre == NULL) {	// 맨 앞에 추가할 경우
		newnode->next = g->adj[end];
		g->adj[end] = newnode;
	}
	else {	// 중간 or 뒤에 추가할 경우
		newnode->next = p;
		pre->next = newnode;
	}
	
	if (start == end) return;	// 중첩이면 리턴
	else {	// 한번더 실행
		addnode(g, end, start, w);
	}
}
graph* setgraph() {
	graph *g = malloc(sizeof(graph));
	g->vertices = 6;	// 정점 개수
	g->adj = malloc(sizeof(node*) * 7); // 배열 1~7까지 사용

	for (int i = 1; i < 7; i++) {	// 배열 초기화
		g->adj[i] = NULL;
	}

	addnode(g, 5, 6, 3);
	addnode(g, 5, 5, 4);
	addnode(g, 3, 5, 4);
	addnode(g, 2, 3, 1);
	addnode(g, 1, 6, 2);
	addnode(g, 1, 4, 1);
	addnode(g, 1, 3, 1);
	addnode(g, 1, 2, 1);

	return g;
}
void printnode(graph *g, int k) {
	if (k > g->vertices || k < 1) {
		printf("-1\n");
		return;
	}
	node* p = g->adj[k];
	while (p != NULL) {
		printf(" %d %d", p->vertex, p->weight);
		p = p->next;
	}
	printf("\n");
}
void change_weight(graph *g, int start, int end,  int w) {
	if (( start > 6 || start < 1 ) || ( end > 6 || end < 1 )) {
		printf("-1\n");
		return;
	}
	if (w != 0) {	// 가중치 (변경 / 생성)
		node* p = g->adj[start];
		node* q = g->adj[end];
		while (p != NULL && p->vertex != end) {
			p = p->next;
		}
		while (q != NULL && q->vertex != start) {
			q = q->next;
		}
		if (p == NULL) {
			addnode(g, start, end, w);
		}
		else {
			p->weight = w;
			q->weight = w;
		}
	}
	else {	// 노드 제거
		node* pre = NULL;
		node* p = g->adj[start];
		while (p->vertex != end) {
			pre = p;
			p = p->next;
		}
		if (pre == NULL) {
			g->adj[start] = p->next;
		}
		else {
			pre->next = p->next;
		}
		free(p);
		// 한번 더
		if (start != end) {
			node* pre_q = NULL;
			node* q = g->adj[end];
			while (q->vertex != start) {
				pre_q = q;
				q = q->next;
			}
			if (pre_q == NULL) {
				g->adj[end] = q->next;
			}
			else {
				pre_q->next = q->next;
			}
			free(q);
		}
	}
}
int main() {
	char c;
	int k, start, end, w;
	graph *g = setgraph();	// 그림3으로 초기화
	while (1) {
		scanf(" %c", &c);
		if (c == 'a') {
			scanf("%d", &k);
			printnode(g, k);
		}
		else if (c == 'm') {
			scanf("%d %d %d", &start, &end, &w);
			change_weight(g, start, end, w);
		}
		else if (c == 'q') {
			exit(0);
		}
	}

	
	return 0;
}
