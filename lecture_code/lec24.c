void allCosts(int cost[][MAX_VERTICES], int distance[][MAX_VERTICES], int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n;j++) {
            distance[i][j] = cost[i][j];
        }
    }
    for (k = 0; k < n;k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if(distance[i][k] + distance[k][j] < distance[i][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }
}

void transitiveClosure(int cost[][MAX_VERTICES], int distance[][MAX_VERTICES], int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            distance[i][j] = cost[i][j];
        }
    }

    for (k = 0; k < n;k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                distance[i][j] = distance[i][j] || (distance[i][k] && distance[k][j]);
            }
        }
    }
}