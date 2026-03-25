#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
typedef struct graph {
	int vertex;
	int adj[7][7];
} graph;
void add(graph *g, int start, int end, int w) {	// 연결
	g->adj[start][end] = w;
	g->adj[end][start] = w;
}
graph* setgraph() {
	graph* g = malloc(sizeof(graph));
	g->vertex = 6;
	for (int i = 1; i < 7; i++) {
		for (int j = 1; j < 7; j++) {
			g->adj[i][j] = 0;
		}
	}
	add(g, 1, 2, 1);
	add(g, 1, 3, 1);
	add(g, 1, 4, 1);
	add(g, 1, 6, 2);
	add(g, 2, 3, 1);
	add(g, 3, 5, 4);
	add(g, 5, 5, 4);
	add(g, 5, 6, 3);
	return g;
}
void printnode(graph* g, int k) {
	if (k > 6 || k < 1) {
		printf("-1\n");
		return;
	}
	for (int i = 1; i < 7; i++) {
		if (g->adj[k][i] != 0) {
			printf(" %d %d", i, g->adj[k][i]);
		}
	}
	printf("\n");
}
void change_weight(graph *g, int start, int end, int w) {
	if (start > 6 || start < 1 || end > 6 || end < 1) {
		printf("-1\n");
		return;
	}
	add(g, start, end, w);
}
int main() {
	char c;
	int k, start, end, w;
	graph* g = setgraph();	// 그림3으로 초기화
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
