#include <bits/stdc++.h>
using namespace std;

const int N = 105;

vector<int> g[N];
int col[N], vis[N], img_no, n, m;

void display() {
    string file = "./graph_texts/" + to_string(img_no++) + ".txt";
    fstream f(file.c_str(), ios::out);
    f << n << " " << m << '\n';
    for (int i=1;i<=n;++i) {
        f << "2\n";
        f << "color " << (col[i] == 0 ? "red" : "blue") << '\n';
        f << "style " << "filled\n";
    }
    int edgeno = 1;
    for (int i=1;i<=n;++i) {
        for (auto v : g[i]) {
            if (v > i) {
                f << v << " " << i << '\n';
                f << "1\n";
                f << "label " << "edge:" + to_string(edgeno++) << '\n';
            }
        }
    }
}

void dfs(int u) {
    col[u] = 1;
    display();
    vis[u] = 1;
    for (auto v : g[u]) if (!vis[v]) {
        col[u] = 0;
        dfs(v);
        col[u] = 1;
        display();
    }
    col[u] = 0;
}

int main() {
    cin >> n >> m;
    for (int i=1;i<=n;++i) {
        col[i] = 0;
        vis[i] = 0;
    }
    for (int i=0;i<m;++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    img_no = 1;
    for (int i=1;i<=n;++i) if (!vis[i]) {
        dfs(i);
    }
}