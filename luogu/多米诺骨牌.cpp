/**
P1282
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cmath>
#include <cctype>
#include <string>
#include <cstring>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
#define INF 0x3f3f3f3f
int card[1010][2];
int preSum[1010];//ǰ��ͽ�Ϊ��ά
int N;
int dp[1010][6010];
int ans = INF;
int main()
{
    std::ios::sync_with_stdio ( false );
    cin >> N;
    memset ( dp, 0x3f, sizeof ( dp ) );
    for ( int i = 1; i <= N; i++ )
    {
        cin >> card[i][0] >> card[i][1];
        preSum[i] = preSum[i - 1] + card[i][0] + card[i][1];
    }
    dp[1][card[1][0]] = 0;
    dp[1][card[1][1]] = 1;
    /**
    ת�Ʒ��̶���
    f[i][j]=ǰi����ʹ����һ�е���֮��Ϊj����С������
    ת�Ʒ���:
    f[i][j]=min{f[i-1][j-card[i][0]],//��ת
                f[i-1][j-card[i][1]]+1}//����ת
    ȡֵ:
    i<=j<=preSum[i]-i
    */
    for ( int i = 2; i <= N; i++ )
        for ( int j = i; j <= preSum[i] - i; j++ )
        {
            if ( j > card[i][0] )
                dp[i][j] = min ( dp[i][j], dp[i - 1][j - card[i][0]] );
            if ( j > card[i][1] )
                dp[i][j] = min ( dp[i][j], dp[i - 1][j - card[i][1]] + 1 );
        }
    int curDiff = INF;
    for ( int j = N; j <= preSum[N] - N; j++ )
        if ( dp[N][j] != INF && abs ( preSum[N] - 2 * j ) < curDiff )
        {
            curDiff = abs ( preSum[N] - 2 * j );
            ans = dp[N][j];
        }
        else if ( dp[N][j] != INF && abs ( preSum[N] - 2 * j ) == curDiff && ans > dp[N][j] )
            ans = dp[N][j];
    cout << ans << endl;
    return 0;
}
