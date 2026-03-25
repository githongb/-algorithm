#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
int search(int *p, int start, int end, int k) {	// k보다 작은 값중 가장 큰 값
	if (start > end) return -1;	// 역전되면 

	int mid = (start + end) / 2;	// 중간 인덱스

	if (p[mid] < k) {	// 중앙값 < k
		int m = search(p, mid + 1, end, k);	// 오른쪽 재귀 탐색
		if (m == -1) {	// 오른쪽을 탐색한 순간 -1 불가능 = 마지막 탐색 값이 가장 큰 값
			return mid;	// 이때 mid 는 마지막 한개 남은 탐색 값
		}
		return m;	// -1가 아닐경우
	}
	else if (p[mid] > k) {	// 중앙값 > k
		return search(p, start, mid - 1, k);	//왼쪽 재귀 탐색
	}
	else return mid;	// 값 같으면 리턴
}
int main(){
	int n, k;
	scanf("%d %d", &n, &k);
	int* p = malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) {
		scanf("%d", p+i);
	}
	int d = search(p, 0, n - 1, k);

	printf(" %d", d);
	return 0;
}

/* 반복문
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
int search(int *p, int start, int end, int k) {	// k보다 큰 값중 가장 작은 값
	int mid;
	int result = end + 1;	// 값이 존재하지 않을 경우 리턴
  
	while (start <= end) {
		mid = (start + end) / 2;
		if (p[mid] > k) {	// 전 경우와 반대인 경우, 중앙값 > k 인 경우가 생기면 
			end = mid - 1;	// 크거나 같은 값이 존재함
			result = mid;
		}
		else if (p[mid] < k) {	// 중앙값 < k
			start = mid + 1;
		}
		else {
			return mid;
		}
	}
	return result;	// 1번 if문을 지나치면 결과 리턴, 아니면 처음에 저장한 n 리턴
}
int main(){
	int n, k;
	scanf("%d %d", &n, &k);
	int* p = malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) {
		scanf("%d", p+i);
	}
	int d = search(p, 0, n - 1, k);

	printf("%d", d);
	return 0;
}
*/
