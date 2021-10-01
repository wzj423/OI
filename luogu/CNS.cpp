#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
typedef long long LL;
const int INF=0x3f3f3f3f;
int N,M;
int L=0x3f3f3f3f,R;
int mat[2010][2010];
bool vis[2010][2010];
// code
bool check1(int);
bool check2(int);
bool judge(int x)
{
    //printf("judge %d\n",x);
    return check1(x)||check2(x);
}
bool check1(int x)
{
    memset(vis,0,sizeof vis);
    int minv=mat[1][1],maxv=0,last=M;
    for(int i=1;i<=N;++i)
    {
        int t=0;
        for(int j=1;j<=M;++j)
        {
            if(mat[i][j]-minv>x||maxv-mat[i][j]>x||j>last)
                break;
            vis[i][j]=true;
            if(mat[i][j]>maxv)   maxv=mat[i][j];
            if(mat[i][j]<minv)  minv=mat[i][j];
            if(j>t) t=j;
            //cout<<"1 ";
        }        
        //cout<<'|'<<endl;
        last=t;
    }
    maxv=0,minv=INF;
    for(int i=1;i<=N;++i)
        for(int j=1;j<=M;++j)
        {
            if(vis[i][j])   vis[i][j]=false;
            else if(mat[i][j]-minv>x||maxv-mat[i][j]>x)
                return false;
            else
            {
                if(mat[i][j]>maxv)   maxv=mat[i][j];
                if(mat[i][j]<minv)  minv=mat[i][j];
            }
        }
    return true;
}
bool check2(int x)
{
    memset(vis,0,sizeof vis);
    int minv=mat[N][1],maxv=0,last=M;
    for(int i=N;i>=1;--i)
    {
        int t=0;
        for(int j=1;j<=M;++j)
        {
            if(mat[i][j]-minv>x||maxv-mat[i][j]>x||j>last)
                break;
            vis[i][j]=true;
            if(mat[i][j]>maxv)   maxv=mat[i][j];
            if(mat[i][j]<minv)  minv=mat[i][j];
            if(j>t) t=j;
           // cout<<"1 ";
        }        
        //cout<<'|'<<endl;
        last=t;
    }
    maxv=0,minv=INF;
    for(int i=1;i<=N;++i)
        for(int j=1;j<=M;++j)
        {
            if(vis[i][j])   vis[i][j]=false;
            else if(mat[i][j]-minv>x||maxv-mat[i][j]>x)
                return false;
            else
            {
                if(mat[i][j]>maxv)   maxv=mat[i][j];
                if(mat[i][j]<minv)  minv=mat[i][j];
            }
        }
    return true;
}
int main()
{
    //freopen("c:\\Users\\Mike-Wu\\Downloads\\oct_r2\\files\\2\\sample3.in","r+",stdin);
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i)
        for(int j=1;j<=M;++j)
            scanf("%d",&mat[i][j]),L=min(L,mat[i][j]),R=max(R,mat[i][j]);
    //printf("%d %d\n",L,R);
    //printf("%d\n",check2(11));
    while(L<=R)
    {
        int mid=(L+R)>>1;
        if(judge(mid))
            R=mid-1;//,puts("Can");
        else
            L=mid+1;//,puts("Cannot");
    }
    printf("%d\n",L);
    return 0;
}