// #include <bits/stdc++.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


using namespace std;


struct Node {
    int n_child = 0; // кол-во потомков
    int cnt = 0; // кол-во терминальных нод ниже (включая эту)
    char value = '\0';
    bool term = false;
    vector<size_t> children = {}; // Массив индексов детей в массиве tree
};


class PrefixTree{
public:
    PrefixTree() : tree(1)  {}


    int findChild(size_t u, char c) const {
        for (size_t v: tree[u].children) {
            if (tree[v].value == c) return (int)v;
        }
        return -1;
    }


    bool contains(const string& s) const {
        int cur = 0;

        for (char c: s) {
            int child = findChild(cur, c);
            if (child == -1) return false;
            cur = child;
        }

        return tree[cur].term;
    }


    int countPrefix(const string& s) const {
        int cur = 0;

        for (char c: s) {
            int child = findChild(cur, c);
            if (child == -1) return 0;
            cur = child;
        }

        return tree[cur].cnt;
    }


    void insert(const string& s) {
        if (contains(s)) return;

        int cur = 0;

        for (char c: s) {
            tree[cur].cnt++;


            int child = findChild(cur, c);

            if (child == -1) {
                child = (int)tree.size();

                tree.push_back(Node());
                tree[child].value = c;

                tree[cur].children.push_back(child);
                tree[cur].n_child++;
            }

            cur = child;
        }

        tree[cur].term = true;
        tree[cur].cnt++;
    }


    void erase(const string& s) {
        if (!contains(s)) return;

        vector<size_t> path;

        size_t cur = 0;
        for (char c: s) {
            tree[cur].cnt--;
            path.push_back(cur);
            cur = findChild(cur, c);
        }

        tree[cur].cnt--;
        tree[cur].term = false;
        path.push_back(cur);


        for (size_t i = path.size()-1; i > 0; --i) {
            if (tree[path[i]].cnt == 0) {
                vector<size_t>& ch = tree[path[i-1]].children;

                ch.erase(find(ch.begin(), ch.end(), path[i]));
                tree[path[i-1]].n_child--;
            } else {
                break;
            }
        }
    }


    void dump() const {
        for (size_t i = 0; i < tree.size(); i++) {
            cout << i << ": '" << (tree[i].value ? tree[i].value : '-') << "' term="
                << tree[i].term << " cnt=" << tree[i].cnt << " n_child=" << tree[i].n_child << " children:";
            for (size_t u : tree[i].children) cout << ' ' << u;
            cout << '\n';
        }
    }

private:
    vector<Node> tree; // vector of nodes
    
};



int main() {
    vector<string> S = {
        "ohae", "onni", "chan", "chore", "nigger"
    };

    PrefixTree bor;

    for (string s: S) {
        bor.insert(s);
    }

    bor.dump();
    cout << bor.contains("chore") << endl;
    cout << bor.countPrefix("ch") << endl;
    // cout << bor.countPrefix("") << endl;
    // cout << bor.countPrefix("o") << endl;
    // cout << bor.countPrefix("chore") << endl;
    // cout << bor.countPrefix("chorex") << endl;
    // cout << bor.countPrefix("x") << endl;
    bor.erase("chore");
    cout << bor.contains("chore") << endl;
    bor.dump();




    return 0;
}
