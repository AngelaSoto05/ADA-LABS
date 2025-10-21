#include <stdio.h>
#include <stdlib.h>

/* Vértices de grafos son representados por objetos del tipo vértice. */
#define vertex int

/* La lista de adyacencia de un vértice v está formada por nodos de tipo nodo. */
typedef struct node *link;
struct node { 
    vertex w; 
    link next; 
};

/* REPRESENTACIÓN POR LISTAS DE ADYACENCIA */
struct graph { 
    int V; 
    int A; 
    link *adj; 
};
typedef struct graph *Graph;

/* Función NEWnode corregida */
static link NEWnode(vertex w, link next) { 
    link a = malloc(sizeof(struct node));
    a->w = w; 
    a->next = next; 
    return a; 
}

/* 1. Inicializar grafo */
Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof(*G));
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));
    for (vertex v = 0; v < V; ++v)
        G->adj[v] = NULL;
    return G;
}

/* 2. Insertar arco */
void GRAPHinsertArc(Graph G, vertex v, vertex w) {
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}

/* 3. Verificar si vértice es aislado */
int GRAPHisolated(Graph G, vertex v) {
    if (G->adj[v] != NULL) return 0;
    
    for (vertex u = 0; u < G->V; u++) {
        if (u == v) continue;
        for (link a = G->adj[u]; a != NULL; a = a->next) {
            if (a->w == v) return 0;
        }
    }
    return 1;
}

/* 4. Grado de salida */
int GRAPHoutdeg(Graph G, vertex v) {
    int count = 0;
    for (link a = G->adj[v]; a != NULL; a = a->next)
        count++;
    return count;
}

/* 5. Grado de entrada */
int GRAPHindeg(Graph G, vertex v) {
    int count = 0;
    for (vertex u = 0; u < G->V; u++) {
        for (link a = G->adj[u]; a != NULL; a = a->next) {
            if (a->w == v) count++;
        }
    }
    return count;
}

/* 6. Verificar adyacencia */
int GRAPHisAdjacent(Graph G, vertex v, vertex w) {
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        if (a->w == w) return 1;
    }
    return 0;
}

/* 7. Mostrar grafo */
void GRAPHshow(Graph G) {
    printf("Grafo con %d vértices y %d arcos:\n", G->V, G->A);
    for (vertex v = 0; v < G->V; v++) {
        printf("%d: ", v);
        for (link a = G->adj[v]; a != NULL; a = a->next)
            printf("%d ", a->w);
        printf("\n");
    }
}

/* 8. Eliminar arco */
void GRAPHremoveArc(Graph G, vertex v, vertex w) {
    link prev = NULL;
    link current = G->adj[v];
    
    while (current != NULL && current->w != w) {
        prev = current;
        current = current->next;
    }
    
    if (current != NULL) {
        if (prev == NULL)
            G->adj[v] = current->next;
        else
            prev->next = current->next;
        free(current);
        G->A--;
    }
}

/* 9. Verificar si es no dirigido */
int GRAPHundir(Graph G) {
    for (vertex v = 0; v < G->V; v++) {
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            vertex w = a->w;
            int found = 0;
            
            for (link b = G->adj[w]; b != NULL; b = b->next) {
                if (b->w == v) {
                    found = 1;
                    break;
                }
            }
            
            if (!found) return 0;
        }
    }
    return 1;
}

/* 10. Insertar arista (grafo no dirigido) */
void UGRAPHinsertEdge(Graph G, vertex v, vertex w) {
    if (!GRAPHisAdjacent(G, v, w)) {
        G->adj[v] = NEWnode(w, G->adj[v]);
        G->A++;
    }
    
    if (!GRAPHisAdjacent(G, w, v)) {
        G->adj[w] = NEWnode(v, G->adj[w]);
        G->A++;
    }
}

/* 11. Eliminar arista (grafo no dirigido) */
void UGRAPHremoveEdge(Graph G, vertex v, vertex w) {
    GRAPHremoveArc(G, v, w);
    GRAPHremoveArc(G, w, v);
}

