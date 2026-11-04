#include <bits/stdc++.h>
#include <fstream>



using namespace std;


struct Node {
    int cnt = 0; // кол-во терминальных нод ниже (включая эту)
    char value = '\0';
    bool term = false; 
    vector<int> children = vector<int>(26, -1); // Массив индексов детей в массиве tree
};


class PersistentTrie{
public:
    PersistentTrie() : tree(1), versions() {
        versions.push_back(0);
    }


    bool contains(int v, const string& s) const {
        int cur = versions[v];

        for (char c: s) {
            int child = tree[cur].children[c - 'a'];

            if (child == -1) return false;
            cur = child;
        }

        return tree[cur].term;
    }


    int countPrefix(int v, const string& s) {
        int cur = versions[v];
        tree.push_back(tree[cur]);
        versions.push_back(tree.size()-1);

        for (char c: s) {
            int child = tree[cur].children[c - 'a'];

            if (child == -1) return 0;
            cur = child;
        }

        return tree[cur].cnt;
    }


    void insert(int v, const string& s) {
        int cur = versions[v];
        tree.push_back(tree[versions[v]]);

        int new_ver = tree.size() - 1;
        versions.push_back(new_ver);
        
        size_t i = 0;

        for (; i < s.size(); ++i) {
            char c = s[i];
            int child = tree[cur].children[c - 'a'];

            if (child == -1) break;
    
            tree.push_back(tree[child]);
            tree[new_ver].children[c - 'a'] = new_ver + 1;
            tree[new_ver++].cnt++;

            cur = child;
        }

        for (; i < s.size(); ++i) {
            char c = s[i];

            tree.push_back(Node());
            tree[new_ver].children[c - 'a'] = new_ver + 1;
            
            tree[new_ver++].cnt++;
            tree[new_ver].value = c;
        }

        tree[new_ver].term = true;
        tree[new_ver].cnt++;
    }


    void erase(int v, const string& s) {
        int cur = versions[v];
        tree.push_back(tree[versions[v]]);

        int new_ver = tree.size() - 1;
        versions.push_back(new_ver);

        for (char c: s) {
            int child = tree[cur].children[c - 'a'];
    
            tree.push_back(tree[child]);
            tree[new_ver].children[c - 'a'] = new_ver + 1;
            tree[new_ver++].cnt--; 
            
            cur = child;
        }

        tree[new_ver].cnt--;
        tree[new_ver].term = false;

        for (int node = new_ver, i = s.size()-1 ; node > new_ver - s.size(); node--, i--) {
            if (tree[node].cnt == 0) {
                tree[node-1].children[s[i] - 'a'] = -1;
            } else {
                break;
            }
        }
    }
private:
    vector<Node> tree; // vector of nodes
    vector<size_t> versions;
};


int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");


    PersistentTrie trie;

    int Q;
    fin >> Q;

    for (int i = 0, last_ans = 0; i < Q; ++i) {
        int t, v;
        string s;

        fin >> t >> v >> s;

        for (char& c: s) {
            c = ((c - 'a' - last_ans) % 26 + 26) % 26 + 'a';
        }

        if (t == 1) trie.insert(v, s);
        if (t == 2) trie.erase(v, s);
        if (t == 3) {
            last_ans = trie.countPrefix(v , s);
            fout << last_ans << '\n';
        }
    }

    return 0;
}