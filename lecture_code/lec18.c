int simpleFind(int i) {
    for (; parent[i] >= 0; i = parent[i])
        ;
    return i;
}

int simpleUnion(int i, int j) {
    parent[i] = j;
}

void weightedUnion(int i, int j) {
    int temp = parent[i] + parent[j];
    if(parent[i] > parent[j]) {
        parent[i] = j;
        parent[j] = temp;
    } else {
        parent[j] = i;
        parent[i] = temp;
    }
}

int collaspingFind(int i) {
    int root, trail, lead;
    for (root = i; parent[root] >= 0; root = parent[root])
        ;
    for (trail = i; trail != root; trail = lead) {
        lead = parent[trail];
        parent[trail] = root;
    }
    return root;
}