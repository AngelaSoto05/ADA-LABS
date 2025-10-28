#include <iostream>
using namespace std;

const int N = 10; // Nodos 0 al 9
int grafo[N][N];  // Matriz de adyacencia
int visitado[N];  // 0 = no visitado, 1 = visitado
int padre[N];     // Guarda el padre de cada nodo
int tiempo = 0;   // Contador para el seguimiento

void dfs(int v) {
    visitado[v] = 1;
    tiempo++;
    cout << "[" << tiempo << "] Descubro  el nodo " << v << endl;

    for (int u = 0; u < N; u++) {
        if (grafo[v][u]) { // hay arista
            if (!visitado[u]) {
                padre[u] = v;
                cout << "  Voy del nodo actual " << v << " al vecino visitado " << u   <<  endl;
                dfs(u);
            } else {
                cout << " Este numero -> " << u << " ya ha sido visitado\n";
            }
        }
    }

    tiempo++;
    cout << "[" << tiempo << "] Termino nodo " << v << endl;
}

void GRAPHdfs() {
    for (int i = 0; i < N; i++) visitado[i] = 0, padre[i] = -1;

    for (int v = 0; v < N; v++) {
        if (!visitado[v]) {
            cout << "\nInicio DFS desde el nodo " << v << ":\n";
            dfs(v);
        }
    }

    cout << "\n=== Arbol DFS (padres) ===\n";
    cout << "Nodo | Padre\n";
    cout << "-------------\n";
    for (int i = 0; i < N; i++) {
        cout << "  " << i << "   |  ";
        if (padre[i] == -1) cout << "-";
        else cout << padre[i];
        cout << endl;
    }
}

int main() {
    // Inicializamos matriz de adyacencia en 0
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grafo[i][j] = 0;

    // Agregamos las aristas (no dirigido)
    int aristas[][2] = {
        {3,7}, {1,4}, {7,8}, {0,5}, {5,2},
        {3,8}, {2,9}, {0,6}, {4,9}, {2,6}, {6,4}
    };

    int M = sizeof(aristas)/sizeof(aristas[0]);
    for (int i = 0; i < M; i++) {
        int a = aristas[i][0], b = aristas[i][1];
        grafo[a][b] = 1;
        grafo[b][a] = 1; // no dirigido
    }

    cout << " GRAFO DFS RASTREADO : \n";
    GRAPHdfs();

    return 0;
}
