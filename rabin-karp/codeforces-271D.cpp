#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int countGoodSubstrings(const string &s, const string &good, int k)
{
    int p = 31;
    int mod = 1e9 + 7;
    int n = s.size();

    set<long long> hashes;

    for (int i = 0; i < n; i++)
    {
        int bad = 0;
        long long currHash = 0;

        for (int j = i; j < n; j++)
        {
            if (good[s[j] - 'a'] == '0')
                bad++;

            if (bad > k)
                break;

            int val = s[j] - 'a' + 1;
            currHash = (currHash * p + val) % mod;

            hashes.insert(currHash);
        }
    }

    return hashes.size();
}

int main()
{
    string s;
    cin >> s;

    string good;
    cin >> good;

    int k;
    cin >> k;

    cout << countGoodSubstrings(s, good, k);

    return 0;
}
