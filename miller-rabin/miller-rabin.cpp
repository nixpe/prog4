#include <iostream>
#include <vector>

using namespace std;

long long powerModulo(long long base, long long exponent, long long modulus)
{
    long long result = 1;
    base %= modulus;

    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            result = (result * base) % modulus;
        }

        base = (base * base) % modulus;
        exponent /= 2;
    }

    return result;
}

bool isCompositeWitness(long long base, long long oddPart, long long powerOfTwo, long long number)
{
    long long currentValue = powerModulo(base, oddPart, number);

    if (currentValue == 1 || currentValue == number - 1)
    {
        return false;
    }

    for (long long step = 1; step < powerOfTwo; step++)
    {
        currentValue = (currentValue * currentValue) % number;

        if (currentValue == number - 1)
        {
            return false;
        }

        if (currentValue == 1)
        {
            return true;
        }
    }

    return true;
}

bool isPrime(long long number)
{
    if (number < 2)
    {
        return false;
    }

    if (number % 2 == 0)
    {
        return number == 2;
    }

    long long oddPart = number - 1;
    long long powerOfTwo = 0;

    while (oddPart % 2 == 0)
    {
        oddPart /= 2;
        powerOfTwo++;
    }

    vector<long long> testBases = {2, 3, 5, 7, 11};

    for (long long base : testBases)
    {
        if (base >= number)
        {
            break;
        }

        if (isCompositeWitness(base, oddPart, powerOfTwo, number))
        {
            return false;
        }
    }

    return true;
}

int main()
{
    long long number;
    cin >> number;

    if (isPrime(number))
    {
        cout << "Prime";
    }
    else
    {
        cout << "Composite";
    }

    return 0;
}