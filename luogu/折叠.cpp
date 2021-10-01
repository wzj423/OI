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
int dp[110][110];
int num10[110];

// code
void calc_num10()
{
    num10[0]=1;
    for(int i=1;i<=110;++i)
        if(i%10==0) num10[i]=num10[i/10]+1;
        else num10[i]=num10[i-1];    
}
bool judge(int a,int b,int c)//[a,b] [b+1,c]
{
    int len1=b-a+1,len2=c-b;
    if(len2%len1!=0)    
        return false;
    for(int i=0;i<len2;++i)
        if(s[b+i+1]!=s[a+i%len1])
            return false;          // printf("%d != %d !!! i== %d\n",b+i,a+i%len1-1,i); 
    return true;
}
int main()
{
    memset(dp,0x3f,sizeof dp);
    calc_num10();
    scanf("%s",s);
    len=strlen(s);
    for(int i=0;i<len;++i)  dp[i][i]=1;
    for(int i=len-1;i>=0;--i)
        for(int j=i+1;j<len;++j)
        {
            dp[i][j]=j-i+1;
            for(int k=i;k<j;++k)
            {
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
                if(judge(i,k,j))
                    dp[i][j]=min(dp[i][j],  dp[i][k]+2+num10[(j-i+1)/(k-i+1)]   );
            }
        }
    printf("%d\n",dp[0][len-1]);
    return 0;
}
