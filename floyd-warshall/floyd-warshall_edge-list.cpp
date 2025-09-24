#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

struct Edge
{
    int u, v, w;
};

void gen_edge_list(vector<Edge> &edges, int n, int e)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int idx = i * n + j;
            edges[idx] = {i, j, (i == j ? 0 : INF)};
        }
    }

    for (int k = 0; k < e; k++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        int idx = u * n + v;
        edges[idx].w = min(edges[idx].w, w);
    }
}

void floyd_warshall(vector<Edge> &edges, int n)
{
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int idx_ij = i * n + j;
                int idx_ik = i * n + k;
                int idx_kj = k * n + j;

                if (edges[idx_ik].w < INF && edges[idx_kj].w < INF)
                {
                    edges[idx_ij].w = min(edges[idx_ij].w,
                                          edges[idx_ik].w + edges[idx_kj].w);
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int d = edges[i * n + j].w;
                d == INF ? cout << "INF " : cout << d << " ";
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
                int idx_it = i * n + t;
                int idx_tt = t * n + t;
                int idx_tj = t * n + j;
                int idx_ij = i * n + j;

                if (edges[idx_it].w < INF && edges[idx_tt].w < 0 && edges[idx_tj].w < INF)
                {
                    edges[idx_ij].w = -INF;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int d = edges[i * n + j].w;

            if (d == INF)
                cout << "INF ";

            else if (d == -INF)
                cout << "-INF ";

            else
                cout << d << " ";
        }
        cout << endl;
    }
}

int main()
{
    int n, e;
    cin >> n >> e;

    vector<Edge> edges(n * n);

    gen_edge_list(edges, n, e);

    floyd_warshall(edges, n);

    return 0;
}