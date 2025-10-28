#include <iostream>
using namespace std;

#define MAXV 10    // número de vértices
#define MAXSTACK 1000

// ---------------------- PILA (STACK.h) ----------------------
int stack[MAXSTACK];
int top = -1;

void STACKinit(int n) { top = -1; }          // inicializa la pila
void STACKpush(int v) { stack[++top] = v; }  // inserta elemento
int  STACKpop() { return stack[top--]; }     // saca elemento
int  STACKempty() { return (top == -1); }    // verifica si está vacía

// ---------------------- GRAFO ----------------------
struct Graph {
    int V;               // cantidad de vértices
    int adj[MAXV][MAXV]; // matriz de adyacencia
};

static int cnt, pre[1000]; // contadores y marcas

// ---------------------- DFS ITERATIVO ----------------------
void dfs(Graph G, int v) {
    pre[v] = cnt++;
    STACKpush(v);

    while (!STACKempty()) {
        v = STACKpop();
        for (int w = 0; w < G.V; ++w)
            if (G.adj[v][w] == 1)
                if (pre[w] == -1) {
                    pre[w] = cnt++;
                    STACKpush(w);
                }
    }
}

// ---------------------- DFS PRINCIPAL ----------------------
void GRAPHdfs(Graph G) {
    STACKinit(G.V);
    cnt = 0;
    for (int v = 0; v < G.V; ++v) pre[v] = -1;
    for (int v = 0; v < G.V; ++v)
        if (pre[v] == -1)
            dfs(G, v);
}

// ---------------------- MAIN ----------------------
int main() {
    Graph G;
    G.V = 10;

    // Inicializar matriz
    for (int i = 0; i < G.V; i++)
        for (int j = 0; j < G.V; j++)
            G.adj[i][j] = 0;

    // Aristas no dirigidas
    int edges[][2] = {
        {3,7},{1,4},{7,8},{0,5},{5,2},
        {3,8},{2,9},{0,6},{4,9},{2,6},{6,4}
    };

    for (auto &e : edges) {
        int u = e[0], v = e[1];
        G.adj[u][v] = G.adj[v][u] = 1;
    }

    GRAPHdfs(G);

    cout << "Orden de visita (pre[v]):\n";
    for (int v = 0; v < G.V; ++v)
        cout << "Vertice " << v << " -> pre = " << pre[v] << endl;

    return 0;
}
