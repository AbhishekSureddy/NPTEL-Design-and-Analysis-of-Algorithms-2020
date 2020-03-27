#include <iostream>
#include <algorithm>

using namespace std;
struct Dragon{
int x,y;
};

bool Comparison(struct Dragon a, struct Dragon b)
{
    return a.x < b.x;
}

int main()
{
    int r,c, k, d;
    cin >> r >> c >> k >> d;
    struct Dragon Dragons[d];
    for (int i = 0; i < d; i++)
    {
        cin >> (Dragons+i)->x >> (Dragons+i)->y;
    }
    // sorting
    sort(Dragons, Dragons+d, Comparison);
    // DP table
    int Dp[d][k];
    // distance from (0,0)
    for (int i = 0; i < d; i++)
        Dp[i][0] = (Dragons+i)->x + (Dragons+i)->y;
    for (int j = 1; j < k; j++)
    {
        Dp[j][j] = Dp[j-1][j-1] + abs((Dragons+j-1)->x -(Dragons+j)->x) + abs((Dragons+j-1)->y -(Dragons+j)->y);
        for( int i = j+1; i <d; i++)
        {
            Dp[i][j] = Dp[i-1][j-1] + abs((Dragons+i-1)->x -(Dragons+i)->x) + abs((Dragons+i-1)->y -(Dragons+i)->y);
            for (int l = i-2; l >= j-1; l--)
                Dp[i][j] = min(Dp[i][j],Dp[l][j-1]+ abs((Dragons+l)->x -(Dragons+i)->x) + abs((Dragons+l)->y -(Dragons+i)->y));
        }
    }


    int res = Dp[k-1][k-1];
    for (int i = k; i < d; i++)
        res = min(res, Dp[i][k-1]);
    cout << res << '\n';
    return 0;
}
