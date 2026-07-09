void dfs(int v) {
    nodePointer w;
    if(!visited[v]) {
        visited[v] = TRUE;
        printf("%5d", v);
        for (w = graph[v]; w; w = w->link) {
            dfs(w->vertex);
        }
    }
}

void iter_dfs(int v) {
    push(v);
    while(top){
        v = pop();
        if(!visited[v]) {
            visited[v] = TRUE;
            printf("%5d", v);
            for (nodePointer w = graph[v]; w; w = w->link) {
                push(w->vertex);
            }
        }
    }
}

void bfs(int v) {
    visited[v] = TRUE;
    printf("%5d", v);
    addq(v);
    while(front) {
        v = deleteq();
        for (nodePointer p = graph[v]; p; p = p->link) {
            int w = p->vertex;
            if(!visited[w]) {
                visited[w] = TRUE;
                printf("%5d", w);
                addq(w);
            }
        }
    }
}

void iter_bfs(int v) {
    addq(v);
    while(front) {
        v = deleteq();
        if(!visited[v]) {
            visited[v] = TRUE;
            printf("%5d", v);
            for (nodePointer w = graph[v]; w; w = w->link) {
                addq(w->vertex);
            }
        }
    }
}

int count_and_label(void) {
    int count = 0;
    for (int i = 0; i < NUM_VERTICES; i++) {
        if(!visited[i]) {
            count++;
            label_component(i, count);
        }
    }
    return count;
}

void label_componet(int v, int label) {
    push(v);
    while(top) {
        v = pop();
        if(!visited[v]) {
            visited[v] = TRUE;
            comp[v] = label;
            for (nodePointer w = graph[v]; w; w = w->link) {
                push(w->vertex);
            }
        }
    }
}