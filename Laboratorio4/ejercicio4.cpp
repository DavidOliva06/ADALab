#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Estructura para representar una arista
struct Edge {
    int u, v; 
    int weight; // Peso
};

// Estructura para el conjunto disjunto (Union-Find)
struct DisjointSet {
    vector<int> parent, rank;
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int xr = find(x), yr = find(y);
        if (xr == yr) return;
        if (rank[xr] < rank[yr]) parent[xr] = yr;
        else if (rank[xr] > rank[yr]) parent[yr] = xr;
        else {
            parent[yr] = xr;
            rank[xr]++;
        }
    }
};

// Algoritmo de Borůvka
int boruvkaMST(int V, vector<Edge>& edges) {
    DisjointSet ds(V);
    int numTrees = V;
    int mstWeight = 0;

    while (numTrees > 1) {
        vector<int> cheapest(V, -1);

        // Buscar la arista más barata de cada componente
        for (int i = 0; i < edges.size(); i++) {
            int set1 = ds.find(edges[i].u);
            int set2 = ds.find(edges[i].v);

            if (set1 == set2) continue;

            if (cheapest[set1] == -1 || edges[i].weight < edges[cheapest[set1]].weight)
                cheapest[set1] = i;
            if (cheapest[set2] == -1 || edges[i].weight < edges[cheapest[set2]].weight)
                cheapest[set2] = i;
        }

        // Unir las aristas más baratas
        for (int i = 0; i < V; i++) {
            if (cheapest[i] != -1) {
                int u = edges[cheapest[i]].u;
                int v = edges[cheapest[i]].v;
                int w = edges[cheapest[i]].weight;

                int set1 = ds.find(u);
                int set2 = ds.find(v);

                if (set1 != set2) {
                    ds.unite(set1, set2);
                    mstWeight += w;
                    numTrees--;
                }
            }
        }
    }

    return mstWeight;
}

// Algoritmo de Kruskal
int kruskalMST(int V, vector<Edge>& edges) {
    DisjointSet ds(V);
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    int mstWeight = 0;
    for (auto& e : edges) {
        if (ds.find(e.u) != ds.find(e.v)) {
            ds.unite(e.u, e.v);
            mstWeight += e.weight;
        }
    }
    return mstWeight;
}

// Programa principal
int main() {
    int V = 1000; // Número de vértices
    int E = 5000; // Número de aristas
    vector<Edge> edges;

    // Generar grafo aleatorio
    srand(42);
    for (int i = 0; i < E; i++) {
        Edge e;
        e.u = rand() % V;
        e.v = rand() % V;
        e.weight = 1 + rand() % 1000;
        if (e.u != e.v) edges.push_back(e);
    }

    cout << "Comparando Boruvka vs Kruskal para " << V << " vertices y " << edges.size() << " aristas...\n";

    // Medir tiempo Boruvka
    auto start = high_resolution_clock::now();
    int mstBoruvka = boruvkaMST(V, edges);
    auto end = high_resolution_clock::now();
    auto durBoruvka = duration_cast<microseconds>(end - start).count();

    // Medir tiempo Kruskal
    start = high_resolution_clock::now();
    int mstKruskal = kruskalMST(V, edges);
    end = high_resolution_clock::now();
    auto durKruskal = duration_cast<microseconds>(end - start).count();

    cout << "\nPeso del MST (Boruvka): " << mstBoruvka << " | Tiempo: " << durBoruvka << " microsegundos";
    cout << "\nPeso del MST (Kruskal): " << mstKruskal << " | Tiempo: " << durKruskal << " microsegundos\n";

    return 0;
}
