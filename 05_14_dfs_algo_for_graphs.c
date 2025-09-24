#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int time_counter = 0;
int disc[MAX], finish[MAX], visited[MAX];
int adj[MAX][MAX]; 
int n;         

void classifyEdge(int u, int v) {
    if (disc[v] == -1) {
        printf("Tree Edge: %d -> %d\n", u, v);
    } else if (finish[v] == -1) {
        printf("Back Edge: %d -> %d\n", u, v);
    } else if (disc[u] < disc[v]) {
        printf("Forward Edge: %d -> %d\n", u, v);
    } else {
        printf("Cross Edge: %d -> %d\n", u, v);
    }
}

void DFS_Visit(int u) {
    visited[u] = 1;
    disc[u] = ++time_counter;

    for (int v = 0; v < n; v++) {
        if (adj[u][v]) {
            if (disc[v] == -1) {
                classifyEdge(u, v);
                DFS_Visit(v);
            } else {
                classifyEdge(u, v);
            }
        }
    }

    finish[u] = ++time_counter;
}

void DFS() {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        disc[i] = -1;
        finish[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            DFS_Visit(i);
        }
    }
}

int main() {
    int edges, u, v;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v) format, 0-indexed:\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1; 
    }

    printf("\nDFS Edge Classification:\n");
    DFS();

    return 0;
}
