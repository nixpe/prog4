#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> DijkstraPrime(int count)
{
    vector<int> primes;

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>>
        minHeap;

    int currentNumber = 1;

    while (primes.size() < count)
    {
        currentNumber++;

        bool isComposite = false;

        while (!minHeap.empty() && minHeap.top().first == currentNumber)
        {
            int currentMultiple = minHeap.top().first;
            int correspondingPrime = minHeap.top().second;
            minHeap.pop();

            minHeap.push({currentMultiple + correspondingPrime, correspondingPrime});
            isComposite = true;
        }

        if (!isComposite)
        {
            primes.push_back(currentNumber);
            minHeap.push({currentNumber * currentNumber, currentNumber});
        }
    }

    return primes;
}

int main()
{
    int n;
    cin >> n;

    vector<int> primes = DijkstraPrime(n);

    for (int i = 0; i < primes.size(); i++)
    {
        cout << primes[i] << " ";
    }

    return 0;
}