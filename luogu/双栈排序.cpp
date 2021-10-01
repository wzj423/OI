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
int N;
int a[1010];
int f[1010];

struct edge {
    int ed,next;
} E[1010*1010];
int head[1010];
int Ecnt;

//图为E,另接连表
int col[1010];

vector <int> s1,s2;
// code
void dfs(int st,int color)//color=1 OR 2
{
    if(!col[st])
        col[st]=color;//没有就染色(1)
    else if(col[st]!=color) //非空且异色,说明这不是一个二分图
    {
        printf("0\n");
        exit(0);
    }
    else return;//搜到了同色节点,返回
    //对应(1)
    for(int i=head[st]; i; i=E[i].next)
        dfs(E[i].ed,3-color);//下一步搜索
}

void addEdge(int st,int ed)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
void init()
{
    scanf("%d",&N);
    for(int i=1; i<=N; ++i)
        scanf("%d",&a[i]);
    memset(f,0x3f,sizeof f);
    for(int i=N; i; --i)
    {
        f[i]=min(f[i+1],a[i]);
    }
}
void work()
{
    for(int i=1; i<N-1; ++i)
        for(int j=i+1; j<N; ++j)
            if(f[j+1]<a[i]&&a[i]<a[j])
                addEdge(i,j),addEdge(j,i);//,printf("Add %d<->%d\n",i,j);

    for(int i=1; i<=N; ++i)
    {
        if(!col[i])
            dfs(i,1);
    }
    /*for(int i=1;i<=N;++i)
        printf("%d ",col[i]);
    puts("");*/
    int cnt=1;
    for(int i=1; i<=N; ++i)
    {
        if(col[i]==1)
        {
            s1.push_back(a[i]);
            printf("a ");
        }
        else
        {
            s2.push_back(a[i]);
            printf("c ");
        }
        while((!s1.empty()&&s1.back()==cnt)||(!s2.empty()&&s2.back()==cnt))
        {
            if(!s1.empty()&&s1.back()==cnt)
            {
                s1.pop_back();
                printf("b ");
                ++cnt;
            }
            if(!s2.empty()&&s2.back()==cnt)
            {
                s2.pop_back();
                printf("d ");
                ++cnt;
            }
        }
    }

}
int main()
{
    init();
    work();
    return 0;
}