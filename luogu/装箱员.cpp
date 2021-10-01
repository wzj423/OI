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
int N;
char s[110];
int f[110][13][13][13];
// code
void do_dp(int now,int nxt,int a,int b,int c,int put)
{
    nxt=min(nxt,N);
    int aa=a,bb=b,cc=c;
    for(int i=now+1; i<=nxt; ++i)
        if(s[i]=='A') ++aa;
        else if(s[i]=='B') ++bb;
        else ++cc;
    if(put==1)
        f[nxt][aa-a][bb][cc]=min(f[nxt][aa-a][bb][cc],f[now][a][b][c]+1);
    else if(put==2)
        f[nxt][aa][bb-b][cc]=min(f[nxt][aa][bb-b][cc],f[now][a][b][c]+1);
    else
        f[nxt][aa][bb][cc-c]=min(f[nxt][aa][bb][cc-c],f[now][a][b][c]+1);
}
int main()
{
    memset(f,0x3f,sizeof f);
    scanf("%d",&N);
    for(int i=1; i<=N; ++i)
        scanf("%1s",&s[i]);
    int a=0,b=0,c=0;
    for(int i=1; i<=min(N,10); ++i)
        if(s[i]=='A')   ++a;
        else if(s[i]=='B')    ++b;
        else    ++c;
    if(N<=10)
    {
        printf("%d\n",(a!=0)+(b!=0)+(c!=0));
        exit(0);
    }
    else
        f[10][a][b][c]=0;
    for(int i=10; i<=N; ++i)
        for(int j=0; j<=10; ++j)
            for(int k=0; k<=10; ++k)
                for(int l=0; l<=10; ++l)
                    if(f[i][j][k][l]<1e9)
                    {
                        if(j>0)
                            do_dp(i,i+j,j,k,l,1);
                        if(k>0)
                            do_dp(i,i+k,j,k,l,2);
                        if(l>0)
                            do_dp(i,i+l,j,k,l,3);
                    }
    int ans=0x3f3f3f3f;
    for(int j=0; j<=10; ++j)
        for(int k=0; k<=10; ++k)
            for(int l=0; l<=10; ++l)
                if(f[N][j][k][l]<1e9)
                    ans=min(ans,f[N][j][k][l]+(j!=0)+(k!=0)+(l!=0));
    printf("%d\n",ans);
    return 0;
}
