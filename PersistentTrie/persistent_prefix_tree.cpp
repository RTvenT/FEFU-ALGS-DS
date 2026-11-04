// #include <bits/stdc++.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>


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


    int countPrefix(int v, const string& s) const {
        int cur = versions[v];

        for (char c: s) {
            int child = tree[cur].children[c - 'a'];

            if (child == -1) return 0;
            cur = child;
        }

        return tree[cur].cnt;
    }


    void insert(int v, const string& s) {
        if (contains(v, s)) return;
        
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
        if (!contains(v, s)) return;

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
    PersistentTrie trie;

    // TEST 1: Базовые вставки
    trie.insert(0, "cat");  // v1 = {cat}
    trie.insert(1, "car");  // v2 = {cat, car}
    trie.insert(2, "dog");  // v3 = {cat, car, dog}

    assert(trie.contains(1, "cat"));
    assert(!trie.contains(1, "car"));
    assert(trie.contains(2, "car"));
    assert(trie.contains(3, "dog"));
    assert(trie.countPrefix(3, "ca") == 2);
    assert(trie.countPrefix(3, "") == 3);

    cout << "TEST 1 PASSED\n";

    // TEST 2: Ветвление от старой версии
    trie.insert(1, "apple");  // v4 = {cat, apple}

    assert(trie.contains(4, "apple"));
    assert(trie.contains(4, "cat"));
    assert(!trie.contains(4, "car"));
    assert(!trie.contains(4, "dog"));
    assert(trie.contains(3, "dog"));
    assert(trie.countPrefix(4, "") == 2);

    cout << "TEST 2 PASSED\n";

    // TEST 3: Удаление с общим префиксом
    trie.erase(3, "cat");  // v5 = {car, dog}

    assert(!trie.contains(5, "cat"));
    assert(trie.contains(5, "car"));
    assert(trie.contains(5, "dog"));
    assert(trie.countPrefix(5, "ca") == 1);
    assert(trie.countPrefix(5, "") == 2);

    // Старая версия не должна измениться
    assert(trie.contains(3, "cat"));
    assert(trie.countPrefix(3, "ca") == 2);

    cout << "TEST 3 PASSED\n";

    // TEST 4: Удаление последнего слова в ветке
    trie.erase(5, "car");  // v6 = {dog}

    assert(!trie.contains(6, "car"));
    assert(!trie.contains(6, "cat"));
    assert(trie.contains(6, "dog"));
    assert(trie.countPrefix(6, "ca") == 0);
    assert(trie.countPrefix(6, "") == 1);

    cout << "TEST 4 PASSED\n";

    // TEST 5: Слово является префиксом другого
    trie.insert(6, "do");     // v7 = {dog, do}
    trie.insert(7, "dove");   // v8 = {dog, do, dove}

    assert(trie.countPrefix(8, "do") == 3);
    assert(trie.contains(8, "do"));
    assert(trie.contains(8, "dog"));
    assert(trie.contains(8, "dove"));

    trie.erase(8, "do");      // v9 = {dog, dove}

    assert(!trie.contains(9, "do"));
    assert(trie.contains(9, "dog"));
    assert(trie.contains(9, "dove"));
    assert(trie.countPrefix(9, "do") == 2);

    cout << "TEST 5 PASSED\n";

    // TEST 6: Удаление из одной ветки версий
    trie.erase(4, "apple");  // v10 = {cat}

    assert(!trie.contains(10, "apple"));
    assert(trie.contains(10, "cat"));
    assert(trie.contains(4, "apple"));
    assert(trie.contains(9, "dog"));
    assert(trie.countPrefix(10, "") == 1);

    cout << "TEST 6 PASSED\n";

    // TEST 7: Пустая версия
    trie.erase(10, "cat");  // v11 = {}

    assert(!trie.contains(11, "cat"));
    assert(trie.countPrefix(11, "") == 0);
    assert(trie.countPrefix(11, "c") == 0);

    trie.insert(11, "hello");  // v12 = {hello}

    assert(trie.contains(12, "hello"));
    assert(!trie.contains(12, "cat"));
    assert(trie.countPrefix(12, "") == 1);

    cout << "TEST 7 PASSED\n";

    cout << "\nALL TESTS PASSED!\n";
    return 0;
}