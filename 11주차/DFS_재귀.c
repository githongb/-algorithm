#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
typedef struct node {
	struct node* next;
	int vertex;
} node;
typedef struct graph {
	int vertices;
	node** adj;
	int* visite;
} graph;
graph* setgraph(int n) {
	graph* g = malloc(sizeof(graph));
	g->vertices = n;
	g->visite = malloc(sizeof(int) * n + 1);	// 정점 번호 1부터 시작
	for (int i = 1; i < n + 1; i++) {	// 방문 확인 배열 초기화
		g->visite[i] = 0;
	}
	g->adj = malloc(sizeof(node*) * n + 1);
	for (int i = 1; i < n + 1; i++) {	// 리스트 배열 초기화
		g->adj[i] = NULL;
	}
	return g;
}
node* getnode(int v) {
	node* newnode = malloc(sizeof(node));
	newnode->next = NULL;
	newnode->vertex = v;
	return newnode;
}
void insertedge(graph *g, int start, int end) {
	node* check = g->adj[end];
	while (check != NULL) {	// 중복체크
		if (check->vertex == start) return;
		check = check->next;
	}

	node* newnode = getnode(start);
	node* p = g->adj[end];
	node* pre = NULL;
	while (p != NULL && p->vertex < newnode->vertex) {	// 삽입정렬
		pre = p;
		p = p->next;
	}
	if (pre == NULL) {	// 맨앞 삽입
		newnode->next = g->adj[end];
		g->adj[end] = newnode;
	}
	else {
		newnode->next = p;
		pre->next = newnode;
	}

	if (start != end) insertedge(g, end, start);	// 한번더
}
void dfs(graph *g, int s) {	// 한 정점에서 가장작은 정점을 찾아 계속 방문
	if (g->visite[s] == 1) {	// case : 이미 방문 했으면
		return;
	}
	// 본문 : 방문 안했으면
	printf("%d\n", s);
	g->visite[s] = 1;

	node* p = g->adj[s];
	while (p != NULL) {	// 정점에 인접한 리스트 순회
		dfs(g, p->vertex);	// 재귀
		p = p->next;
	}
}
int main() {
	int n, m, s;	// 정점 수, 간선 수, 정점 번호
	int start, end;
	scanf("%d %d %d", &n, &m, &s);
	graph* g = setgraph(n);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &start, &end);
		insertedge(g, start, end);
	}
	dfs(g, s);

	return 0;
}
