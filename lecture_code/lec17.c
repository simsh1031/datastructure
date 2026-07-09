typedef struct {
    int key;
} element;

struct node {
    element data;
    struct node *leftChild, *rightChild;
};

typedef struct node *treePointer;

element *iterSearch(treePointer tree, int k) {
    while(tree) {
        if(k == tree->data.key) {
            return &(tree->data);
        }
        if(k < tree->data.key) {
            tree = tree->leftChild;
        } else {
            tree = tree->rightChild;
        }
    }
    return NULL;
}

void insertNode(treePointer *node, int k) {
    treePointer ptr, temp = modifiedSearch(*node, k);
    if(temp || !(*node)) {
        ptr = (treePointer)malloc(sizeof(struct node));
        ptr->data.key = k;
        ptr->leftChild = ptr->rightChild = NULL;
        if(*node) {
            if (k<temp->data.key) {
                temp->leftChild = ptr;
            } else {
                temp->rightChild = ptr;
            }
        } else {
            *node = ptr;
        }
    }
}

treePointer modifiedSearch(treePointer node, int k) {
    treePointer parent = NULL;
    while (node) {
        if(k == node->data.key) {
            return NULL;
        }
        parent = node;
        if(k < node->data.key) {
            node = node->leftChild;
        } else {
            node = node->rightChild;
        }
    }
    return parent;
}

void deleteNode(treePointer *node, int k)