#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 100

struct node {
    char data;
    struct node *left_child, *right_child;
};
typedef struct node *tree_pointer;

tree_pointer create_tree_node(char);
void recursive_inorder(tree_pointer);
void iter_inorder(tree_pointer);
void iter_postorder(tree_pointer);
void iter_preorder(tree_pointer);
void level_order(tree_pointer);

/* TODO: add function prototype if necessary */
/* if stack full, output error and exit */
void add(tree_pointer* stack, int* top, tree_pointer node);
/* if stack empty, return NULL */
tree_pointer delete(tree_pointer* stack, int* top);
/* if queue full, output error and exit */
void addq(tree_pointer* queue, int front, int* rear, tree_pointer node);
/* if queue empty, return NULL */
tree_pointer deleteq(tree_pointer* queue, int* front, int rear);

void main() {
    /* create a tree that represents an arithmetic expression */
    tree_pointer ptr, ptr1, ptr2;

    ptr1 = create_tree_node('A');
    ptr2 = create_tree_node('B');
    ptr = create_tree_node('/');
    ptr->left_child = ptr1;
    ptr->right_child = ptr2;

    ptr1 = ptr;
    ptr2 = create_tree_node('C');
    ptr = create_tree_node('*');
    ptr->left_child = ptr1;
    ptr->right_child = ptr2;

    ptr1 = ptr;
    ptr2 = create_tree_node('D');
    ptr = create_tree_node('*');
    ptr->left_child = ptr1;
    ptr->right_child = ptr2;

    ptr1 = ptr;
    ptr2 = create_tree_node('E');
    ptr = create_tree_node('+');
    ptr->left_child = ptr1;
    ptr->right_child = ptr2;

    /* call traversal functions */
    printf("recursive inorder\n");
    recursive_inorder(ptr);
    printf("\n");

    printf("iterative inorder\n");
    iter_inorder(ptr);
    printf("\n");

    printf("iterative preorder\n");
    iter_preorder(ptr);
    printf("\n");

    printf("iterative postorder\n");
    iter_postorder(ptr);
    printf("\n");

    printf("iterative level order\n");
    level_order(ptr);
    printf("\n");
}

tree_pointer create_tree_node(char data) {
    tree_pointer ptr = (tree_pointer)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->left_child = NULL;
    ptr->right_child = NULL;
    return ptr;
}

void recursive_inorder(tree_pointer ptr) {
    if (ptr) {
        recursive_inorder(ptr->left_child);
        printf("%c ", ptr->data);
        recursive_inorder(ptr->right_child);
    }
}

void iter_inorder(tree_pointer root) {
    tree_pointer stack[MAX_STACK_SIZE], ptr = root;
    int top = -1; // intialize stack

    ptr = root;
    /* Loop while nodes remain to be visited or backtracked. */
    while (ptr || top > -1) {
        for (; ptr; ptr = ptr->left_child)
            add(stack, &top, ptr);
        ptr = delete(stack, &top);
        printf("%c ", ptr->data);
        ptr = ptr->right_child;
    }
}

void iter_preorder(tree_pointer root) {
    // TODO
    tree_pointer stack[MAX_STACK_SIZE], ptr = root;
    int top = -1; // initialize stack

    ptr = root;

    while (ptr || top > -1) {
        for (; ptr; ptr = ptr->left_child) {
            printf("%c ", ptr->data);
            add(stack, &top, ptr);
        }
        ptr = delete(stack, &top);
        ptr = ptr->right_child;
    }
}

void iter_postorder(tree_pointer root) {
    // TODO
    tree_pointer stack[MAX_STACK_SIZE], ptr = root, visited = NULL;
    int top = -1;

    while (ptr || top > -1) {
        for (; ptr; ptr = ptr->left_child)
            add(stack, &top, ptr);
        ptr = stack[top];
        if (!ptr->right_child || ptr->right_child == visited) {
            printf("%c ", ptr->data);
            visited = delete(stack, &top);
            ptr = NULL;
        } else {
            ptr = ptr->right_child;
        }
    }
}

void level_order(tree_pointer root) {
    // TODO
    tree_pointer queue[MAX_QUEUE_SIZE], ptr = root;
    int front = 0, rear = 0;
    
    if (!ptr) return;  // tree is empty
    addq(queue, front, &rear, ptr);
    while (front != rear) {  // queue is not empty
        ptr = deleteq(queue, &front, rear);
        printf("%c ", ptr->data);
        if (ptr->left_child)
            addq(queue, front, &rear, ptr->left_child);
        if (ptr->right_child) 
            addq(queue, front, &rear, ptr->right_child);
    }

}

/* TODO: add function implementations here */
/* if stack full, output error and exit */
void add(tree_pointer* stack, int* top, tree_pointer node) {
    if (*top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "no more space in the stack\n");
        exit(1);
    }
    stack[++(*top)] = node;
}
/* if stack empty, return NULL */
tree_pointer delete(tree_pointer* stack, int* top) {
    if (*top < 0) {
        return NULL;
    }
    return stack[(*top)--];
}
/* if queue full, output error and exit */
void addq(tree_pointer* queue, int front, int* rear, tree_pointer node) {
    if ((*rear + 1) % MAX_QUEUE_SIZE == front) {
        fprintf(stderr, "no more space in the queue\n");
        exit(1);
    }
    *rear = (*rear + 1) % MAX_QUEUE_SIZE;
    queue[*rear] = node;
}
/* if queue empty, return NULL */
tree_pointer deleteq(tree_pointer* queue, int* front, int rear) {
    if (*front == rear) {
        return NULL;
    }
    *front = (*front + 1) % MAX_QUEUE_SIZE;
    tree_pointer node = queue[*front];
    return node;
}