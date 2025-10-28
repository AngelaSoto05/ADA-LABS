#include <iostream>
using namespace std;

const int N = 12; // Número de nodos (0 al 11)
int grafo[N][N];  // Matriz de adyacencia
int visitado[N];  // 0 = no visitado, 1 = visitado
int padre[N];     // Para guardar el árbol DFS
int tiempo = 0;
int d[N], f[N];   // Tiempos de descubrimiento y finalización

void dfs(int v) {
    visitado[v] = 1;
    tiempo++;
    d[v] = tiempo;
    cout << "Descubro nodo " << v << " en tiempo " << tiempo << endl;

    for (int u = 0; u < N; u++) {
        if (grafo[v][u] && !visitado[u]) {
            padre[u] = v;
            dfs(u);
        }
    }

    tiempo++;
    f[v] = tiempo;
    cout << "Termino nodo " << v << " en tiempo " << tiempo << endl;
}

int main() {
    // Inicializamos matriz con 0
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grafo[i][j] = 0;
        }
        visitado[i] = 0;
        padre[i] = -1;
    }

    // ----- Definición del grafo según las listas dadas -----
    // 0: 1 4
    grafo[0][1] = 1; grafo[0][4] = 1;
    // 1: 2 5
    grafo[1][2] = 1; grafo[1][5] = 1;
    // 2: 3
    grafo[2][3] = 1;
    // 3: 7
    grafo[3][7] = 1;
    // 4: 8
    grafo[4][8] = 1;
    // 5: 4
    grafo[5][4] = 1;
    // 6: 5 10 2
    grafo[6][5] = 1; grafo[6][10] = 1; grafo[6][2] = 1;
    // 7: 11 6
    grafo[7][11] = 1; grafo[7][6] = 1;
    // 8: 9
    grafo[8][9] = 1;
    // 9: 5 8
    grafo[9][5] = 1; grafo[9][8] = 1;
    // 10: 9
    grafo[10][9] = 1;
    // 11: 10
    grafo[11][10] = 1;
    // -------------------------------------------------------

    cout << "=== Búsqueda en profundidad (DFS) ===\n";

    for (int i = 0; i < N; i++) {
        if (!visitado[i]) {
            cout << "\nInicio DFS desde el nodo " << i << ":\n";
            dfs(i);
        }
    }

    cout << "\n=== Resultados finales ===\n";
    cout << "Nodo | Desc | Fin | Padre\n";
    cout << "-------------------------\n";
    for (int i = 0; i < N; i++) {
        cout << " " << i << "   |  " << d[i] << "   |  " << f[i] << "   |  ";
        if (padre[i] == -1) cout << "-";
        else cout << padre[i];
        cout << endl;
    }

    return 0;
}
