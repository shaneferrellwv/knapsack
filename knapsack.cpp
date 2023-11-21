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
    vector<item> sack;

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

    // solves knapsack problem using bottom-up dynamic programming for recurrence relation
    // dp[i][w][k] has max value of first i items of size exactly k whose total weight is exactly w
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

    void traceback()
    {
        int bagValue = dp[N][C][K];
        int c = C;      // current bag weight
        int k = K;      // items removed
        int n = N - 1;  // current bag size

        while (bagValue > 0)
        {
            for (int i = 0; i < items.size(); i++)
            {
                // weight of item chosen by bottom-up dynamic programming solution
                if (c - items[n - i].w >= 0)
                {
                    int chosenItemValue = bagValue - dp[N][c - items[n - i].w][k - 1];

                    // if item was chosen
                    if (chosenItemValue == items[n - i].v)
                    {
                        // add item to list of items in solution
                        sack.push_back(items[n - i]);

                        // update bag value and bag weight
                        bagValue -= items[n - i].v;
                        c -= items[n - i].w;

                        // remove item from items list
                        items.erase(items.begin() + n - i);

                        k--;
                        n--;
                        break;
                    }
                }
            }
        }

        bagValue;
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
        traceback();
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
            cout << "Max value in knapsack: " << maxValue << endl;
            cout << "Knapsack contains: ";
            for (auto it = sack.begin(); it != sack.end(); ++it)
            {
                cout << it->name;
                if (next(it) != sack.end())
                    cout << ", ";
            }
        }
        else
            cout << "There is no subset of exactly " << K << " items exactly totaling weight " << C << endl;
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