#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
typedef struct node {
	struct node* left;
	struct node* right;
	struct node* parent;
	int key;
	int height;
} node;

int getheight(node *p) {
	if (p == NULL) return 0;
	return p->height;
}
void updateheight(node *p) {
	int a = getheight(p->left);
	int b = getheight(p->right);

	p->height = 1 + ((a > b) ? a : b);	//연산자 순서
}
node* getnode(int key, node* parent) {
	node* newnode = malloc(sizeof(node));
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = parent;
	newnode->key = key;
	newnode->height = 1;
	return newnode;
}
void rotate_left(node **h) {
	node* up = (*h)->right;
	node* down = *h;

	if (down->parent != NULL) {	// 부모 연결
		if (down->parent->left == down) {
			down->parent->left = up;
		}
		else {
			down->parent->right = up;
		}
	}
	up->parent = down->parent;
	down->parent = up;
	down->right = up->left;
	if (down->right) {	// 다운 자식의 부모 연결 
		down->right->parent = down;
	}
	up->left = down;

	updateheight(down);	// 높이 갱신 해줘야 함
	updateheight(up);
	
	*h = up;
}
void rotate_right(node ** h) {
	node* up = (*h)->left;
	node* down = *h;

	if (down->parent != NULL) {
		if (down->parent->left == down) {
			down->parent->left = up;
		}
		else {
			down->parent->right = up;
		}
	}
	up->parent = down->parent;
	down->parent = up;
	down->left = up->right;
	if (down->left) {
		down->left->parent = down;
	}
	up->right = down;

	updateheight(down);
	updateheight(up);

	*h = up;
}
void rebalance(node **h) {
	updateheight(*h);
	int k = getheight((*h)->left) - getheight((*h)->right);

	if (k >= 2) {	//L
		int t = getheight((*h)->left->left) - getheight((*h)->left->right);
		if (t > 0) {	//LL
			rotate_right(h);
		}
		else {	//LR
			rotate_left(&((*h)->left));
			rotate_right(h);
		}
	}
	else if (k <= -2) {	//R
		int t = getheight((*h)->right->left) - getheight((*h)->right->right);
		if (t > 0) {	//RL
			rotate_right(&((*h)->right));
			rotate_left(h);
		}
		else {	//RR
			rotate_left(h);
		}
	}
}
void insertitem(node **h, int key) {
	if (*h == NULL) {
		*h = getnode(key, NULL);
		return;
	}
	node* p = *h;
	if (p->key > key) {
		if (p->left == NULL) {
			p->left = getnode(key, p);	//리턴하면 안됌 p높이 갱신이 안됌
		}
		else insertitem(&(p->left), key);
	}
	else {
		if (p->right == NULL) {
			p->right = getnode(key, p);
		}
		else insertitem(&(p->right), key);
	}
	rebalance(h);	// 높이 갱신 및 회전
}
node* search(node* h, int key) {
	if (h == NULL) return NULL;
	if (h->key == key) return h;
	if (h->key > key) {
		return search(h->left, key);
	}
	else {
		return search(h->right, key);
	}
}
node* findmin(node* p) {
	while (p->left != NULL) {
		p = p->left;
	}
	return p;
}
void delnode(node** h, node *p) {
	node* pp;
	if (p->left == NULL && p->right == NULL) {
		if (p == *h) {
			*h = NULL;
		}
		else {
			if (p->parent->left == p) {
				p->parent->left = NULL;
			}
			else {
				p->parent->right = NULL;
			}
		}
		pp = p->parent;
		free(p);
	}
	else if (p->left == NULL || p->right == NULL){
		node* child = (p->left == NULL) ? p->right : p->left;
		if (p == *h) {
			*h = child;
		}
		else {
			if (p->parent->left == p) {
				p->parent->left = child;
			}
			else {
				p->parent->right = child;
			}
		}
		child->parent = p->parent;
		pp = p->parent;
		free(p);
	}
	else {
		node *q = findmin(p->right);
		p->key = q->key;
		delnode(h, q);
		return;
	}
	while (pp->parent != NULL) {	//삭제 노드의 부모부터 올라가면서 회전
		rebalance(&pp);
		pp = pp->parent;
	}
	rebalance(&pp);
	*h = pp;
}
void print(node *h) {
	if (h == NULL) return;
	printf(" %d", h->key);
	print(h->left);
	print(h->right);
}
int main() {
	char c;
	int key;
	node* h = NULL;
	while (1) {
		scanf(" %c", &c);
		if (c == 'i') {
			scanf("%d", &key);
			insertitem(&h, key);
		}
		else if (c == 'd') {
			scanf("%d", &key);
			node *p = search(h, key);
			if (p != NULL) {
				printf("%d\n", p->key);
				delnode(&h, p);
			}
			else {
				printf("X\n");
			}
		}
		else if (c == 's') {
			scanf("%d", &key);
			node* p = search(h, key);
			if (p == NULL) {
				printf("X\n");
			}
			else {
				printf("%d\n", p->key);
			}
		}
		else if (c == 'p') {
			print(h);
			printf("\n");
		}
		else if (c == 'q') {
			exit(0);
		}
	}
	return 0;
}
