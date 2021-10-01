#include <bits/stdc++.h>

using namespace std;
int N,M;
int a[20010],pos[20010];
int rt[20010*32];
int v[20010*32],cnt;
int lc[20010*32],rc[20010*32];
void seg_add(int &id,int L,int R,int position,int x) {
    if(!id) id=++cnt; 
    ++v[id];
    if(L==R)    return;
    int mid=(L+R)>>1;
    if(position<=mid)  seg_add(lc[id],L,mid,position,x);
    else               seg_add(rc[id],mid+1,R,position,x);
}
int seg_query(int id,int L,int R,int B,int E)
{
    if(B<=L&&R<=E)  return v[id];
    if(B>R||E<L)    return 0;
    int mid=(L+R)>>1;
    return seg_query(lc[id],L,mid,B,E)+seg_query(rc[id],R,mid+1,B,E);
}
int main()
{

    return 0;
}