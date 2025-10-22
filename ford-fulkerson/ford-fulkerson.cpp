#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int bfs(int s, int t, vector<int> &parent, vector<vector<int>> &capacity, vector<vector<int>> &adj)
{
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty())
    {
        auto [u, flow] = q.front();
        q.pop();

        for (int v : adj[u])
        {
            if (parent[v] == -1 && capacity[u][v] > 0)
            {
                parent[v] = u;

                int new_flow = min(flow, capacity[u][v]);

                if (v == t)
                    return new_flow;

                q.push({v, new_flow});
            }
        }
    }

    return 0;
}

int ford_fulkerson(int n, int s, int t, vector<vector<int>> &capacity, vector<vector<int>> &adj)
{
    int max_flow = 0;

    while (true)
    {
        vector<int> parent(n, -1);
        parent[s] = -2;

        int new_flow = bfs(s, t, parent, capacity, adj);

        if (new_flow == 0)
            break;

        max_flow += new_flow;

        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            capacity[u][v] -= new_flow;
            capacity[v][u] += new_flow;
        }
    }

    return max_flow;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> capacity(n, vector<int>(n, 0));
    vector<vector<int>> adj(n);

    for (int i = 0; i < m; i++)
    {
        int u, v, cap;
        cin >> u >> v >> cap;

        capacity[u][v] += cap;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << ford_fulkerson(n, 0, n - 1, capacity, adj);

    return 0;
}