void shortestPath(int v, int cost[][MAX_VERTICES], int distance[], int n, short int found[]) {
    for (int i = 0; i < n; i++) {
        found[i] = FALSE;
        distance[i] = cost[v][i];
    }
    found[v] = TRUE;
    distance[v] = 0;
    for (int i = 0; i < n - 2; i++) {
        int u = choose(distance, n, found);
        found[u] = TRUE;
        for (int w = 0; w < n; w++) {
            if (!found[w]) {
                if (distance[u] + cost[u][w] < distance[w]) {
                    distance[w] = distance[u] + cost[u][w];
                }
            }
        }
    }
}

#include <limits.h>

int choose (int distance[], int n, short int found[]) {
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void BellmanFor (int n, int v) {
    for (int i = 0; i < n; i++) {
        dist[i] = length[v][i];
    }
    for (int k = 2; k <= n - 1; k++) {
        for (each u such that u!= v and u has at least one incoming edge) {
            for (each incoming edge <i, u>) {
                if (dist[u] > dist[i] + length[i][u]) {
                    dist[u] = dist[i] + length[i][u];
                }
            }
        }
    }
}