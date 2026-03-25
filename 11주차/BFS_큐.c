#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
typedef struct graph {
	int adj[101][101];
	int vertices;
	int* visit;
} graph;

graph* setgraph(int n) {
	graph* g = malloc(sizeof(graph));
	g->vertices = n;	// 정점 수
	g->visit = malloc(sizeof(int) * (n + 1));
	for (int i = 1; i < n + 1; i++) {	//그래프 초기화
		g->visit[i] = 0;
		for (int j = 1; j < n + 1; j++) {
			g->adj[i][j] = 0;
		}
	}
	return g;
}
void insertedge(graph *g, int start, int end) {
	g->adj[start][end] = 1;
	g->adj[end][start] = 1;
}
/*
레벨순회 {
	q 생성;
	q 에 시작 정점 삽입
	while (q가 빌때까지) {
		front 방문;
		
		for (인접 정점) {
			큐에 삽입
		}
	}
}
*/
void bfs(graph *g, int s) {
	int *q = malloc(sizeof(int)*(g->vertices + 1)); // 큐 배열 생성
	int front = 1, rear = 1;
	q[rear++] = s;	// 정점 값 삽입
	g->visit[s] = 1;	// 삽입후 항상 방문처리
	while (front < rear) {	// 큐가 빌때까지
		int k = q[front++];	// 맨 앞값 제거 후 출력
		printf("%d\n", k);
		for (int i = 1; i < g->vertices + 1; i++) {	// k값이랑 연결된 노드중 아직 방문 안한 노드
			if (g->adj[k][i] == 1 && g->visit[i] == 0) {
				q[rear++] = i;	// 삽입, 방문처리
				g->visit[i] = 1;
			}
		}
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
	bfs(g, s);

	return 0;
}
