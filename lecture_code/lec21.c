#define MIN2(x, y) ((x) < (y) ? (x) : (y))
#define MAX_VERTICES 200
short int dfn[MAX_VERTICES];
short int low[MAX_VERTICES];
int num;

void init(void) {
    for (int i = 0; i < n; i++) {
        dfn[i] = low[i] = -1;
    }
    num = 0;
}

void dfnlow(int u, int v) {
    nodePointer ptr;
    int w;
    dfn[u] = low[u] = num++;
    for (ptr = graph[u]; ptr; ptr = ptr->link) {
        w = ptr->vertex;
        if(dfn[u] == -1) {
            dfnlow(w, u);
            low[u] = MIN2(low[u], low[w]);
        } else if (w != v) {
            low[u] = MIN2(low[u], low[w]);
        }
    }
}