/**
幻想迷宫
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
#define STOP(x) {cout<<x<<endl;}
using namespace std;
int N,M;
char maze[4510][4510];
short help[4510][4510];
int startI,startJ;
int helpMove[8][2]= {{0,1},{0,-1},{1,0},{-1,0}};
bool dfs(int i,int j)
{
    if(maze[i][j]=='#'||help[i][j])
        return false;
    help[i][j]=1;
    if(maze[i][j]=='S')
    {
        if((i!=startI||j!=startJ))
            return true;
        else
            return false;
    }
    for(int k=0; k!=4; k++)
    {
        bool b=dfs(i+helpMove[k][0],j+helpMove[k][1]);
        if(b)
            return true;
    }
    return false;
}

void imagineBreaker()/*手动滑稽*/
{
    memset(maze,0,sizeof(maze));
    memset(help,0,sizeof(help));
    STOP(3);
    cin>>N>>M;
    STOP(N);
    STOP(M);
    for(int i=1; i<=N; i++)
        for(int j=1; j<=M; j++)
        {
            cin>>maze[i][j];
            cout<<maze[i][j];
            maze[i+N][j]=maze[i+2*N][j]
                         =maze[i+N][j]=maze[i+N][j+M]=maze[i+2*N][j+M]
                                       =maze[i+N][j]=maze[i+N][j+2*M]=maze[i+2*N][j+2*M]=maze[i][j];
            if(maze[i][j]=='S')
            {
                startI=i;
                startJ=j;
            }
        }
    STOP(4);
    STOP(6);
    STOP(startI);
    STOP(startJ);
    for(int i=1; i<=3*N; i++)
        for(int j=1; i<=3*M; j++)
        {
            cout<<maze[i][j]<<(j==3*M?'\n':' ');
        }
    STOP(5);
    cout<<(dfs(startI+N,startJ+M)?"Yes":"No")<<endl;
}


int main()
{
    freopen("in/imagineMaze.in","r+",stdin);
    //std::ios::sync_with_stdio(false);
    int c;
    while((c=getchar()!=EOF))
    {
        cout<<c<<endl;
        STOP(1);
        ungetc(c,stdin);
        STOP(2);
        imagineBreaker();
    }
    return 0;
}
