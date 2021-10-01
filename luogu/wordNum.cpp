/**
luogu P1026
统计单词个数
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cmath>
#include <cctype>
#include <string>
#include <cstring>

#include <queue>
#include <stack>
#include <algorithm>

using namespace std;
string a,tmp;
int help[201][201];
int dp[201][201];
string dic[10];
int P,K,S,len;
/**
dp[i][j] = 把前i个字符分成j段可以得到的最大单词数
dp[i][j] = dp[i-k][j-1]+help[i-k+1][i] (1<=k<=j)
*/

void deal()
{
    string::size_type pos=0;
    for(int i=0; i<len; i++)
        for(int j=len-1; j>=i; j--)
        {
            int start=j-i;
            for(int k=1; k<=S; k++)
                if(a.find(dic[k],start)==start&&dic[k].size()<=i+1)
                {
                    help[start][j]++;
                    break;
                }
            help[start][j]+=help[start+1][j];
        }
}
int main()
{
    std::ios::sync_with_stdio(false);
    cin>>P>>K;
    for(int i=1; i<=P; i++)
    {
        cin>>tmp;
        a+=tmp;
    }
    len=P*20;
    cin>>S;
    for(int i=1; i<=S; i++)
        cin>>dic[i];
    deal();
    for(int i=1;i<=len;i++)
        for(int j=1;j<=K&&j<=i;j++)
            for(int k=j-1;k<i;k++)
                dp[i][j]=max(dp[i][j],dp[k][j-1]+help[k][i-1]);
    cout<<dp[len][K]<<endl;
    return 0;
}
