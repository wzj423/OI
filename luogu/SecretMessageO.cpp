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
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void addMsg(int length,int id=0)
{
    if(!length)
    {
        ++T[id].leave;
        return;
    }
    int t=read();
    //scanf("%d",&t);
    if(T[id].child[t]==0)
        T[id].child[t]=Tsize++;
    addMsg(length-1,T[id].child[t]);
    ++T[id].downNodeCnt;
}

int searchMsg(int length,int id=0)
{
    int t,ans=0;
    if(T[id].leave!=0)
        ans+=T[id].leave;
    if(length==0)
        return T[id].downNodeCnt+ans;
    //scanf("%d",&t);
    t=read();
    if(T[id].child[t]!=0)
        return ans+searchMsg(length-1,T[id].child[t]);
    else
    {
        --length;
        while((length--)>0)
            read();
        return ans;
    }

}

int M,N;
int main()
{
    M=read();
    N=read();
    int len;
    for(int i=1; i<=M; ++i)
    {
        len=read();
        addMsg(len);
    }
    for(int i=1; i<=N; ++i)
    {
        len=read();
        printf("%d\n",searchMsg(len));
    }
    return 0;
}
