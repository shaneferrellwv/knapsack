#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

#include "item.h"

using namespace std;

const int negativeInfinity = -99999999;

class knapsack
{
    // user-defined member variables
    vector<item> items;
    int N, C, K;
    int ***dp;

    // intermediate member variables
    int maxValue;

    // utility function to allocate 3D dp array
    void allocate3DArray()
    {
        dp = new int**[N + 1];
        for (int i = 0; i <= N; i++)
        {
            dp[i] = new int*[C + 1];
            for (int w = 0; w <= C; w++)
            {
                dp[i][w] = new int[K + 1];
            }
        }
    }

    // utility function to delete 3D dp array
    void deallocate3DArray()
    {
        for (int i = 0; i <= N; i++)
        {
            for (int w = 0; w <= C; w++)
            {
                delete[] dp[i][w];
            }
            delete[] dp[i];
        }
        delete[] dp;
    }

    // solves knapsack problem using bottom-up dynamic programming
    // dp has max value of first i items of size exactly k whose total weight is exactly w
    int solve()
    {
        for (int i = 0; i <= N; i++)
        {
            for (int w = 0; w <= C; w++)
            {
                for (int k = 0; k <= K; k++)
                {
                    if ((i < k) || (w > 0 && k == 0) || (w == 0 && k > 0))
                        dp[i][w][k] = negativeInfinity;
                    else if (w == 0 && k == 0)
                        dp[i][w][k] = 0;
                    else if (items[i - 1].w > w)
                        dp[i][w][k] = dp[i - 1][w][k];
                    else
                        dp[i][w][k] = max(dp[i - 1][w][k], items[i - 1].v + dp[i - 1][w - items[i - 1].w][k - 1]);
                }
            }
        }
        return dp[N][C][K];
    }

public:
    // knapsack constructor
    knapsack(string fileName, int capacity, int numberOfItems)
    {
        items = item::createItemsList(fileName);
        N = items.size();
        C = capacity;
        K = numberOfItems;

        allocate3DArray();
        maxValue = solve();
    }

    // knapsack destructor
    ~knapsack()
    {
        deallocate3DArray();
    }

    void printSolution()
    {
        if (maxValue >= 0)
        {
            cout << "Max value in knapsack: " << maxValue << endl << endl;
            cout << "Knapsack contains: ";
            
        }
        else
            cout << "There is no subset of exactly " << K << " items totaling exactly weight " << C << endl;
    }
};

int main(int argc, char* argv[])
{
    string fileName = argv[1];
    int capacity = atoi(argv[2]);
    int numberOfItems = atoi(argv[3]);

    try
    {
        knapsack k = knapsack(fileName, capacity, numberOfItems);
        k.printSolution();
    }
    catch(const exception& e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}