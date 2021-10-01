/**
虫食算
Luogu P1092
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

int N;
string ss[3];
int n2c[30],c2n[130];//num to char and char to num
int up[30];//进位
// code
void dfs2(int,int);
void display()
{
    for(int i='A'; i<='A'+N-1; ++i)
        printf("%d ",c2n[i]);
    puts("");
    exit(0);
}
int getcur(int pos,int cur)
{
    int ret=(c2n[ ss[2][pos] ]+N-c2n[ ss[1-cur][pos] ]-up[pos+1])%N;
    return ret;
}
void dfs1(int pos,int cur)//pos from N-1(个位) to 0(最高位) num=0 or 1
{
    //printf("dfs1 pos=%d,cur=%d\n",pos,cur);
    if(pos==-1)
    {
        if(up[0]==0)
            display();
        return;
    }
    int ch=ss[cur][pos];
    if(c2n[ch]!=-1)
    {
        if(cur==1)  dfs2(pos,cur+1);
        else    dfs1(pos,cur+1);
        return;
    }
    
    for(int i=N-1; i>=0; --i)
    {
        if(n2c[i]!=-1)
            continue;

        n2c[i]=ch;
        c2n[ch]=i;
        //printf(" set(%c<->%d)\n",ch,i);

        if(cur==1)  dfs2(pos,cur+1);
        else    dfs1(pos,cur+1);

        n2c[i]=-1;
        c2n[ch]=-1;
    }
    //printf("exit dfs1 pos=%d,cur=%d\n",pos,cur);
}
inline bool check(int pos)//检查该位是否满足关系
{
    //printf(" check %d ,%c(%d)+%c(%d)=%c(%d)\n",pos,ss[0][pos],c2n[ ss[0][pos] ],ss[1][pos],c2n[ ss[1][pos] ],ss[2][pos],c2n[ ss[2][pos] ]);
    int t= (c2n[ ss[0][pos] ]+c2n[ ss[1][pos] ]+up[pos+1])%N;
    if( t== c2n[ ss[2][pos] ] )
    {
        return true;
    }
    else
        return false;
}
inline bool check2(int pos)
{
    if(c2n[ ss[0][pos] ]==-1||c2n[ ss[1][pos] ]==-1||c2n[ ss[2][pos] ]==-1)
        return true;
    else return check(pos);
}
void dfs2(int pos,int cur)//pos from N-1(个位) to 0(最高位) num=2
{
    int ch=ss[cur][pos];
    if(c2n[ch]!=-1)
    {
        if(check(pos))
        {
            up[pos]=(c2n[ ss[0][pos] ]+c2n[ ss[1][pos] ]+up[pos+1])/N;
            dfs1(pos-1,0);
            up[pos]=0;
        }
        return;
    }
    {
        int i=(c2n[ ss[0][pos] ]+c2n[ ss[1][pos] ]+up[pos+1])%N;
        if(n2c[i]!=-1)
            return;

        n2c[i]=ch;
        c2n[ch]=i;

        if(check(pos))
        {
            up[pos]=(c2n[ ss[0][pos] ]+c2n[ ss[1][pos] ]+up[pos+1])/N;
            if(check2(pos-1))
                dfs1(pos-1,0);
            up[pos]=0;
        }
        n2c[i]=-1;
        c2n[ch]=-1;
    }
}
int main()
{
    memset(c2n,-1,sizeof c2n);
    memset(n2c,-1,sizeof n2c);
    scanf("%d",&N);
    cin>>ss[0]>>ss[1]>>ss[2];
    dfs1(N-1,0);
    return 0;
}
