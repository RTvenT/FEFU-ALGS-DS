#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = LLONG_MAX;

struct Edge {
    int to;
    int rev; // reverse edge index in adj list
    ll cap;
};

class FordFulkerson {
private:
    int n;
    vector<vector<Edge>> graph;

    ll dfs(int v, int t, ll pushed, vector<bool>& visited) {
        if (v == t) return pushed;

        visited[v] = true;

        for (Edge& edge: graph[v]) {
            if (!visited[edge.to] && edge.cap > 0) {
                ll max_pushed = dfs(edge.to, t, min(pushed, edge.cap), visited);
                
                //cout << v << ": " << max_pushed << '\n';
          
                edge.cap -= max_pushed;
                graph[edge.to][edge.rev].cap += max_pushed;

                if (max_pushed != 0) return max_pushed;
            }
        }

        return 0;
    }

public:
    explicit FordFulkerson(int n)
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
            vector<bool> visited(n);
            ll add_flow =  dfs(s, t, INF, visited);
            // cout << add_flow << '\n';
            if (add_flow == 0) break;

            f += add_flow;
        }

        return f;
    }
};

int main() {
    ifstream fin("test.in");
    ofstream fout("test.out");

    int V, E;
    fin >> V >> E;

    FordFulkerson solver(V);

    for (int i = 0; i < E; ++i) {
        int u, v;
        ll cap;

        fin >> u >> v >> cap;
        solver.add_edge(u, v, cap);
    }

    fout << solver.max_flow(0, V - 1) << '\n';

    return 0;
}