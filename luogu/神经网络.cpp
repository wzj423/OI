/**
神经网络
Luogu P1038
*/
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
int a[110];//初始状态
int valve[110];//阀值
int mat[110][110];//邻接矩阵
int condition[110];//储存状态
int ans[110];
bool vis[110];//bfs访问
int N,P;
queue<int> q;
// code
void init()
{
    scanf("%d%d",&N,&P);
    for(int i=1; i<=N; ++i)
    {
        scanf("%d%d",&a[i],&valve[i]);
    }
    int x,y,vv;
    for(int i=1; i<=P; ++i)
    {
        scanf("%d%d%d",&x,&y,&vv);
        mat[x][y]=vv;
    }
}
int findStartPoint()
{
    bool b=true;
    for(int i=1; i<=N; ++i)
    {
        b=true;
        for(int j=1; j<=N; ++j)
        {
            if(mat[j][i]!=0)
                b=false;
        }
        if(b==false)
            continue;
        else
        {
            q.push(i);
        }

    }
}
void output()
{
    bool b=true,outed=false;
    for(int i=1; i<=N; ++i)
    {
        b=true;
        for(int j=1; j<=N; ++j)
        {
            if(mat[i][j]!=0)
                b=false;
        }
        if(b&&a[i]>0)
        {
            cout<<i<<" "<<a[i]<<endl;
            outed=true;
        }
    }
    if(!outed)
        cout<<"NULL"<<endl;
}
void work()
{
    findStartPoint();
    while(!q.empty())
    {
        int t=q.front();
        q.pop();
        if(a[t]<=0)
            continue;
        for(int i=1; i<=N; ++i)
        {
            if(mat[t][i]!=0)
            {
                a[i]+=(a[t]*mat[t][i]);
                if(vis[i]==false)
                {
                    q.push(i);
                    a[i]-=valve[i];
                    vis[i]=true;
                }
            }
        }
    }
    output();
}
int main()
{
    init();
    //cout<<"-----------------------------------"<<endl;
    work();
    return 0;
}
