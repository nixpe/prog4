#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

void gen_dist(vector<vector<int>> &dist, int n, int e)
{
    for (int i = 0; i < n; i++)
        dist[i][i] = 0;

    for (int i = 0; i < e; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
    }
}

void floyd_warshall(vector<vector<int>> &dist, int n)
{
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] < INF && dist[k][j] < INF)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                dist[i][j] == INF ? cout << "INF " : cout << dist[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int t = 0; t < n; t++)
            {
                if (dist[i][t] < INF && dist[t][t] < 0 && dist[t][j] < INF)
                {
                    dist[i][j] = -INF;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] == INF)
                cout << "INF ";

            else if (dist[i][j] == -INF)
                cout << "-INF ";

            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int n, e;
    cin >> n >> e;

    vector<vector<int>> dist(n, vector<int>(n, INF));

    gen_dist(dist, n, e);

    floyd_warshall(dist, n);

    return 0;
}