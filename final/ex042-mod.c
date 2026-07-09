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

struct queue {
  int item;
  struct queue* link;
};
typedef struct queue *queue_pointer;
queue_pointer front = NULL, rear = NULL;

void addq(queue_pointer *front, queue_pointer *rear, int item) {
  /* add an element to the rear of the queue */
  queue_pointer temp = (queue_pointer)malloc(sizeof(struct queue));
  temp->item = item;
  temp->link = NULL;
  if(*front)
    (*rear)->link = temp;
  else *front = temp;
  *rear = temp;
}

int deleteq(queue_pointer *front) {
  /* delete an element from the queue */
  queue_pointer temp = *front;
  int item;
  if(*front == NULL) {
    printf("queue is empty!\n");
    exit(0);
  }
  item = temp->item;
  *front = temp->link;
  free(temp);
  return item;
}

void printq(queue_pointer front) {
  queue_pointer temp = front;
  while(temp != NULL) {
    printf("%2d ", temp->item);
    temp = temp->link;
  }
  printf("\n");
}

// void bfs(int v) {
//   nodePointer w;

//   addq(&front, &rear, v);
//   while (front) {
//       v = deleteq(&front);
//       if (!visited[v]) {
//           visited[v] = TRUE; printf("%5d", v);
//           for (w = graph[v]; w; w = w->link)
//               addq(&front, &rear, w->vertex);
//       }
//   }
// }

void bfs(int v) {
    visited[v] = TRUE;
    printf("%5d", v); 
    addq(&front, &rear, v);
    while (front) {  // queue is not empty 
        v = deleteq(&front);
        for (nodePointer e = graph[v]; e; e = e->link) {
            int w = e->vertex;
            if (!visited[w]) {
                visited[w] = TRUE; 
                printf("%5d", w);
                addq(&front, &rear, w);
            }
        }
    } 
}



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
    
    bfs(0);
    printf("\n");
}