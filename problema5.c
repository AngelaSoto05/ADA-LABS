#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

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

static int cnt;
static int sangria;
int pre[1000];

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

static void dfsR(Graph G, vertex v) 
{ 
    for (int i = 0; i < sangria; i++) // Imprime la entrada con sangría
        printf(" ");
    printf("%d-%d dfsR(G,%d)\n", sangria, sangria, v);
    
    sangria++;  // Incrementar al ENTRAR en la recursión
    pre[v] = cnt++; 
    
    for (link a = G->adj[v]; a != NULL; a = a->next) { 
        vertex w = a->w; 
        if (pre[w] == -1) 
            dfsR(G, w); 
    } 
    
    sangria--; // Decrementar al SALIR de la recursión
    
    for (int i = 0; i < sangria; i++)  // Imprimie la salida con sangría
        printf(" ");
    printf("%d\n", v);
}

void GRAPHdfs(Graph G) 
{ 
    cnt = 0;
    sangria = 0; // Inicializa la sangría
    
    for (vertex v = 0; v < G->V; ++v) 
        pre[v] = -1; 
    
    for (vertex v = 0; v < G->V; ++v) 
        if (pre[v] == -1) {
            dfsR(G, v); // comienza nueva etapa
            printf("\n"); // Línea en blanco entre etapas
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

void imprimirPre(Graph G) {
    printf("\nVector pre[]:\n");
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
    if (argc < 2) {
        printf("Uso: %s <archivo_de_grafo>\n", argv[0]);
        printf("\nEjemplo de formato del archivo:\n");
        printf("7\n");
        printf("0 1 6\n");
        printf("1 0 6 3\n");
        printf("2 4\n");
        printf("3 1\n");
        printf("4 2\n");
        printf("5\n");
        printf("6 0 1\n");
        return 1;
    }
    
    Graph G = leerGrafoDesdeArchivo(argv[1]);
    if (G == NULL) {
        return 1;
    }
    
    printf("Grafo con %d vértices y %d aristas\n\n", G->V, G->A);
    printf("Rastreo de DFS:\n");
    
    GRAPHdfs(G);
    
    imprimirPre(G);
    
    GRAPHdestroy(G);
    
    return 0;
}