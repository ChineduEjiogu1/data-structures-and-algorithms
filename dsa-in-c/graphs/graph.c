#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// --- Structures ---
typedef struct Vertex Vertex;

typedef struct AdjacencyNode {
    Vertex *vertex;
    struct AdjacencyNode *next;
} AdjacencyNode;

struct Vertex {
    char *id;
    AdjacencyNode *adj_list;
};

typedef struct {
    Vertex **vertices;
    int vertex_count;
    int capacity;
} Graph;

// --- Helper Functions ---
Vertex *create_vertex(const char *id) {
    Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));
    vertex->id = strdup(id);
    vertex->adj_list = NULL;
    return vertex;
}

AdjacencyNode *create_adjacency_node(Vertex *vertex) {
    AdjacencyNode *node = (AdjacencyNode *)malloc(sizeof(AdjacencyNode));
    node->vertex = vertex;
    node->next = NULL;
    return node;
}

Graph *create_graph(int capacity) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertices = (Vertex **)malloc(sizeof(Vertex *) * capacity);
    graph->vertex_count = 0;
    graph->capacity = capacity;
    return graph;
}

Vertex *get_vertex(Graph *graph, const char *id) {
    for (int i = 0; i < graph->vertex_count; i++) {
        if (strcmp(graph->vertices[i]->id, id) == 0) {
            return graph->vertices[i];
        }
    }
    return NULL;
}

void insert_vertex(Graph *graph, const char *id) {
    if (graph->vertex_count == graph->capacity) {
        printf("Graph capacity exceeded!\n");
        return;
    }
    if (get_vertex(graph, id)) {
        printf("Vertex %s already exists!\n", id);
        return;
    }
    graph->vertices[graph->vertex_count++] = create_vertex(id);
}

void insert_edge(Graph *graph, const char *src_id, const char *dest_id) {
    Vertex *src = get_vertex(graph, src_id);
    Vertex *dest = get_vertex(graph, dest_id);

    if (!src || !dest) {
        printf("One or both vertices not found!\n");
        return;
    }

    AdjacencyNode *new_node = create_adjacency_node(dest);
    new_node->next = src->adj_list;
    src->adj_list = new_node;
}

void print_graph(Graph *graph) {
    for (int i = 0; i < graph->vertex_count; i++) {
        Vertex *vertex = graph->vertices[i];
        printf("%s ->", vertex->id);

        AdjacencyNode *adj = vertex->adj_list;
        while (adj) {
            printf(" %s", adj->vertex->id);
            adj = adj->next;
        }
        printf("\n");
    }
}

void free_graph(Graph *graph) {
    for (int i = 0; i < graph->vertex_count; i++) {
        Vertex *vertex = graph->vertices[i];

        AdjacencyNode *adj = vertex->adj_list;
        while (adj) {
            AdjacencyNode *temp = adj;
            adj = adj->next;
            free(temp);
        }

        free(vertex->id);
        free(vertex);
    }
    free(graph->vertices);
    free(graph);
}

// --- BFS Function ---
void bfs(Graph *graph, const char *start_key) {
    Vertex *start_vertex = get_vertex(graph, start_key);
    if (!start_vertex) {
        printf("Start vertex not found!\n");
        return;
    }

    bool visited[graph->vertex_count];
    for (int i = 0; i < graph->vertex_count; i++) {
        visited[i] = false;
    }

    Vertex *queue[graph->vertex_count];
    int front = 0, rear = 0;

    queue[rear++] = start_vertex;
    visited[start_vertex - graph->vertices[0]] = true;

    printf("BFS Traversal: ");

    while (front < rear) {
        Vertex *current = queue[front++];
        printf("%s ", current->id);

        AdjacencyNode *adj = current->adj_list;
        while (adj) {
            Vertex *neighbor = adj->vertex;
            int index = neighbor - graph->vertices[0];
            if (!visited[index]) {
                queue[rear++] = neighbor;
                visited[index] = true;
            }
            adj = adj->next;
        }
    }

    printf("\n");
}

// --- DFS Functions ---
void dfs_util(Vertex *vertex, bool visited[], Graph *graph) {
    int index = vertex - graph->vertices[0];
    visited[index] = true;
    printf("%s ", vertex->id);

    AdjacencyNode *adj = vertex->adj_list;
    while (adj) {
        Vertex *neighbor = adj->vertex;
        int neighbor_index = neighbor - graph->vertices[0];
        if (!visited[neighbor_index]) {
            dfs_util(neighbor, visited, graph);
        }
        adj = adj->next;
    }
}

void dfs(Graph *graph, const char *start_key) {
    Vertex *start_vertex = get_vertex(graph, start_key);
    if (!start_vertex) {
        printf("Start vertex not found!\n");
        return;
    }

    bool visited[graph->vertex_count];
    for (int i = 0; i < graph->vertex_count; i++) {
        visited[i] = false;
    }

    printf("DFS Traversal: ");
    dfs_util(start_vertex, visited, graph);
    printf("\n");
}

// --- Main Function ---
int main() {
    Graph *graph = create_graph(10);

    insert_vertex(graph, "A");
    insert_vertex(graph, "B");
    insert_vertex(graph, "C");
    insert_vertex(graph, "D");

    insert_edge(graph, "A", "B");
    insert_edge(graph, "A", "C");
    insert_edge(graph, "B", "D");

    print_graph(graph);

    bfs(graph, "A");
    dfs(graph, "A");

    free_graph(graph);
    return 0;
}