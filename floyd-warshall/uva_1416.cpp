#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

const int INF = 1e9;

long long floyd_warshall(vector<vector<int>> dist, int n, int L)
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    long long sum = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            sum += (dist[i][j] != INF ? dist[i][j] : L);

    return sum * 2;
}

int main()
{
    int n, m, L;
    cin >> n >> m >> L;

    vector<tuple<int, int, int>> edges;

    vector<vector<int>> dist(n, vector<int>(n, INF));

    for (int i = 0; i < n; i++)
        dist[i][i] = 0;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        --u;
        --v;

        edges.push_back({u, v, w});
        dist[u][v] = dist[v][u] = min(dist[u][v], w);
    }

    long long init_sum = floyd_warshall(dist, n, L);
    long long second_sum = init_sum;

    for (int idx = 0; idx < m; idx++)
    {
        vector<vector<int>> temp_dist(n, vector<int>(n, INF));

        for (int i = 0; i < n; i++)
            temp_dist[i][i] = 0;

        for (int j = 0; j < m; j++)
        {
            if (j == idx)
                continue;

            auto [u, v, w] = edges[j];
            temp_dist[u][v] = temp_dist[v][u] = min(temp_dist[u][v], w);
        }

        second_sum = max(second_sum, floyd_warshall(temp_dist, n, L));
    }

    cout << init_sum << " " << second_sum;

    return 0;
}