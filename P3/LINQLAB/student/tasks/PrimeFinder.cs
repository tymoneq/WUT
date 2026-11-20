namespace tasks;

/// <summary>
/// Here you should implement the Sieve of Eratosthenes algorithm to find all prime numbers up to a given upper bound.
/// </summary>
public static class PrimeFinder
{
    public static IEnumerable<int> SieveOfEratosthenes(int upperBound)
    {
        if (upperBound < 2)
        {
            yield break;
        }

        var NotPrime = new bool[upperBound + 1];

        for (int i = 2; i <= upperBound; i++)
        {
            if (NotPrime[i])
                continue;
            yield return i;

            for (int j = i * i; j <= upperBound; j += i)
            {
                NotPrime[j] = true;
            }
        }
    }
}