#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, weight;
};

int main() {
    int V, E, source;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<Edge> edges(E);
    cout << "Enter each directed edge as: u v weight  (vertices 0-indexed)\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    cout << "Enter source vertex: ";
    cin >> source;

    const long long INF = LLONG_MAX / 2;
    vector<long long> dist(V, INF);
    dist[source] = 0;

    for (int i = 0; i < V - 1; i++) {
        for (const auto& e : edges) {
            if (dist[e.u] != INF && dist[e.u] + e.weight < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.weight;
            }
        }
    }

    bool hasNegativeCycle = false;
    for (const auto& e : edges) {
        if (dist[e.u] != INF && dist[e.u] + e.weight < dist[e.v]) {
            hasNegativeCycle = true;
            break;
        }
    }

    if (hasNegativeCycle) {
        cout << "\nGraph contains a negative-weight cycle. Shortest paths undefined.\n";
        return 0;
    }

    cout << "\nShortest distances from source " << source << ":\n";
    for (int i = 0; i < V; i++) {
        cout << "Vertex " << i << " : ";
        if (dist[i] == INF) cout << "unreachable\n";
        else cout << dist[i] << "\n";
    }

    return 0;
}
