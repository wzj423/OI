#include <bits/stdc++.h>

using namespace std;
//defs==============================
int bin[2000];
int _T,N,T[1010],B[1010];
int f[1010][300][30];
/*
    f[i][S][k+13] 表示当前队列最前的人是i,以i作为第0人开始一直到第B[i]个人的集合为S,上一个打饭的人是以第i个人计算向后k个
    为了-1的情况因而加上了一个13的偏移量

    f[i][S][k+13] -> 选取不是当前队首的人l打饭 -> f[i][S|bin[l]][l+13]
    f[i][S][k+13] -> 选取是当前队首的人打饭  ->   f[i+t][S'][13-t]
            S|=1 while(S&1) S>>=1,++t
*/
void pb(int x) {
    bitset<5> B(x);
    cout<<B;
}
void update(int &x,int y) {
    if(y<x) x=y;
}
void display(int i,int j,int k) {
    printf("f[%d][",i);pb(j);printf("][%d]=%d\n",k-13,f[i][j][k]);
}
bool OK(int pos,int S,int ins) {
    int up=min(B[pos],N-pos);
    for(int i=0;i<ins;++i) {
        if(bin[i]&S) continue;//打过饭的人不用考虑限制
up=min(B[pos+i],N-pos-i);
//printf("lim%d=%d\n",i,up);        
        if(up+i<ins) return false;

    }
    return true;
}
void init();
void do_dp() {
    //cout<<OK(2,2,3)<<endl;
    memset(f,0x3f,sizeof f);
    f[1][0][12]=0;
    for(int i=1;i<=N;++i) {
        int up=bin[min(B[i]+1,N-i+1)];
        for(int j=0;j<up;++j) {
            if(j&1) continue;
            for(int k=1;k<=B[i]+13 && i+k-13<=N;++k) {//上一次打饭的人不是队头(k已经加上了13的偏移量)
                if(f[i][j][k]>1e9) continue;  
                if(k==13) continue;//跳过队头(队头还没有打过饭)
                if(k>=13 && !(bin[k-13]&j)) continue;
               // display(i,j,k);
                for(int l=1;l<=B[i];++l) {//选不是队头的人转移(l没有加13偏移)
                    if(bin[l]&j) continue;
                    if(!OK(i,j,l)) continue;
                    int cost=(i+k-13!=0)? (T[i+k-13]^T[i+l]):0;
                    update(f[i][j|bin[l]][l+13],f[i][j][k]+ cost );
                   //printf("\tto:");display(i,j|bin[l],l+13);
                }
                //选是队头的人转移
                int cost=(i+k-13!=0)? (T[i+k-13]^T[i]):0;
                int S=j|1,ni=i,nk=13;
                while(S&1) S>>=1,++ni,--nk;
                update(f[ni][S][nk],f[i][j][k]+cost);
                    //printf("\tto:");display(ni,S,nk);                
            }             
        }
    }
    int ans=1e9+10;
    for(int i=0;i<28;++i) {
        ans=min(f[N+1][0][i],ans);
    }
    printf("%d\n",ans);
}
//main===============================
int main() {
    //freopen("gen.in","r",stdin);
    //freopen("my.out","w",stdout);
    bin[0]=1;
    for(int i=1;i<2000;++i) bin[i]=bin[i-1]*2;
    scanf("%d",&_T);
    while(_T--) {
        init();
        do_dp();
    }
    return 0;
}

void init() {
    scanf("%d",&N);
    for(int i=1;i<=N;++i) scanf("%d%d",T+i,B+i);
}