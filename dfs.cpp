#include <bits/stdc++.h>
#include <node.hpp>
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
    // cin >> n >> m;
    // for (int i=1;i<=n;++i) {
    //     col[i] = 0;
    //     vis[i] = 0;
    // }
    // for (int i=0;i<m;++i) {
    //     int u, v;
    //     cin >> u >> v;
    //     g[u].push_back(v);
    //     g[v].push_back(u);
    // }
    // img_no = 1;
    // for (int i=1;i<=n;++i) if (!vis[i]) {
    //     dfs(i);
    // }
    Graph<int, int> g;
    int n, m;
    cin >> n >> m;

    for (int i=0;i<n;++i) g.addVertex(i);
    for (int i=0;i<m;++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }
    // for (int i=0;i<n;++i) g.addEdge(i, (i+1)%n);
    // fstream f("./graph_texts/1.txt", ios::out);
    // f << g << '\n';
    g.code = [](Node<int, int> &node) {
      for (auto &it : node.inBox) {
        node.state = std::max(node.state, it.second);
      }
      node.inBox.clear();
      node.state = std::max(node.state, node.id);
      node.setNodeParam("color", "blue");
      node.setNodeParam("label", "state=" + std::to_string(node.state) + ",id=" + std::to_string(node.id));
      for (int j=0;j<node.neighbours.size();++j) {
        node.send(node.state, j);
        node.setEdgeParam(j, "label", std::to_string(node.state));
        node.setEdgeParam(j, "color", "red");
      }
    };
    g.simulate(3);
}