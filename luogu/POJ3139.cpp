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
typedef long long ll;
const int bits=(1<<16)-1;
using namespace std;
int a[20];
int counter;
struct node {
    int val,nxt;
}L[2000000];
int head[70010],lcnt;
void add(int chain,int num) {
    L[++lcnt].val=num;
    L[lcnt].nxt=head[chain];
    head[chain]=lcnt;
}
//=====================================
int f[65535];
//dfs================================
int seq[6];
void dfs(int cnt,int now,int status) {
    if(cnt==4) {
        do{
            add(seq[1]*1+seq[2]*2+seq[3]*3+seq[4]*4,status);//按值存放
            //printf("%d %d %d %d\n",seq[1],seq[2],seq[3],seq[4]);
        }while(next_permutation(seq+1,seq+4+1));
    } else {
        for(int i=now;i<=15;++i) {
            seq[cnt+1]=a[i];
            dfs(cnt+1,i+1,status|(1<<i));
        }
    }
}
//modules=========================== 
void init() {
    ++counter;
    for(int i=1;i<16;++i)
        scanf("%d",a+i);
    sort(a,a+16);
    memset(head,0,sizeof head);
    memset(f,0,sizeof f);
    lcnt=0;
    dfs(0,0,0);
    for(int i=0;i<=bits;++i) {
        for(int j=head[i];j;j=L[j].nxt) {
            for(int k=L[j].nxt;k;k=L[k].nxt) {
                if((L[j].val&L[k].val)==0 ) {
                    ++f[L[j].val|L[k].val];
                }
            }
        }
    }
}
void work() {
    int ans=0;
    for(int i=0;i<=bits;++i) {
        ans+=f[i]*f[bits^i];
    }
    printf("Case %d: %d\n",counter,ans/2);
}
//main==========================
int main() {
    scanf("%d",a);
    while(a[0]) {
        init();
        work();
        scanf("%d",a);
    }
    return 0;
}