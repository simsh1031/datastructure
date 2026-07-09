// Binary Tree Representations
struct node {
    char data;
    struct node *left_child, *right_child;
};
typedef struct node *tree_pointer;

void inorder(tree_pointer ptr) {
    while(ptr) {
        inorder(ptr->left_child);
        printf("%c", ptr->data);
        inorder(ptr->right_child);
    }
}

void preorder(tree_pointer ptr) {
    while(ptr) {
        printf("%c", ptr->data);
        preorder(ptr->left_child);
        preorder(ptr->right_child);
    }
}

void postorder(tree_pointer ptr) {
    while(ptr) {
        postorder(ptr->left_child);
        postorder(ptr->right_child);
        printf("%c", ptr->data);
    }
}

#define MAX_STACK_SIZE 100
void iter_inorder(tree_pointer root) {
    tree_pointer stack[MAX_STACK_SIZE], ptr = root;
    int top = -1;
    while(ptr || top>-1) {
        for (; ptr; ptr=ptr->left_child){
            add(stack, &top, ptr);
        }
        ptr = delete(stack, &top);
        printf("%c", ptr->data);
        ptr = ptr->right_child;
    }
}

void iter_inorder2(tree_pointer root) {
    tree_pointer stack[MAX_STACK_SIZE], ptr = root;
    int top = -1;
    while(ptr || top>-1) {
        if(ptr) {
            add(stack, &top, ptr);
            ptr = ptr->left_child;
        } else {
            ptr = delete(stack, &top);
            printf("%c", ptr->data);
            ptr = ptr->right_child;
        }
    }
}

#define MAX_QUEUE_SIZE 100

void level_order(tree_pointer root) {
    tree_pointer queue[MAX_QUEUE_SIZE], ptr = root;
    int front = 0, rear = 0;
    if(!ptr) return;
    addq(queue, &front, &rear, ptr);
    while(front != rear) {
        ptr = deleteq(queue, &front);
        printf("%c", ptr->data);
        if(ptr->left_child){
            addq(queue, &front, &rear, ptr->left_child);
        }
        if(ptr->right_child){
            addq(queue, &front, &rear, ptr->right_child);
        }
    }
}