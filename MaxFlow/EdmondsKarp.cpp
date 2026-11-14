#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = LLONG_MAX;


struct Edge {
    int to;
    int rev; // reverse edge index in adj list
    ll cap;
};


class EdmondsKarp {
private:
    int n;
    vector<vector<Edge>> graph;

    bool bfs (int s, int t, vector<int>& parent_vertex, vector<int>& parent_edge) {
        queue<int> q;
        vector<bool> visited(graph.size(), false);

        q.push(s);

        while (!q.empty()) {
            int a = q.front();
            q.pop();
           
            for (size_t i = 0; i < graph[a].size(); ++i) {
                Edge& edge = graph[a][i];
                if (edge.cap > 0 && !visited[edge.to]) {
                    visited[edge.to] = true;
                    parent_vertex[edge.to] = a;
                    parent_edge[edge.to] = i;

                    if (edge.to == t) return true;

                    q.push(edge.to);
                }
            }
        }

        return visited[t];
    }

public:
    explicit EdmondsKarp(int n)
        : n(n), graph(n) {}

    void add_edge(int u, int v, ll cap) {
        if (u == v) return;

        Edge edge{v, (int)graph[v].size(), cap};
        graph[u].push_back(edge);
        
        Edge rev{u, (int)graph[u].size()-1, 0};
        graph[v].push_back(rev);
    }

    ll max_flow(int s, int t) {
        if (s == t) return 0;

        ll f = 0;

        while (true) {
            vector<int> parent_vertex(n, -1);
            vector<int> parent_edge(n, -1);

            bool path = bfs(s, t, parent_vertex, parent_edge);
            if (!path) break;

            // searching max available additional flow
            ll pushed = INF;
            for (int cur = t; cur != s;) {
                int parent = parent_vertex[cur];
                int in_edge_idx = parent_edge[cur];

                Edge& in_edge = graph[parent][in_edge_idx];

                pushed = min(pushed, in_edge.cap);
                
                cur = parent;
            }

            // updatint forward and reverse edges
            for (int cur = t; cur != s;) {
                int parent = parent_vertex[cur];
                int in_edge_idx = parent_edge[cur];

                Edge& in_edge = graph[parent][in_edge_idx];

                in_edge.cap -= pushed;
                graph[cur][in_edge.rev].cap += pushed;
                
                cur = parent;
            }

            f += pushed;
        }

        return f;
    }
};


int main() {
    ifstream fin("test.in");
    ofstream fout("test.out");

    int V, E;
    fin >> V >> E;

    EdmondsKarp solver(V);

    for (int i = 0; i < E; ++i) {
        int u, v;
        ll cap;

        fin >> u >> v >> cap;
        solver.add_edge(u, v, cap);
    }

    fout << solver.max_flow(0, V - 1) << '\n';

    return 0;
}