#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
typedef struct edge {	// 힙, 간선리스트
	int start;
	int end;
	int weight;
} edge;
typedef struct graph {	// 그래프
	int vertices;
	edge* adj;	// 간선 리스트
} graph;
int n, m;
int edge_count = 0;
graph* g;
int* parent;	// 분리집합
edge heap[100];	// 힙
int h_count = 0;

void setgraph() {
	g = malloc(sizeof(graph));
	g->vertices = n;
	g->adj = malloc(sizeof(edge) * (m));	// 간선리스트
	parent = malloc(sizeof(int) * (n + 1));	// 분리집합
	for (int i = 1; i <= n; i++) {	// 분리집합 초기화, 자기자신을 가리킴
		parent[i] = i;
	}
}
void swap(edge* a, edge* b) {
	edge c = *a;
	*a = *b;
	*b = c;
}
void upheap(int k) {
	if (k == 1) return;
	if (heap[k].weight < heap[k / 2].weight) {
		swap(&heap[k], &heap[k / 2]);
		upheap(k / 2);
	}
}
void downheap(int k) {
	if (k * 2 > h_count) return;	// 자식 x
	int index = k * 2;
	if (index + 1 <= h_count && heap[index + 1].weight < heap[index].weight) {
		index = index + 1;
	}
	if (heap[index].weight < heap[k].weight) {
		swap(&heap[index], &heap[k]);
		downheap(index);
	}
}
void insertheap(edge e) {
	heap[++h_count] = e;
	upheap(h_count);
}
edge removemin() {
	swap(&heap[1], &heap[h_count]);
	h_count--;
	downheap(1);
	return heap[h_count + 1];
}
void insertedge(int start, int end, int weight) {
	g->adj[edge_count].start = start;
	g->adj[edge_count].end = end;
	g->adj[edge_count].weight = weight;
	insertheap(g->adj[edge_count++]);	// 힙 추가
}
int find_parent(int x) {	// 부모 노드 찾기
	if (parent[x] == x) return x;	// 부모노드면 리턴
	return parent[x] = find_parent(parent[x]);	// 경로 압축 기법
}
void union_parent(int a, int b) {	// 합 집합
	int x = find_parent(a);
	int y = find_parent(b);
	parent[x] = y;
}
void kruskal() {
	int count = 0;
	int total_weight = 0;
	while (count < n - 1) {
		edge e = removemin();	// 가중치 최소 간선
		if (find_parent(e.start) != find_parent(e.end)) {	// 분리집합이 다르면
			union_parent(e.start, e.end);	// 합집합
			total_weight += e.weight;	// 가중치 합
			printf(" %d", e.weight);	// 가중치 출력
			count++;
		}
	}
	printf("\n%d", total_weight);
}

int main() {
	int start, end, weight;
	scanf("%d %d", &n, &m);
	setgraph();
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &start, &end, &weight);
		insertedge(start, end, weight);
	}
	kruskal();

	return 0;
}
