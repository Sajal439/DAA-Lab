#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct
{
    int V;
    int adj[MAX_VERTICES][MAX_VERTICES];
} Graph;

void initGraph(Graph *g, int vertices)
{
    g->V = vertices;
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            g->adj[i][j] = 0;
        }
    }
}

void addEdge(Graph *g, int u, int v)
{
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}

void dfs(Graph *g, int v, int visited[])
{
    visited[v] = 1;
    for (int i = 0; i < g->V; i++)
    {
        if (g->adj[v][i] == 1 && !visited[i])
        {
            dfs(g, i, visited);
        }
    }
}

int isConnected(Graph *g)
{
    int visited[MAX_VERTICES] = {0};
    int startVertex = -1;

    for (int i = 0; i < g->V; i++)
    {
        for (int j = 0; j < g->V; j++)
        {
            if (g->adj[i][j] == 1)
            {
                startVertex = i;
                break;
            }
        }
        if (startVertex != -1)
            break;
    }

    if (startVertex == -1)
    {
        return 0;
    }

    dfs(g, startVertex, visited);

    for (int i = 0; i < g->V; i++)
    {
        for (int j = 0; j < g->V; j++)
        {
            if (g->adj[i][j] == 1 && !visited[i])
            {
                return 0;
            }
        }
    }

    return 1;
}

int main()
{
    int vertices, edges, u, v;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    Graph g;
    initGraph(&g, vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (u v):\n");
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d", &u, &v);
        addEdge(&g, u, v);
    }

    if (isConnected(&g))
        printf("Graph is Connected\n");
    else
        printf("Graph is Disconnected\n");

    return 0;
}
