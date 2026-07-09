#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

enum boolean {FALSE, TRUE};

struct node {
    int vertex;
    struct node *link;
};
typedef struct node* nodePointer;

nodePointer graph[MAX_VERTICES];
int visited[MAX_VERTICES] = {FALSE};

struct stack {
  int item;
  struct stack* link;
};
typedef struct stack *stack_pointer;
stack_pointer top = NULL;

void push(stack_pointer *top, int item) {
  stack_pointer temp = (stack_pointer)malloc(sizeof(struct stack));
  temp->item = item;
  temp->link = *top;
  *top = temp;
}

int pop(stack_pointer *top) {
  stack_pointer temp = *top;
  int item;
  if(*top == NULL) {
    printf("stack is empty!\n");
    exit(0);
  }
  item = temp->item;
  *top = temp->link;
  free(temp);
  return item;
}

void printStack(stack_pointer top) {
  stack_pointer temp = top;
  while(temp != NULL) {
    printf("%2d ", temp->item);
    temp = temp->link;
  }
  printf("\n");
}

nodePointer graph[MAX_VERTICES];

/* depth first search of a graph beginning at v */
void dfs(int v) { // 재귀 dfs
  nodePointer w;
  if(!visited[v]) { // 방문하지 않았다면
    visited[v] = TRUE; // 방문 표시
    printf("%5d", v); // 출력
    for(w = graph[v]; w; w = w->link)  
      dfs(w->vertex); // 재귀 함수 호출
  }
} 

/* interative DFS */
void dfs_iterative(int v) { // 반복 dfs
  nodePointer w;
  push(&top, v);
  while(top) {
    v = pop(&top);
    if (!visited[v]) {
      visited[v] = TRUE; 
      printf("%5d", v);
      for (w = graph[v]; w; w = w->link)
        push(&top, w->vertex); // 스택의 특성으로 인해서 LIFO가 됨 (Last in First out) 
                               // ex) graphy[0]일 때 : 1 2(top)
    }
  }
}

// 재귀 dfs는 함수 호출 스택이 자동으로 깊이 우선 탐색을 수행
// 반복 dfs는 개발자가 스택을 관리하며 인접 정점의 push 순서에 따라 방문 순서가 달라질 수 있믐

void main() {

    nodePointer prev;
    nodePointer np;

    /* adjacency list for vertex 0 */
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 1; np->link = NULL; graph[0] = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 2; np->link = NULL; prev->link = np;

    /* adjacency list for vertex 1 */
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 0; np->link = NULL; graph[1] = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 3; np->link = NULL; prev->link = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 4; np->link = NULL; prev->link = np;

    /* adjacency list for vertex 2 */
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 0; np->link = NULL; graph[2] = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 5; np->link = NULL; prev->link = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 6; np->link = NULL; prev->link = np;

    /* adjacency list for vertex 3 */
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 1; np->link = NULL; graph[3] = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 7; np->link = NULL; prev->link = np;

    /* adjacency list for vertex 4 */
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 1; np->link = NULL; graph[4] = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 7; np->link = NULL; prev->link = np;

    /* adjacency list for vertex 5 */
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 2; np->link = NULL; graph[5] = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 7; np->link = NULL; prev->link = np;

    /* adjacency list for vertex 6 */
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 2; np->link = NULL; graph[6] = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 7; np->link = NULL; prev->link = np;

    /* adjacency list for vertex 7 */
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 3; np->link = NULL; graph[7] = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 4; np->link = NULL; prev->link = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 5; np->link = NULL; prev->link = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 6; np->link = NULL; prev->link = np;

    for(int i=0; i<8; i++) visited[i] = 0;    
    dfs(0);
    printf("\n");

    for(int i=0; i<8; i++) visited[i] = 0;
    dfs_iterative(0);
    printf("\n");
}

/*
      0
    /   \
   1     2
  / \   / \
 3   4 5   6
  \  \ /   /
      7
*/