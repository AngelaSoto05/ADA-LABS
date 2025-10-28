#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int w;
    struct node *next;
} *link;

typedef struct {
    int V;
    int A;
    link *adj;  
} *Graph;

typedef int vertex;

// Estructura para la pila
typedef struct stackNode {
    vertex v;
    struct stackNode *next;
} *Stack;

static int cnt;
int pre[1000];

Stack stackInit() {
    return NULL;
}

int stackEmpty(Stack s) {
    return s == NULL;
}

Stack stackPush(Stack s, vertex v) {
    Stack new = malloc(sizeof(*new));
    new->v = v;
    new->next = s;
    return new;
}

vertex stackPop(Stack *s) {
    if (*s == NULL) return -1;
    Stack temp = *s;
    vertex v = temp->v;
    *s = temp->next;
    free(temp);
    return v;
}

void stackFree(Stack s) {
    while (!stackEmpty(s)) {
        stackPop(&s);
    }
}

link newNode(int w, link next) {
    link a = malloc(sizeof(*a));
    a->w = w;
    a->next = next;
    return a;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof(*G));
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));
    for (vertex v = 0; v < V; v++)
        G->adj[v] = NULL;
    return G;
}

void GRAPHinsertArc(Graph G, vertex v, vertex w) {
    G->adj[v] = newNode(w, G->adj[v]);
    G->A++;
}

// VERSIÓN ITERATIVA DE DFS
static void dfsIterativo(Graph G, vertex v) {
    Stack s = stackInit();
    s = stackPush(s, v);
    
    while (!stackEmpty(s)) {
        vertex atual = stackPop(&s);
        // Si ya fue visitado, continuar
        if (pre[atual] != -1)
            continue;
        pre[atual] = cnt++; // Marcar como visitado
        printf("Visitando vértice: %d (pre[%d] = %d)\n", atual, atual, pre[atual]);
        
        // Agregar vecinos no visitados a la pila
        for (link a = G->adj[atual]; a != NULL; a = a->next) {
            vertex w = a->w;
            if (pre[w] == -1) {
                s = stackPush(s, w);
            }
        }
    }
    
    stackFree(s);
}

void GRAPHdfsIterativo(Graph G) {
    cnt = 0;
    
    for (vertex v = 0; v < G->V; ++v)
        pre[v] = -1;
    
    for (vertex v = 0; v < G->V; ++v) {
        if (pre[v] == -1) {
            printf("\n=== Nueva etapa desde vértice %d ===\n", v);
            dfsIterativo(G, v);
        }
    }
}

Graph leerGrafoDesdeArchivo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo %s\n", nombreArchivo);
        return NULL;
    }
    
    int V;
    fscanf(archivo, "%d", &V);
    
    Graph G = GRAPHinit(V);
    
    int v;
    while (fscanf(archivo, "%d", &v) == 1) {
        int w;
        while (fscanf(archivo, "%d", &w) == 1) {
            if (w == 0 && v == 0) break;
            GRAPHinsertArc(G, v, w);
        }
    }
    
    fclose(archivo);
    return G;
}

void imprimirGrafo(Graph G) {
    printf("Grafo con %d vértices y %d aristas:\n", G->V, G->A);
    for (vertex v = 0; v < G->V; v++) {
        printf("%d:", v);
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            printf(" %d", a->w);
        }
        printf("\n");
    }
}

void imprimirPre(Graph G) {
    printf("\nVector pre[] (orden de descubrimiento):\n");
    for (vertex v = 0; v < G->V; v++) {
        printf("pre[%d] = %d\n", v, pre[v]);
    }
}

void GRAPHdestroy(Graph G) {
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

int main(int argc, char *argv[]) {    
    Graph G = leerGrafoDesdeArchivo(argv[1]);
    if (G == NULL) {
        return 1;
    }
    
    imprimirGrafo(G);

    printf("Ejecutando DFS Iterativo:\n");
    
    GRAPHdfsIterativo(G);
    
    imprimirPre(G);
    
    GRAPHdestroy(G);
    
    return 0;
}