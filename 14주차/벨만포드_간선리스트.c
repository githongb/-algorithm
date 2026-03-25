#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
typedef struct edge {	// 간선 리스트
	int from;
	int to;
	int weight;
} edge;
typedef struct graph {
	int vertices;
	edge *adj;
} graph;
int n, m, s;
graph *g;
int edge_count = 0;
int* dist;
int inf = 100000;	// 무한

void setgraph() {
	g = malloc(sizeof(graph));
	g->vertices = n;
	g->adj = malloc(sizeof(edge) * (m));
	dist = malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++) {
		dist[i] = inf;
	}
}
void insertedge(int start, int end, int weight) {	// 방행 가중그래프 간선 추가
	edge e;
	e.from = start;
	e.to = end;
	e.weight = weight;
	g->adj[edge_count++] = e;
}
void print() {
	for (int i = 1; i <= n; i++) {
		if (i == s || dist[i] == inf) {
			continue;
		}
		printf("%d %d\n", i, dist[i]);
	}
}
void bellmanford() {
	dist[s] = 0; // 시작정점 초기화

	for (int i = 0; i < n - 1; i++) {	// n-1은 출발정점 > 도착정점으로 연결되는 간선 개수의 최대값
		for (int j = 0; j < m; j++) {	// 모든 간선 확인
			edge e = g->adj[j];	// 간선 꺼내기
			if (dist[e.from] != inf && dist[e.to] > dist[e.from] + e.weight) {
			// 출발 정점이 INF가 아니고, 더 작은 거리가 갱신 가능하면
				dist[e.to] = dist[e.from] + e.weight;
			}
		}
	}
	print();
}
int main() {
	int start, end, weight;
	scanf("%d %d %d", &n, &m, &s);
	setgraph();
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &start, &end, &weight);
		insertedge(start, end, weight);
	}

	bellmanford();

	return 0;
}
