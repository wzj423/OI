#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <queue>
#include <stack>
#include <algorithm>

using namespace std;
typedef long long LL;
char s[110];
int len;
int dp[110][110][2];
int num10[110];

// code
bool same(int a,int b)
{
    int l=b-a+1;
    if(l&1)return 0;
    for(int i=a; i<=(a+b)/2; i++)
        if(s[i]!=s[i+l/2])return false;
    return true;
}

int main()
{
    memset(dp,0x3f,sizeof dp);
    scanf("%s",s);
    len=strlen(s);
    for(int i=len-1; i>=0; --i)
        for(int j=i; j<len; ++j)
        {
            dp[i][j][0]=j-i+1;
            dp[i][j][1]=j-i+1;
            for(int k=i; k<j; ++k)
            {
                dp[i][j][1]=min(dp[i][j][1], min(dp[i][k][0],dp[i][k][1])+min(dp[k+1][j][0],dp[k+1][j][1])+1);//压缩
                dp[i][j][0]=min(dp[i][j][0], dp[i][k][0]+j-k);
            }
            if(same(i,j)&&j!=i)
                dp[i][j][0]=min(dp[i][j][0],dp[i][(i+j)/2][0]+1);
        }
    printf("%d\n",min(dp[0][len-1][0],dp[0][len-1][1]));
    return 0;
}
