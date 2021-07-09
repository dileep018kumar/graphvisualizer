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
    void setclr()
    {
        clr = 1;
    }
    void resetclr()
    {
        clr = 0;
    }
};
class graph : public node
{
    map<node, list<node>> l;

public:
    void addEdge(node x, node y)
    {
        l[x].push_back(y);
        l[y].push_back(x);
    }
    /* void print()
    {
        map<node, list<node>>::iterator it1;
        list<node>::iterator it2;
        for (it1 = l.begin(); it1 != l.end(); it1++)
        {
            // cout << "hello in 1st loop";
            cout << (it1->first).num << "->";
            for (it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
            {
                cout << *it2 << " ";
                // cout << "hello";
            }
            cout << '\n';
        }
    }*/
    void bfs(int src, node *p)
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
            //    cout << node << "color of node " << p[node].getclr() << "\n";

            for (int nbr : l[node])
            {
                if (vis[nbr] == 0)
                    cout << p[1].getnum() << " ";
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
    g.bfs(1, arr[0]);
    return 0;
}
