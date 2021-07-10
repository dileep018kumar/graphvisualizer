#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class node
{

    int num;
    bool clr;

public:
    node(int num = 0, bool clr = 0)
    {
        this->num = num;
        this->clr = clr;
    }
    int getnum()
    {
        return num;
    }
    bool getclr()
    {
        return clr;
    }

    void resetclr()
    {
        clr = 0;
    }
};
class graph : public node
{
    map<int, list<int>> l;
    map<int, bool> clr;

public:
    void addEdge(int x, int y)
    {
        l[x].push_back(y);
        l[y].push_back(x);
    }
    void print()
    {
        map<int, list<int>>::iterator it1;
        list<int>::iterator it2;
        for (it1 = l.begin(); it1 != l.end(); it1++)
        {
            // cout << "hello in 1st loop";
            cout << it1->first << "->";
            for (it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
            {
                cout << *it2 << " ";
                // cout << "hello";
            }
            cout << '\n';
        }
    }
    void printclr(int v)
    {
        map<int, bool>::iterator it;
        cout << "graph colour for bfs of node " << v << " is:";
        for (it = clr.begin(); it != clr.end(); it++)
            cout << it->second << " ";
        cout << '\n';
    }
    void setclr(int vertices)
    {
        map<int, bool>::iterator it;

        for (int i = 1; i <= vertices; i++)
            clr[i] = 0;
    }
    void setNodeClr(int v)
    {
        clr[v] = 1;
        printclr(v);
        clr[v] = 0;
    }
    void bfs(int src)
    {
        map<int, bool> vis;
        queue<int> q;
        q.push(src);
        vis[src] = 1;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            // setClr(node);
            cout << "visiting node:" << node << "\n";
            setNodeClr(node);

            for (int nbr : l[node])
            {
                if (vis[nbr] == 0)
                {
                    q.push(nbr);
                    vis[nbr] = 1;
                }
            }
        }
    }
};
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    graph g;
    ll vertices;
    cin >> vertices;
    //  ll adjmat[vertices][vertices];

    node *arr[vertices];
    for (ll i = 1; i <= vertices; i++)
    {
        arr[i] = new node(i);
    }
    ll edges, edges1;
    cin >> edges;
    edges1 = edges;
    while (edges1--)
    {
        ll node1, node2;
        cin >> node1 >> node2;
        g.addEdge(node1, node2);
    }
    // g.print();

    // for (ll i = 1; i <= vertices; i++)
    // {
    //     cout << " color of " << i << " is"
    //          << "-" << arr[i]->getclr() << " ";
    // }
    g.setclr(vertices);
    g.bfs(1);

    return 0;
}
