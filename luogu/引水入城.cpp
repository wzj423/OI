/**
引水入城
Luogu P1514
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
#include <utility>
using namespace std;
int mat[600][600];
int vis[600][600];
int N,M;
int mov[4][2]= {{1,0},{-1,0},{0,1},{0,-1}};
struct sect
{
    int L;
    int R;
    bool operator < (sect Other)
    {
        if(L==Other.L) return R>Other.R;
        return L<Other.L;
    }
    sect(int l,int r)
    {
        L=l;
        R=r;
    }
};

vector<sect> S;

int minL,minR;//记录在每一次搜索过程中在最底边的一行经过的最左和最右
/// code here
void init()
{
    memset(mat,0x3f,sizeof(mat));
    scanf("%d%d",&N,&M);
    for(int i=1; i<=N; ++i)
        for(int j=1; j<=M; ++j)
        {
            scanf("%d",&mat[i][j]);
        }
}
void dfs(int x,int y,int id)
{
    vis[x][y]=id;// 进入节点
    if(x==N)
    {
        minL=min(y,minL);
        minR=max(y,minR);
    }
    for(int i=0; i<4; ++i)
    {
        int toX=x+mov[i][0];
        int toY=y+mov[i][1];
        if(vis[toX][toY]!=id&&mat[toX][toY]<mat[x][y])
        {
            dfs(toX,toY,id);
        }
    }

}
void dis_vis()
{
    for(int i=1; i<=N; ++i)
    {
        for(int j=1; j<=M; ++j)
            cout<<vis[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}
void checkNul()
{
    bool b=false;
    int nulCnt=0;
    for(int i=1; i<=M; ++i) //如果不能全覆盖
    {
        if(vis[N][i]==0)
        {
            b=true;
            ++nulCnt;
            //cout<<vis[N][i]<<endl;
        }
    }
    if(b)
    {
        printf("0\n%d\n",nulCnt);
        exit(0);
    }
}
void work()
{

    if(mat[1][1]>=mat[1][2])
    {
        minL=10000,minR=0;
        dfs(1,1,1);
        //cout<<"dfs in"<<1<<" :"<<minL<<" "<<minR<<endl;
        S.push_back(sect(minL,minR));
    }
    //dis_vis();
    if(mat[1][M]>=mat[1][M-1])
    {
        minL=10000,minR=0;
        dfs(1,M,M);   //特判
        // cout<<"dfs in"<<M<<" :"<<minL<<" "<<minR<<endl;
        S.push_back(sect(minL,minR));
    }
    //dis_vis();
    for(int i=2; i<M; ++i)
    {
        if(mat[1][i]>=mat[1][i-1]&&mat[1][i]>=mat[1][i+1])//如果是转折点
        {
            minL=10000;
            minR=0;
            dfs(1,i,i);
            //cout<<"dfs in"<<i<<" :"<<minL<<" "<<minR<<endl;
            S.push_back(sect(minL,minR));
            //dis_vis();
        }
    }
    checkNul();
    ///拼接区间
    sort(S.begin(),S.end());
    for(auto i=S.begin(); i!=S.end(); ++i)
        cout<<i->L<<" "<<i->R<<endl;
    int curR,nextR,secNum=0;
    int up=S.size();
    curR=S[0].R;
    nextR=S[0].R;
    for(int i=1; i<up; ++i)
    {
        if(S[i].L>curR)
        {
            curR=nextR;
            secNum++;
        }
        if(S[i].L<=curR&&S[i].R>nextR)
        {
            nextR=S[i].R;
        }
    }
    printf("1\n%d\n",secNum);
}
int main()
{
    /*  S.push_back(sect(1,2));
      S.push_back(sect(1,3));
      S.push_back(sect(1,4));
    */
    init();
    work();
    return 0;
}
