#include <stdio.h>
#include <stdlib.h>

#define MAX 30

struct Edge
{
    int src, dest, weight;
};

struct Graph
{
    int V, E;
    struct Edge *edges;
};

struct Subset
{
    int parent;
    int rank;
};

struct Graph *createGraph(int V, int E)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge *)malloc(E * sizeof(struct Edge));
    return graph;
}

int find(struct Subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(struct Subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int compareEdges(const void *a, const void *b)
{
    return ((struct Edge *)a)->weight - ((struct Edge *)b)->weight;
}

void KruskalMST(struct Graph *graph)
{
    int V = graph->V;
    struct Edge result[MAX];
    int e = 0;
    int i = 0;

    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compareEdges);

    struct Subset *subsets = (struct Subset *)malloc(V * sizeof(struct Subset));

    for (int v = 0; v < V; v++)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E)
    {
        struct Edge next_edge = graph->edges[i++];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y)
        {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    printf("\nMinimum Spanning Tree:\n");
    int minimumCost = 0;
    for (i = 0; i < e; i++)
    {
        printf("Edge %d-%d: Weight %d\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("Total Cost of MST: %d\n", minimumCost);

    free(subsets);
}

int main()
{
    int V, E;

    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    struct Graph *graph = createGraph(V, E);

    printf("Enter edge details (source destination weight):\n");
    for (int i = 0; i < E; i++)
    {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &graph->edges[i].src, &graph->edges[i].dest, &graph->edges[i].weight);
    }

    KruskalMST(graph);

    free(graph->edges);
    free(graph);
    return 0;
}