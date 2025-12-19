#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

void buildPowers(
    vector<long long> &power,
    int length,
    int base,
    int mod)
{
    power[0] = 1;
    for (int i = 1; i <= length; i++)
        power[i] = (power[i - 1] * base) % mod;
}

void buildPrefixHash(
    const string &text,
    vector<long long> &prefixHash,
    int base,
    int mod)
{
    prefixHash[0] = 0;
    for (int i = 0; i < text.size(); i++)
    {
        int value = text[i] - 'a' + 1;
        prefixHash[i + 1] =
            (prefixHash[i] * base + value) % mod;
    }
}

long long getHash(
    int left,
    int right,
    const vector<long long> &prefixHash,
    const vector<long long> &power,
    int mod)
{
    long long value =
        prefixHash[right] - (prefixHash[left] * power[right - left]) % mod;

    if (value < 0)
        value += mod;

    return value;
}

int findDuplicateSubstring(
    const string &text,
    int length,
    const vector<long long> &prefixHash,
    const vector<long long> &power,
    int mod)
{
    unordered_map<long long, int> seen;

    for (int start = 0; start + length <= text.size(); start++)
    {
        long long hashValue =
            getHash(start, start + length, prefixHash, power, mod);

        if (seen.count(hashValue))
            return start;

        seen[hashValue] = start;
    }

    return -1;
}

string longestDupSubstring(const string &text)
{
    int n = text.size();
    int base = 31;
    int mod = 1e9 + 7;

    vector<long long> power(n + 1);
    vector<long long> prefixHash(n + 1);

    buildPowers(power, n, base, mod);
    buildPrefixHash(text, prefixHash, base, mod);

    int left = 1;
    int right = n - 1;

    int bestLength = 0;
    int bestStart = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        int start =
            findDuplicateSubstring(text, mid, prefixHash, power, mod);

        if (start != -1)
        {
            bestLength = mid;
            bestStart = start;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    if (bestStart == -1)
        return "";

    return text.substr(bestStart, bestLength);
}

int main()
{
    string text;
    cin >> text;

    cout << longestDupSubstring(text);

    return 0;
}
