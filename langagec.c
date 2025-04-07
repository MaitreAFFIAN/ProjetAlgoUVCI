#include <stdio.h>
#include <stdlib.h>

// Structure pour les attributs d’une arête (vous pouvez la supprimer si vous n'en avez pas besoin)
typedef struct EdgeAttr {
    float distance;
    float baseTime;
    float cost;
    int roadType;
    float reliability;
    int restrictions;
} EdgeAttr;

// Structure pour un noeud de la liste d’adjacence
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

// Structure pour une liste d’adjacence
typedef struct AdjList {
    AdjListNode* head;
} AdjList;

// Structure pour le graphe
typedef struct Graph {
    int V;          // Nombre de sommets
    AdjList* array; // Tableau de listes d'adjacence
} Graph;

// Déclaration des fonctions
AdjListNode* createAdjListNode(int dest);
Graph* createGraph(int V);
void addEdge(Graph* graph, int src, int dest);
void printGraph(Graph* graph);
void freeGraph(Graph* graph);

// Programme principal
int main() {
    Graph* graph = createGraph(9);

    // Ajout des arêtes
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 0);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 5);
    addEdge(graph, 2, 4);
    addEdge(graph, 2, 6);
    addEdge(graph, 3, 0);
    addEdge(graph, 4, 3);
    addEdge(graph, 7, 4);
    addEdge(graph, 7, 6);

    // Afficher le graphe
    printGraph(graph);

    // Libérer la mémoire
    freeGraph(graph);
    return 0;
}

// Crée un nouveau noeud de la liste d’adjacence
AdjListNode* createAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (!newNode) {
        printf("Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Crée un graphe avec V sommets
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        printf("Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    if (!graph->array) {
        printf("Erreur d'allocation de mémoire\n");
        free(graph);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < V; i++) {
        graph->array[i].head = NULL;
    }
    return graph;
}

// Ajoute une arête (non orientée ici, comme sur le schéma)
void addEdge(Graph* graph, int src, int dest) {
    // Ajout d'une arête de src à dest
    AdjListNode* newNode = createAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Ajout d'une arête de dest à src (puisque le graphe est non orienté)
    newNode = createAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Affiche la liste d’adjacence
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        printf("Sommet %d:", i + 1);
        AdjListNode* temp = graph->array[i].head;
        while (temp) {
            printf(" -> %d", temp->dest + 1);
            temp = temp->next;
        }
        printf(" -> NULL\n");
    }
}

// Libère la mémoire allouée pour le graphe
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        AdjListNode* temp = graph->array[i].head;
        while (temp) {
            AdjListNode* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->array);
    free(graph);
}