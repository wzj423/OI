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
}
void dfs1(int pos,int cur)//pos from N-1(个位) to 0(最高位) num=0 or 1
{
    if(pos==-1)
    {
        if(up[0]==0)
            display();
        return;
    }
    char ch=ss[cur][pos];
    if(c2n[ch])
    {
        if(cur==2)  dfs2(pos,cur+1);
        else    dfs1(pos,cur+1);
    }

    for(int i=0; i<N; ++i)
    {
        if(n2c[i])
            continue;

        n2c[i]='A'+i;
        c2n['A'+i]=i;

        if(cur==2)  dfs2(pos,cur+1);
        else    dfs1(pos,cur+1);

        n2c[i]=0;
        c2n['A'+i]=0;
    }
}
bool check(int pos)//检查该位是否满足关系
{
    int t= (c2n[ ss[0][pos] ]+c2n[ ss[1][pos] ]+up[pos+1])%N;
    if( t== c2n[ ss[2][pos] ] )
    {
        return true;
    }
    else
        return false;
}
void dfs2(int pos,int cur)//pos from N-1(个位) to 0(最高位) num=2
{
    int ch=ss[cur][pos];
    if(c2n[ch])
    {
        if(check(pos))  dfs1(pos-1,0);
        else return;        
    }

    for(int i=0; i<N; ++i)
    {
        if(n2c[i])
            continue;

        n2c[i]='A'+i;
        c2n['A'+i]=i;

        if(check(pos))
        {
            up[pos]=(c2n[ ss[0][pos] ]+c2n[ ss[1][pos] ]+up[pos+1])/N;
            dfs1(pos-1,0);
            up[pos]=0;
        }
        n2c[i]=0;
        c2n['A'+i]=0;
    }
}
int main()
{
    scanf("%d",&N);
    cin>>ss[0]>>ss[1]>>ss[2];
    cout<<ss[0];
    dfs1(N-1,0);
    return 0;
}