/* 12. Grado máximo (grafo no dirigido) */
int UGRAPHmaxDegree(Graph G) {
    int max_deg = 0;
    for (vertex v = 0; v < G->V; v++) {
        int deg = GRAPHoutdeg(G, v);
        if (deg > max_deg)
            max_deg = deg;
    }
    return max_deg;
}

/* 13. Destruir grafo */
void GRAPHdestroy(Graph G) {
    if (G == NULL) return;
    
    for (vertex v = 0; v < G->V; v++) {
        link a = G->adj[v];
        while (a != NULL) {
            link temp = a;
            a = a->next;
            free(temp);
        }
    }
    free(G->adj);
    free(G);
}

/* FUNCIÓN PRINCIPAL CON PRUEBAS */
int main() {
    printf("=== PRUEBAS DE GRAFOS CON LISTAS DE ADYACENCIA ===\n\n");
    
    // Crear grafo de prueba
    Graph G = GRAPHinit(6);
    
    // Insertar arcos (ejemplo del laboratorio)
    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 0, 5);
    GRAPHinsertArc(G, 1, 0);
    GRAPHinsertArc(G, 1, 5);
    GRAPHinsertArc(G, 2, 4);
    GRAPHinsertArc(G, 3, 1);
    GRAPHinsertArc(G, 5, 3);
    
    printf("1. Grafo inicial:\n");
    GRAPHshow(G);
    printf("\n");
    
    printf("2. Grados de los vértices:\n");
    for (vertex v = 0; v < G->V; v++) {
        printf("Vértice %d - Grado entrada: %d, Grado salida: %d\n", 
               v, GRAPHindeg(G, v), GRAPHoutdeg(G, v));
    }
    printf("\n");
    
    printf("3. Vértices aislados:\n");
    for (vertex v = 0; v < G->V; v++) {
        if (GRAPHisolated(G, v))
            printf("Vértice %d es aislado\n", v);
    }
    printf("\n");
    
    printf("4. Verificar adyacencias:\n");
    printf("¿0 es adyacente a 1? %s\n", GRAPHisAdjacent(G, 0, 1) ? "Sí" : "No");
    printf("¿0 es adyacente a 3? %s\n", GRAPHisAdjacent(G, 0, 3) ? "Sí" : "No");
    printf("\n");
    
    printf("5. ¿El grafo es no dirigido? %s\n", GRAPHundir(G) ? "Sí" : "No");
    printf("\n");
    
    // Probar eliminación de arco
    printf("6. Eliminar arco 0-1:\n");
    GRAPHremoveArc(G, 0, 1);
    GRAPHshow(G);
    printf("\n");
    
    // Probar inserción de arista (hacer grafo no dirigido)
    printf("7. Insertar arista 0-1 (no dirigido):\n");
    UGRAPHinsertEdge(G, 0, 1);
    GRAPHshow(G);
    printf("¿Ahora es no dirigido? %s\n", GRAPHundir(G) ? "Sí" : "No");
    printf("\n");
    
    // Probar grado máximo
    printf("8. Grado máximo del grafo: %d\n", UGRAPHmaxDegree(G));
    printf("\n");
    
    // Probar eliminación de arista
    printf("9. Eliminar arista 0-1:\n");
    UGRAPHremoveEdge(G, 0, 1);
    GRAPHshow(G);
    printf("\n");
    
    // Liberar memoria
    GRAPHdestroy(G);
    
    printf("10. Grafo destruido correctamente.\n");
    
    // Crear un grafo no dirigido de prueba
    printf("\n11. Crear grafo no dirigido de prueba:\n");
    Graph G2 = GRAPHinit(4);
    UGRAPHinsertEdge(G2, 0, 1);
    UGRAPHinsertEdge(G2, 0, 2);
    UGRAPHinsertEdge(G2, 1, 3);
    UGRAPHinsertEdge(G2, 2, 3);
    
    GRAPHshow(G2);
    printf("¿Es no dirigido? %s\n", GRAPHundir(G2) ? "Sí" : "No");
    printf("Grado máximo: %d\n", UGRAPHmaxDegree(G2));
    
    GRAPHdestroy(G2);
    
    printf("\n=== TODAS LAS PRUEBAS COMPLETADAS ===\n");
    
    return 0;
}
