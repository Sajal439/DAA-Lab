#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

void topologicalSortBFS(int V, int adj[MAX_NODES][MAX_NODES])
{
    int inDegree[V], queue[MAX_NODES], front = 0, rear = 0;

    for (int i = 0; i < V; i++)
        inDegree[i] = 0;

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            if (adj[i][j])
                inDegree[j]++;

    for (int i = 0; i < V; i++)
        if (inDegree[i] == 0)
            queue[rear++] = i;

    int count = 0, topoOrder[MAX_NODES];

    while (front < rear)
    {
        int node = queue[front++];
        topoOrder[count++] = node;

        for (int i = 0; i < V; i++)
        {
            if (adj[node][i])
            {
                if (--inDegree[i] == 0)
                    queue[rear++] = i;
            }
        }
    }

    if (count != V)
    {
        printf("Graph has a cycle! Topological sorting not possible.\n");
        return;
    }

    printf("Topological Order: ");
    for (int i = 0; i < count; i++)
        printf("%d ", topoOrder[i]);
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

    topologicalSortBFS(V, adj);
    return 0;
}
