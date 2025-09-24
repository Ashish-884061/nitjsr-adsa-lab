#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

int n;                 
int adj[MAX][MAX];     
int visited[MAX], stack[MAX];
int top = -1;

int minCycle = INT_MAX;
int maxCycle = -1;

void push(int v) {
    stack[++top] = v;
}

void pop() {
    top--;
}

int isInStack(int v) {
    for (int i = 0; i <= top; i++) {
        if (stack[i] == v) return i; 
    }
    return -1;
}

void DFS(int u, int parent, int directed) {
    visited[u] = 1;
    push(u);

    for (int v = 0; v < n; v++) {
        if (adj[u][v]) {
            if (!visited[v]) {
                DFS(v, u, directed);
            } else {
                int idx = isInStack(v);
                if (idx != -1) {
                    int cycleLen = top - idx + 1;
                    if (cycleLen < minCycle) minCycle = cycleLen;
                    if (cycleLen > maxCycle) maxCycle = cycleLen;
                }
            }
        }
    }

    pop();
    visited[u] = 0;
}

void findCycles(int directed) {
    for (int i = 0; i < n; i++) {
        DFS(i, -1, directed);
    }

    if (minCycle == INT_MAX) {
        printf("No cycles found.\n");
    } else {
        printf("Smallest cycle length = %d\n", minCycle);
        printf("Largest cycle length = %d\n", maxCycle);
    }
}

int main() {
    int edges, u, v, directed;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter 1 for directed graph, 0 for undirected: ");
    scanf("%d", &directed);

    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        if (!directed) adj[v][u] = 1;
    }

    findCycles(directed);

    return 0;
}
