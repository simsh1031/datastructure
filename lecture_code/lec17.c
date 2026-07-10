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

/* delete the node whose key is k */
void deleteNode(treePointer *node, int k)
{
    treePointer parent = NULL;
    treePointer curr = *node;

    /* ---------- Case 1 : node does not exist ---------- */
    while (curr && curr->data.key != k) {
        parent = curr;

        if (k < curr->data.key)
            curr = curr->leftChild;
        else
            curr = curr->rightChild;
    }

    if (!curr)
        return;

    /* ---------- Case 4 : node has two children ---------- */
    if (curr->leftChild && curr->rightChild) {

        treePointer replaceParent = curr;
        treePointer replace = curr->leftChild;

        /* largest node in left subtree */
        while (replace->rightChild) {
            replaceParent = replace;
            replace = replace->rightChild;
        }

        /* copy key */
        curr->data = replace->data;

        /* now delete replacement node */
        parent = replaceParent;
        curr = replace;
    }

    /* ---------- Case 2 & 3 ---------- */

    treePointer child;

    if (curr->leftChild)
        child = curr->leftChild;
    else
        child = curr->rightChild;

    /* deleting root */
    if (parent == NULL)
        *node = child;

    /* left child of parent */
    else if (parent->leftChild == curr)
        parent->leftChild = child;

    /* right child of parent */
    else
        parent->rightChild = child;

    free(curr);
}