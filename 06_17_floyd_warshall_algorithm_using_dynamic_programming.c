#include <stdio.h>
#define INF 1000000

void floydWarshall(int V, int dist[V][V]) {
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

void printMatrix(int V, int dist[V][V]) {
    printf("Shortest distance matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            (dist[i][j] == INF) ? printf("INF ") : printf("%3d ", dist[i][j]);
        printf("\n");
    }
}

int main() {
    int V;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    int dist[V][V];
    printf("Enter adjacency matrix (use %d for INF):\n", INF);
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &dist[i][j]);

    floydWarshall(V, dist);
    printMatrix(V, dist);

    return 0;
}
