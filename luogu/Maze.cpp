#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
int Move[10][2]={{0,0},{0,1},{1,0},{-1,0},{0,-1}};
int Map[10][10];
int X,Y,NumNotGo;
struct point
{
    int x;
    int y;
}Start,End,tmp;
int ans;
void DFS(int x,int y)
{
    if(x>X||x<1||y>Y||y<1||Map[x][y]==-1||Map[x][y]==-2)
    {
        //cout<<x<<" "<<y<<"isn't available!"<<endl;
        return;
    }

    //cout<<"DFS in :"<<x<<" "<<y<<endl;
    if(x==End.x&&y==End.y)
    {
        ans++;
        return;
    }

    Map[x][y]=-1;
    for(int i=1;i<=4;i++)
    {

        DFS(x+Move[i][0],y+Move[i][1]);
    }
    Map[x][y]=0;

}
int main()
{
    std::ios::sync_with_stdio(false);
    cin>>Y>>X>>NumNotGo;
    cin>>Start.x>>Start.y;
    cin>>End.x>>End.y;
    Map[Start.x][Start.y]=0;
    for (int i=1;i<=NumNotGo;i++ )
    {
        cin>>tmp.x>>tmp.y;
        Map[tmp.x][tmp.y]=-2;
        tmp.x=0;
        tmp.y=0;
    }
    DFS(Start.x,Start.y);
    cout<<ans<<endl;
    return 0;
}
