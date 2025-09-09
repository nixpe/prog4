#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> gen_adj_mat(const vector<pair<int, int>> &edges)
{
    int max_node = 0;
    for (const auto &edge : edges)
        max_node = max({max_node, edge.first, edge.second});

    vector<vector<int>> adj_mat(max_node + 1, vector<int>(max_node + 1, 0));

    for (const auto &edge : edges)
    {
        adj_mat[edge.first][edge.second] = 1;
        adj_mat[edge.second][edge.first] = 1;
    }

    return adj_mat;
}

ostream &operator<<(ostream &os, const vector<vector<int>> &adj_mat)
{
    int i = 0;
    for (const auto &row : adj_mat)
    {
        os << i++ << " : ";
        for (const auto &val : row)
            os << val << " ";
        os << endl;
    }

    return os;
}

int main()
{
    vector<pair<int, int>> edges = {{2, 3}, {5, 6}, {4, 3}, {0, 6}, {7, 3}, {5, 2}};
    vector<vector<int>> adj_mat = gen_adj_mat(edges);

    cout << adj_mat;

    return 0;
}