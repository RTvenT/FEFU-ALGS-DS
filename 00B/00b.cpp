#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;


class SegTree {
public:
    SegTree(const vector<int>& values)
        : n(values.size()), t(2 * values.size(), 0) {
        for (int k = 0; k < n; ++k) t[n + k] = values[k];
        for (int i = n - 1; i >= 1; --i) t[i] = max(t[2 * i], t[2 * i + 1]);
    }

    void set(int k, int v) {
        k += n;
        t[k] = v;
        for (k /= 2; k >= 1; k /= 2) t[k] = max(t[2 * k], t[2 * k + 1]);
    }

    int query(int l, int r) const {
        int res = 0;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) res = max(res, t[l++]);
            if (r % 2 == 1) res = max(res, t[--r]);
        }
        return res;
    }

private:
    int n;
    vector<int> t;
};


struct P {
    int x, y, z;
    int id;
};


int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt"); 

    int n;
    fin >> n;

    vector<P> v(n);

    for (int i = 0; i < n; ++i) {
        fin >> v[i].x >> v[i].y >> v[i].z;
        v[i].id = i+1;
    }

    sort(v.begin(), v.end(), [](const P& l, const P& r) {
        return l.y < r.y;
    });

    vector<int> border_y(n);
    border_y[n - 1] = n;
    for (int k = n - 2; k >= 0; --k) {
        if (v[k].y == v[k + 1].y) border_y[k] = border_y[k + 1];
        else border_y[k] = k + 1;
    }

    vector<int> order_x(n);
    iota(order_x.begin(), order_x.end(), 0);
    sort(order_x.begin(), order_x.end(), [&](int p, int q) {
        return v[p].x < v[q].x;
    });

    vector<int> z_vec(n);
    for (int i = 0; i < n; ++i) z_vec[i] = v[i].z;

    SegTree tree(z_vec);

    vector<int> ans;

    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && v[order_x[j]].x == v[order_x[i]].x) ++j;

        for (int s = i; s < j; ++s) {
            tree.set(order_x[s], 0);
        }

        for (int s = i; s < j; ++s) {
            int k = order_x[s];                        
            if (tree.query(border_y[k], n) <= v[k].z) {
                ans.push_back(v[k].id);                 
            }
        }

        i = j;                                          
    }

    sort(ans.begin(), ans.end());

    for (int id : ans) fout << id << " ";
}