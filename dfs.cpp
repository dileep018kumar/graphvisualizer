#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 2;
vector<ll> adj[N];
bool vis[N] = {0};
int32_t main()
{
    ll n, m;
    cin >> n >> m;

    for (ll i = 0; i < m; i++)
    {
        ll x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    queue<ll> q;
    q.push(1);
    vis[1] = 1;
    while (q.size() > 0)
    {
        ll node = q.front();
        q.pop();
        cout << node << " ";
        vector<ll>::iterator it;
        for (it = adj[node].begin(); it != adj[node].end(); it++)
        {
            if (vis[*it] == 0)
            {
                vis[*it] = 1;
                q.push(*it);
            }
        }
    }
    return 0;
}
