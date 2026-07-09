#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
  int key;
} element;
element heap[MAX_ELEMENTS];
int n = 0;

void push(element item, int *n);
element pop(int *n);

void main() {

  int i, rn;
  element item;

  srand(time(NULL));
 
  printf("INSERTING: ");
  for(i=0; i<10; i++) {
    rn = rand() % 100 + 1;
    printf("%3d ", rn);
    item.key = rn;
    push(item, &n); // n은 함수 밖에서 정의되어 있음, 원소의 수를 뜻함
  }
  printf("\n\n");

  printf("DELETING:  ");
  for(i=0; i<10; i++) {
    item = pop(&n);
    printf("%3d ", item.key);
  }
  printf("\n");
}

void push(element item, int *n) {
  /* insert item into a max heap of current size *n */
  int i;
  if(HEAP_FULL(*n)) {
    fprintf(stderr, "The heap is full.\n");
    exit(1);
  }
  i = ++(*n);
  while((i != 1) && (item.key > heap[i/2].key)) { // 가리키는 노드가 1이 아니고 다루는 key 값이 부모 노드의 key 값보다 크면
    heap[i] = heap[i/2]; // 부모 노드의 값을 현재 노드에 넣음
    i /= 2; // 현재 노드의 위치를 부모 노드로 이동
  }
  heap[i] = item;
}

element pop(int *n) {
  /* delete element with the highest key from the heap */
  int parent, child;
  element item, temp;
  if(HEAP_EMPTY(*n)) {
    fprintf(stderr, "The heap is empty");
    exit(1);
  }
  /* save value of the element with the largest key */
  item = heap[1]; // 루트의 값 삭제
  /* use the last element in the heap to adjust heap */
  temp = heap[(*n)--]; // 가장 마지막 노드의 값을 루트로 올리고, n을 감소시킴
  parent = 1;
  child = 2;
  while(child <= *n) {
    /* find the larger child of the current parent */
    if((child < *n) && (heap[child].key < heap[child+1].key)) child++; // 값이 더 큰 자식 노드로 이동
    if(temp.key >= heap[child].key) break; // 가져온 가장 마지막 노드의 값이 비교하는 자식 노드의 값보다 크면 반복문 종료
    /* move to the next lower level */
    heap[parent] = heap[child]; // 부모 노드와 자식 노드 값 변경
    parent = child;
    child *= 2;
  }
  heap[parent] = temp;
  return item;
}

