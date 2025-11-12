#include <stdio.h>
#include <stdbool.h>

#define V 6

void topoSortUtil(int v, bool visited[], int stack[], int *top, int graph[V][V]) {
    visited[v] = true;

    for (int i = 0; i < V; i++) {
        if (graph[v][i] && !visited[i]) {
            topoSortUtil(i, visited, stack, top, graph);
        }
    }

    stack[++(*top)] = v;
}

void topologicalSort(int graph[V][V]) {
    bool visited[V] = {false};
    int stack[V], top = -1;

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            topoSortUtil(i, visited, stack, &top, graph);
    }

    printf("Topological Sort Order: ");
    while (top >= 0)
        printf("%d ", stack[top--]);
    printf("\n");
}

int main() {
    int graph[V][V] = {
        {0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0}
    };

    topologicalSort(graph);

    return 0;
}
