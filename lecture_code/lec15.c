struct node {
    char data;
    struct node *left_child, *right_child;
};
typedef struct node *tree_pointer;

tree_pointer copy(tree_pointer original) {
    tree_pointer temp;
    if(original) {
        temp = malloc(sizeof(struct node));
        if (IS_FULL(temp)) {
            fprintf(stderr, "The memory is full\n");
            exit(1);
        }
        temp->left_child = original->left_child;
        temp->right_child = original->right_child;
        temp->data = original->data;
        return temp;
    }
    return NULL;
}

int equal(tree_pointer first, tree_pointer second) {
    return (
        (!first && !second) ||
        (first && second &&
         (first->data == second->data) &&
         equal(first->left_child, second->left_child) &&
         equal(first->right_child, second->right_child))
    );
}

#define TRUE 1
#define FALSE 0

typedef enum
{
    NOT,
    AND,
    OR,
    T,
    F
} logical;
struct node {
    struct node *left_child;
    logical data;
    short int value;
    struct node *right_child;
};
typedef struct node *tree_pointer;

void post_order_eval(tree_pointer node) {
    if(node) {
        post_order_eval(node->left_child);
        post_order_eval(node->right_child);
        switch(node->data) {
            case NOT:
                node->value = !node->right_child->value;
                break;
            case AND:
                node->value = node->right_child->value && node->left_child->value;
                break;
            case OR:
                node->value = node->right_child->value || node->left_child->value;
                break;
            case T:
                node->value = TRUE;
                break;
            case F:
                node->value = FALSE;
        }
    }
}

void generateTree() {
    int iter = 0;
    treePointer ptr, lptr, rptr;
    while(exprpost[iter] != '\0') {
        char tok = exprpost[iter];
        ptr = malloc(sizeof(struct node));
        if(tok == '&') {
            rptr = tpop();
            lptr = tpop();
            ptr->variable = tok;
            ptr->data = AND;
            ptr->value = FALSE;
            ptr->leftChild = lptr;
            ptr->rightChild = rptr;
            tpush(ptr);
        }
        else if(tok == '|') {
            rptr = tpop();
            lptr = tpop();
            ptr->variable = tok;
            ptr->data = OR;
            ptr->value = FALSE;
            ptr->leftChild = lptr;
            ptr->rightChild = rptr;
            tpush(ptr);
        }
        else if(tok == '~') {
            rptr = tpop();
            ptr->variable = tok;
            ptr->data = OR;
            ptr->value = FALSE;
            ptr->leftChild = NULL;
            ptr->rightChild = rptr;
            tpush(ptr);
        }
        else {
            ptr->variable = tok;
            ptr->data = F;
            ptr->value = FALSE;
            ptr->leftChild = NULL;
            ptr->rightChild = NULL;
            tpush(ptr);
        }
        iter++;
    }
    binaryTree = tpop();
}

struct threaded_tree {
    short int left_thread;
    struct threaded_tree *left_child;
    char data;
    short int right_thread;
    struct threaded_tree *right_child;
};
typedef struct threaded_tree *threaded_pointer;

threaded_pointer insucc(threaded_pointer tree) {
    threaded_pointer temp;
    temp = tree->right_child;
    if(!tree->right_thread) {
        while(!temp->left_thread) {
            temp = temp->left_child;
        }
    }
    return temp;
}

void tinorder(threaded_pointer tree) {
    threaded_pointer temp = tree;
    for (;;) {
        temp = insucc(temp);
        if(temp == tree) {
            break;
        }
        printf("%3c", temp->data);
    }
}

void insert_right(threaded_pointer parent, threaded_pointer child) {
    threaded_pointer temp;
    child->right_child = parent->right_child;
    child->right_thread = parent->right_thread;
    child->left_child = parent;
    child->left_thread = TRUE;
    parent->right_child = child;
    parent->right_thread = FALSE;
    if(!child->right_thread) {
        temp = insucc(child);
        temp->left_child = child;
    }
}