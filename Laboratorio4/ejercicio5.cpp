#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace std::chrono;
const int INF = 1e9;

// ------------------- DIJKSTRA -------------------
vector<int> dijkstra(int n, vector<vector<pair<int, int>>> &adj, int src) {
    vector<int> dist(n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// ------------------- FLOYD–WARSHALL -------------------
vector<vector<int>> floydWarshall(int n, vector<vector<int>> &mat) {
    vector<vector<int>> dist = mat;
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    return dist;
}

// ------------------- MAIN -------------------
int main() {
    srand(42);
    vector<pair<int, int>> configs = {
        {100, 300}, {200, 1000}, {400, 3000}
    };

    for (auto [V, E] : configs) {
        cout << "\nComparando Dijkstra vs Floyd–Warshall para " 
             << V << " vertices y " << E << " aristas...\n";

        // Generar grafo aleatorio
        vector<vector<pair<int, int>>> adj(V);
        vector<vector<int>> mat(V, vector<int>(V, INF));
        for (int i = 0; i < V; i++) mat[i][i] = 0;

        for (int i = 0; i < E; i++) {
            int u = rand() % V;
            int v = rand() % V;
            int w = 1 + rand() % 100;
            if (u != v) {
                adj[u].push_back({v, w});
                mat[u][v] = w;
            }
        }

        // Dijkstra (desde un nodo)
        auto start = high_resolution_clock::now();
        auto dist1 = dijkstra(V, adj, 0);
        auto end = high_resolution_clock::now();
        auto timeDijkstra = duration_cast<microseconds>(end - start).count();

        // Floyd–Warshall (todos los pares)
        start = high_resolution_clock::now();
        auto dist2 = floydWarshall(V, mat);
        end = high_resolution_clock::now();
        auto timeFloyd = duration_cast<microseconds>(end - start).count();

        cout << "Tiempo Dijkstra (desde nodo 0): " << timeDijkstra << " microsegundos\n";
        cout << "Tiempo Floyd-Warshall (todos los pares): " << timeFloyd << " microsegundos\n";
    }

    return 0;
}
