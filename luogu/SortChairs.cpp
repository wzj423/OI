#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <string>
#include <cstring>
#include <cmath>
#include <cctype>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
struct _d
{
    int id=0;
    int sum=0;
}Hang[1010],Lie[1010];
bool cmp(_d a,_d b)
{
    if(a.sum!=b.sum)
        return a.sum>b.sum;
    else
        return a.id<b.id;
}
bool cmp2(_d a,_d b)
{
    return a.id<b.id;
}
struct pt
{
    int x=-1;
    int y=-1;
};
int mm[1010][1010];
int M,N,K,L,D;
int main()
{
    cin>>M>>N>>K>>L>>D;
    pt t1,t2;
    for(int i=1;i<=M;i++)
        Hang[i].id=i;
    for(int i=1;i<=N;i++)
        Lie[i].id=i;
    for(int i=1;i<=D;i++)
    {
        cin>>t1.x>>t1.y>>t2.x>>t2.y;
        if(t1.x==t2.x)
            Lie[min(t1.y,t2.y)].sum++;
        else
            Hang[min(t1.x,t2.x)].sum++;
    }
    sort(Hang+1,Hang+M+1,cmp);
    sort(Lie+1,Lie+N+1,cmp);
    /*for(int i=1;i<=M;i++)
        cout<<Hang[i].id<<" "<<Hang[i].sum<<endl;
    for(int i=1;i<=N;i++)
        cout<<Lie[i].id<<" "<<Lie[i].sum<<endl;*/
    sort(Hang+1,Hang+K+1,cmp2);
    sort(Lie+1,Lie+L+1,cmp2);
    for(int i=1;i<=K;i++)
        cout<<Hang[i].id<<" ";
    cout<<endl;
    for(int i=1;i<=L;i++)
        cout<<Lie[i].id<<" ";
    cout<<endl;
    return 0;

}
