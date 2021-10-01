#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include<string>

#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;
int N;
int mat[10][8];
struct _mov
{
    int x,y,direct;
} t;
vector <_mov> Move;
// code
void init()
{
    scanf("%d",&N);
    for(int i=1; i<=5; ++i)
        for(int j=1; j<=8; ++j)
        {
            scanf("%d",&mat[i][j]);
            if(!mat[i][j]) break;
        }
}
void print(int a[10][8])
{
    for(int j=7; j>=1; --j)
    {
        for(int i=1; i<=5; ++i)
            printf("%d ",a[i][j]);
        puts("");
    }
    puts("__________________________");
}
void drop(int a[10][8])
{
    for(int j=2; j<=7; ++j)
        for(int i=5; i>=1; --i)
        {
            if(a[i][j]==0) continue;
            int k=j;
            while(k>=2 && a[i][k-1]==0)
            {
                swap(a[i][k-1],a[i][k]);
                k--;
            }
        }
}

bool remove(int a[10][8])
{
    bool b[10][8],ret=false;
    memset(b,0,sizeof b);
    for(int i=1; i<=5; ++i)
    {
        for(int j=1; j<=7; ++j)
        {
            if(a[i][j]&&a[i][j]==a[i-1][j]&&a[i][j]==a[i+1][j])
                b[i][j]=b[i-1][j]=b[i+1][j]=ret=true;
            if(a[i][j]&&a[i][j]==a[i][j-1]&&a[i][j]==a[i][j+1])
                b[i][j]=b[i][j-1]=b[i][j+1]=ret=true;
        }
    }
    for(int i=1; i<=5; ++i)
        for(int j=1; j<=7; ++j)
            if(b[i][j]) a[i][j]=0;
    drop(a);
    return ret;
}
void deal(int a[10][8])
{
    drop(a);
    while(remove(a));
    remove(a);
}
bool isNull(int a[10][8])
{
    for(int i=1; i<=5; ++i)
        for(int j=1; j<=7; ++j)
            if(a[i][j]) return false;
    return true;
}
void print_ans()
{
    for(int i=0; i<Move.size(); ++i)
        printf("%d %d %d\n",Move[i].x-1,Move[i].y-1,Move[i].direct);
    exit(0);
}
void dfs(int curStep,int curMap[10][8])
{
    int Map[10][8];//本层
    int tempMap[10][8];//下一层
    memcpy(Map,curMap,sizeof Map);
    if(isNull(Map))
        print_ans();
    else if(curStep==N)
        return;
    for(int i=1; i<=5; ++i)
        for(int j=1; j<=7; ++j)
        {
            if(i+1<=5&&Map[i][j]!=0)
            {
                memcpy(tempMap,Map,sizeof Map);
                swap(tempMap[i][j],tempMap[i+1][j]);
                deal(tempMap);

                t.x=i;
                t.y=j;
                t.direct=1;
                Move.push_back(t);

                dfs(curStep+1,tempMap);

                Move.pop_back();
            }
            if(i-1>=1&&Map[i-1][j]==0&&Map[i][j]!=0)
            {
                memcpy(tempMap,Map,sizeof Map);
                swap(tempMap[i][j],tempMap[i-1][j]);
                deal(tempMap);

                t.x=i;
                t.y=j;
                t.direct=-1;
                Move.push_back(t);

                dfs(curStep+1,tempMap);

                Move.pop_back();
            }
        }
}
void work()
{
    dfs(0,mat);
    printf("-1\n");
}

int main()
{
    freopen("mayan.in","r+",stdin);
    freopen("mayan.out","w+",stdout);
    init();
    work();
    return 0;
}