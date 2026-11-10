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
        // TODO 1: Условие достижения стока
        if (v == t) return pushed;

        // TODO 2: Пометить вершину как посещённую
        visited[v] = true;

        // TODO 3: Перебрать исходящие остаточные рёбра
        for (Edge& edge: graph[v]) {
            // TODO 4: Проверить возможность перехода
            if (!visited[edge.to] && edge.cap > 0) {
                // TODO 5: Рекурсивно найти увеличивающий путь
                ll max_pushed = dfs(edge.to, t, min(pushed, edge.cap), visited);
                // TODO 6: Обновить прямое и обратное рёбра
                edge.cap -= max_pushed;
                graph[edge.to][edge.rev].cap += max_pushed;
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
        Edge rev{u, (int)graph[u].size()-1, 0};
        
        graph[u].push_back(edge);
        graph[v].push_back(edge);
    }

    ll max_flow(int s, int t) {
        // TODO 1: Инициализировать величина потока
        ll f = 0;

        // TODO 2: Запускать DFS, пока
        //          существуют увеличивающие пути
        while (true) {
            vector<bool> visited(n);
            ll add_flow =  dfs(s, t, 0, visited);

            // TODO 3: Суммировать найденные увеличения
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