#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
typedef struct node {
	struct node* next;
	int vertex;
	int weight;
} node;
typedef struct graph {
	int vertices;
	node** adj;
	int* visit;
} graph;
typedef struct edge {
	int from;
	int to;
	int weight;
} edge;
int n, m;
graph* g;
edge heap[100];	// 힙 생성
int size = 0;

void setgraph() {
	g = malloc(sizeof(graph));
	g->vertices = n;
	g->visit = malloc(sizeof(int) * (n + 1));
	g->adj = malloc(sizeof(node*) * (n + 1));
	for (int i = 1; i <= n; i++) {
		g->visit[i] = 0;
		g->adj[i] = NULL;
	}
}
node* getnode(int vertex, int weight) {
	node* newnode = malloc(sizeof(node));
	newnode->next = NULL;
	newnode->weight = weight;
	newnode->vertex = vertex;
	return newnode;
}
void addedge(int start, int end, int weight) {
	node* p = getnode(end, weight);
	p->next = g->adj[start];
	g->adj[start] = p;

	if (start == end) return;

	node* q = getnode(start, weight);
	q->next = g->adj[end];
	g->adj[end] = q;
}
void swap(edge *a, edge *b) {	// 스왑
	edge c = *a;
	*a = *b;
	*b = c;
}
void upheap(int s) {
	if (s == 1) return;

	if (heap[s].weight < heap[s / 2].weight) {
		swap(&heap[s], &heap[s / 2]);
		upheap(s / 2);
	}
}
void downheap(int s) {
	if (s * 2 > size) {	// 자식 없음
		return;
	}
	int min = s * 2;
	if (size >= (min) + 1 && heap[min].weight > heap[s * 2 + 1].weight) {
		min++;
	}

	if (heap[min].weight < heap[s].weight) {
		swap(&heap[min], &heap[s]);
		downheap(min);
	}
}
void insertheap(int start, int end, int weight) {
	edge newedge;
	newedge.from = start;
	newedge.to = end;
	newedge.weight = weight;
	heap[++size] = newedge;
	upheap(size);
}
edge removemin() {
	swap(&heap[1], &heap[size]);
	size--;
	downheap(1);
	return heap[size + 1];
}
void prim() {
	int total_weight = 0;
	int count = 0;

	printf(" 1");	// 정점 1 방문
	node* p = g->adj[1];
	g->visit[1] = 1;

	while (p != NULL) {
		insertheap(1, p->vertex, p->weight);
		p = p->next;
	}
	while (count < n - 1) {
		edge e = removemin();
		if (g->visit[e.to] == 1) {
			continue;
		}
		printf(" %d", e.to);
		total_weight += e.weight;
		g->visit[e.to] = 1;

		p = g->adj[e.to];
		while (p != NULL) {
			if (g->visit[p->vertex] == 0) {
				insertheap(e.to, p->vertex, p->weight);
			}
			p = p->next;
		}
		count++;
	}
	printf("\n%d", total_weight);
}
int main() {
	int start, end, weight;
	scanf("%d %d", &n, &m);
	setgraph();
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &start, &end, &weight);
		addedge(start, end, weight);
	}
	prim();

	return 0;
}
