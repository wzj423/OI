#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstdlib>
//#include <hash_map>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
int Map[1010][1010];
int Color[1010][1010];
int Key[1010*1010];
int Move[20][2]={{0,0},{0,1},{0,-1},{1,0},{-1,0}};
int N,M;

struct point
{
    int x;
    int y;
    point(){x=-1;y=-1;}
    point(int a,int b){x=a;y=b;}
};
queue <point> que;
point FindFreePoint(bool IsFirstRun=false)
{
    static int i,j;
    if(IsFirstRun)
    {
        i=1;
        j=1;
    }
    for(;i<=N;i++)
        for(;j<=N;j++)
            if(Color[i][j]==-1)
                return point(i,j);
    return point();
}
void BFS(point start,int key)
{
    point tmp;
    que.push(start);
    Color[start.x][start.y]=key;
    //cout<<"Added Key At :"<<start.x<<","<<start.y<<endl;
    Key[key]++;
    while(!que.empty())
    {
        tmp=que.front();
        que.pop();
        for(int i=1;i<=4;i++)
        {
            if(Color[tmp.x+Move[i][0]][tmp.y+Move[i][1]]==-1&&
               abs(Map[tmp.x+Move[i][0]][tmp.y+Move[i][1]]-Map[tmp.x][tmp.y])==1&&
               tmp.x+Move[i][0]>=1&&tmp.x+Move[i][0]<=N&&tmp.y+Move[i][1]>=1&&tmp.y+Move[i][1]<=N)
               {
                   que.push(point(tmp.x+Move[i][0],tmp.y+Move[i][1]));
                   Key[key]++;
                   //cout<<"Added Key At :"<<tmp.x+Move[i][0]<<","<<tmp.y+Move[i][1]<<endl;
                   Color[tmp.x+Move[i][0]][tmp.y+Move[i][1]]=key;
               }


        }
    }
}
int main()
{
    std::ios::sync_with_stdio(false);
    memset(Map,-1,sizeof(Map));
    memset(Color,-1,sizeof(Color));
    cin>>N>>M;
    char tmp;
    for (int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            cin>>tmp;
            Map[i][j]=tmp-'0';
        }
    }
    point p=FindFreePoint(true);
    int cnt=0;
    while(p.x!=-1&&p.y!=-1)
    {
        BFS(p,cnt);
        cnt++;
        p=FindFreePoint();
    }
    point tmpPoint;
    for(int i=1;i<=M;i++)
    {
        cin>>tmpPoint.x>>tmpPoint.y;
        cout<<Key[Color[tmpPoint.x][tmpPoint.y]]<<endl;
    }
    return 0;
}
