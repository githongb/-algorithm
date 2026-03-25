#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
typedef struct node {
	struct node* next;
	int weight;
	int vertex;
} node;
typedef struct graph {
	int vertices;
	node** adj;
} graph;
typedef struct hnode {	// 다익스트라 힙
	int vertex;
	int dist;	// 한 정점으로 부터의 거리(누적 거리)
} hnode;
hnode h[1000];	// 힙
int h_count = 0;
int n, m, s;
graph* g;
int* dist;	// 거리 배열

void swap(hnode *a, hnode *b) {
	hnode c = *a;
	*a = *b;
	*b = c;
}
void upheap(int i) {
	if (i == 1) return;
	if (h[i].dist < h[i / 2].dist) {
		swap(&h[i], &h[i / 2]);
		upheap(i / 2);
	}
}
void downheap(int i) {
	if (i * 2 > h_count) return; //자식 없음

	int min = i * 2;
	if (min + 1 <= h_count && h[min + 1].dist < h[min].dist) {
		min += 1;
	}

	if (h[min].dist < h[i].dist) {
		swap(&h[min], &h[i]);
		downheap(min);
	}
}
hnode removemin() {
	swap(&h[1], &h[h_count]);
	h_count--;
	downheap(1);
	return h[h_count + 1];
}
void insertheap(int v, int d) {
	hnode newnode;
	newnode.dist = d;
	newnode.vertex = v;
	h[++h_count] = newnode;
	upheap(h_count);
}
void setgraph() {
	g = malloc(sizeof(graph));
	g->vertices = n;
	g->adj = malloc(sizeof(node*) * (n + 1));
	dist = malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++) {
		g->adj[i] = NULL;
		dist[i] = 1000;	// 무한대
	}
}
node* getnode(int vertex, int weight) {
	node* newnode = malloc(sizeof(node));
	newnode->next = NULL;
	newnode->vertex = vertex;
	newnode->weight = weight;
	return newnode;
}
void insertedge(int start, int end, int weight) {
	node* p = getnode(end, weight);
	p->next = g->adj[start];
	g->adj[start] = p;

	if (start == end) return;

	node* q = getnode(start, weight);
	q->next = g->adj[end];
	g->adj[end] = q;
}
void print() {
	for (int i = 1; i <= n; i++) {
		if (dist[i] != 0 && dist[i] != 1000) {
			printf("%d %d\n", i, dist[i]);
		}
	}
}
void dijkstra() {
	dist[s] = 0;	// 시작 정점의 거리 0
	insertheap(s, 0);	// 힙에 삽입

	while (h_count != 0) {	// 정점이 남아있지 않을 때 까지
		hnode e = removemin();	// 가장 가까운 정점 꺼내기

		/*한 정점이 여러번 들어갈 수 있음, 더 작은 누적거리를 먼저 꺼내기 때문에
		나중에 꺼내는 큰 누적거리의 정점을 무시하기 위해*/
		if (e.dist > dist[e.vertex]) {	// 배열에 저장된 거리보다 크면 무시
			continue; // 이미 더 짧은 경로가 발견된 상태라 무시하고 다음으로 넘어감
		}

		node* p = g->adj[e.vertex];
		while (p != NULL) {
			// e,dist == dist[e.vertex] 같은 의미
			if (p->weight + dist[e.vertex] < dist[p->vertex]) { // 꺼낸 정점에서 다른 정점으로 가는 더 짧은 거리가 발견되면
				dist[p->vertex] = p->weight + dist[e.vertex];	// 거리 갱신
				insertheap(p->vertex, dist[p->vertex]);	// 힙에 삽입
			}
			p = p->next;
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

	dijkstra();

	return 0;
}
