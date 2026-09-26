#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, weight;
};

class DSU {
    vector<int> parent, rank_;
public:
    DSU(int n) {
        parent.resize(n);
        rank_.assign(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); 
        return parent[x];
    }

    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false; 
        if (rank_[rx] < rank_[ry]) swap(rx, ry);
        parent[ry] = rx;
        if (rank_[rx] == rank_[ry]) rank_[rx]++;
        return true;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<Edge> edges(E);
    cout << "Enter each edge as: u v weight  (vertices 0-indexed)\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    DSU dsu(V);
    vector<Edge> mst;
    int totalWeight = 0;

    for (const auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst.push_back(e);
            totalWeight += e.weight;
        }
        if ((int)mst.size() == V - 1) break;
    }

    if ((int)mst.size() != V - 1) {
        cout << "\nGraph is not connected; no spanning tree exists.\n";
        return 0;
    }

    cout << "\nEdges in the Minimum Spanning Tree:\n";
    for (const auto& e : mst) {
        cout << e.u << " - " << e.v << "  (weight " << e.weight << ")\n";
    }
    cout << "Total weight of MST: " << totalWeight << "\n";

    return 0;
}
