#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
int parent[MAX_SIZE];

int simpleFind(int i) { // 루트 찾기
    for( ; parent[i] >= 0; i = parent[i]) // parent[i]가 양수 : 루트 가리킴 -> 루트로 이동
        ;
    return i;
}

void weightedUnion(int i, int j) { // 집합 합치기 (작은 집합을 큰 집합 밑으로)
    int temp = parent[i] + parent[j];
    if(parent[i] > parent[j]) { // 루트 값은 음수 -> 음수 비교 (절댓값-집합 속 원소의 수가 더 큰 쪽이 더 큰 집합)
        parent[i] = j; // i를 j로 연결
        parent[j] = temp; // j의 절댓값 증가 (집합 속 원소 수)
    } else {
        parent[j] = i; // j를 i로 연결
        parent[i] = temp; // i의 절댓값 증가 (집합 속 원소 수)
    }
}

void main() {

    int i, j, n, found;
    printf("Enter number of items (<= %d) ", MAX_SIZE);
    scanf("%d", &n);

    for(i=0; i<n; i++) parent[i] = -1;

    printf("Enter a pair of equivalent items (-1 -1 to quit): ");
    scanf("%d%d", &i, &j);
    
    weightedUnion(i, j);

    while(i >= 0) {
        printf("Enter a pair of equivalent items (-1 -1 to quit): ");
        scanf("%d%d", &i, &j);

        weightedUnion(simpleFind(i), simpleFind(j));
    }

    for(i=0; i<n; i++) {
        found = 0;
        for(j=0; j<n; j++) {
            if(simpleFind(j) == i) {
                printf("%d ", j);
                found = 1;
            }
        }
        if(found > 0) printf("\n");
    }
}