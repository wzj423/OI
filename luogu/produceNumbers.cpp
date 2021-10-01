/**
产生数
luogu P1037
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
int a[20][20];
int vis[20];
int toNum[20];
string number;
int N;
int dfs(int s)
{
    int ans=1;
    if(vis[s])
        return 0;
    vis[s]=true;
    for(int i=0; i<=9; i++)
    {
        if(a[s][i]>0)
        {
            ans+=dfs(i);
        }
    }
    //vis[s]=false;
    return ans;
}
int *ans,*help;
const int lenDigit=205;
void mul(int *to,int *from,int mulNum)
{
    for(int i=0; i<from[lenDigit]; i++)
    {
        to[i]+=(from[i]*mulNum);
        to[i+1]+=(to[i]/10);
        to[i]%=10;
    }
    to[lenDigit]=from[lenDigit]+1;
    if(to[to[lenDigit]-1]==0)
        to[lenDigit]--;
}
void display(int *num)
{
    for(int i=num[lenDigit]-1; i>=0; i--)
        cout<<num[i];
    cout<<endl;
}
int main()
{
    cin>>number>>N;
    ans=new int[210];
    help=new int[210];
    memset(ans,0,210);
    memset(help,0,210);
    ans[0]=1;
    ans[lenDigit]=1;
    for(int i=1; i<=N; i++)
    {
        int x,y;
        cin>>x>>y;
        a[x][y]=1;
    }
    for(int i=0; i<=9; i++)
    {
        toNum[i]=dfs(i);
        memset(vis,0,sizeof(vis));
    }
    for(int i=0; i<=9; i++)
        cout<<i<<" can turn to "<<toNum[i]<<" digits"<<endl;
    for(int i=number.size()-1; i>=0; --i)
    {
        //display(ans);
        //cout<<toNum[number[i]-'0']<<endl;
        //cout<<"==>"<<endl;
        mul(help,ans,toNum[number[i]-'0']);
        swap(ans,help);
        memset(help,0,210);
        //display(ans);
    }
    display(ans);
    return 0;
}
