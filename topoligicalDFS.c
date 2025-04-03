#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

void dfs(int node, int visited[], int stack[], int *stackIndex, int V, int adj[MAX_NODES][MAX_NODES])
{
    visited[node] = 1;

    for (int i = 0; i < V; i++)
    {
        if (adj[node][i] && !visited[i])
        {
            dfs(i, visited, stack, stackIndex, V, adj);
        }
    }

    stack[(*stackIndex)++] = node;
}

void topologicalSortDFS(int V, int adj[MAX_NODES][MAX_NODES])
{
    int visited[MAX_NODES] = {0}, stack[MAX_NODES], stackIndex = 0;

    for (int i = 0; i < V; i++)
        if (!visited[i])
            dfs(i, visited, stack, &stackIndex, V, adj);

    printf("Topological Order: ");
    while (stackIndex > 0)
        printf("%d ", stack[--stackIndex]);
    printf("\n");
}

int main()
{
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    int adj[MAX_NODES][MAX_NODES] = {0};

    printf("Enter the directed edges (from -> to):\n");
    for (int i = 0; i < E; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
    }

    topologicalSortDFS(V, adj);
    return 0;
}
