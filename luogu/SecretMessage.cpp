/**
Luogu P2922
Secret Message
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

using namespace std;
struct Node
{
    int leave;
    int downNodeCnt;
    int child[2];
} T[1000100];
int Tsize=1;

void addMsg(int length,int id=0)
{
    if(length==0)
    {
        ++T[id].leave;
        return;
    }
    int t;
    scanf("%d",&t);
    if(T[id].child[t]==0)
        T[id].child[t]=Tsize++;
    addMsg(length-1,T[id].child[t]);
    ++T[id].downNodeCnt;
}

int dfs(int id)
{
    int ans=0;
    if(T[id].leave!=0)
        ans+=T[id].leave;
    for(int i=0; i<2; ++i)
        if(T[id].child[i]!=0)
            ans+=dfs(T[id].child[i]);
    return ans;
}

int searchMsg(int length,int id=0)
{
    int t,ans=0;
    if(T[id].leave!=0)
        ans+=T[id].leave;
    if(length==0)
        //return dfs(id);//!如果搜到了尽头，没有是密码的前缀的了，DFS判断把密码当做前缀的
        return T[id].downNodeCnt+ans;
    scanf("%d",&t);
    if(T[id].child[t]!=0)
        return ans+searchMsg(length-1,T[id].child[t]);
    else
    {
        --length;
        while((length--)>0)
            scanf("%d",&t);
        return ans;
    }

}

int M,N;
int main()
{
    scanf("%d%d",&M,&N);
    for(int i=1; i<=M; ++i)
    {
        int len;
        scanf("%d",&len);
        addMsg(len);
    }
    for(int i=1; i<=N; ++i)
    {
        int len;
        scanf("%d",&len);
        printf("%d\n",searchMsg(len));
    }
    return 0;
}
