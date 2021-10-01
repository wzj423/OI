/**
HH的项链
Luogu P1972
TODO
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <queue>
#include <stack>
#include <algorithm>

using namespace std;
int N;
int a[50010];
int b[50010];
struct node
{
    int l,r;
    int num;
} T[200010];

/// code
int read()
{
    int w=1,q=0;
    char ch=' ';
    while(ch!='-'&&(!isdigit(ch)))ch=getchar();
    if(ch=='-')w=-1,ch=getchar();
    while(isdigit(ch))q=q*10+ch-'0',ch=getchar();
    return w*q;
}
/*int Hash(int x)
{
    int id=x%73079;
    while(Hash[id])
}*/
void make_tree(int L,int R,int id=1)
{
    T[id].l=L;
    T[id].r=R;
    if(L==R)
    {
        T[id].num=1;
        return;
    }
    int mid=(L+R)/2;
    make_tree(L,mid,id<<1);
    make_tree(mid+1,R,id<<1|1);
    int lp=L,rp=mid+1,up=R-L+1;
    for(int i=L; i<=R; ++i)
    {
        if(rp==R||a[lp]<a[rp])
            b[i]=a[lp++];
        else if(lp==mid||a[rp]<a[lp])
            b[i]=a[rp++];
    }
    for(int i=L;i<=R;++i)
    {
        if(i==L)
            T[id].num++;
        else if(b[i]!=b[i-1])
            T[id].num++;
        a[i]=b[i];
    }
}
void init()
{
    scanf("%d",&N);
    for(int i=1; i<=N; ++i)
    {
        scanf("%d",&a[i]);
    }
    make_tree(1,N);
    for(int i=1;i<=N;++i)
    {
        cout<<a[i]<<endl;
    }
}
int main()
{
    init();
    return 0;
}
