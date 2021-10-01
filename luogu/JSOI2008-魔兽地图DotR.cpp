#include <bits/stdc++.h>
typedef long long ll;
typedef double db;
#define Set0(x) memset(x,0,sizeof (x))
#define SetMax(x) memset(x,0x3f,sizeof (x))
#define SetMin(x) memset(x,0xc0,sizeof (x))
using namespace std;
int rd() {
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
/*
    对于每一个子树x,我们有
    f[x][i][k] 表示当前子树为x,有i个物品上交上一层合成(从而不计贡献但是计入成本),子树内一共投入了k元的最大收益
    一个子树的贡献有以下几个方面:
    1.其余儿子节点内部的贡献
    2.儿子节点上交的物品合成一部分当前节点物品,这一部分又有一部分被截留在当前节点,产生了贡献
    那么影响一个节点决策的因素有以下几个方面:
    1.投入
    2.合成几个
    3.上交几个
    其中1和3
    会影响父节点的决策,而2仅仅会影响子节点的决策,所以先枚举2,再讨论在多种情况2之下哪种1和3的组合最优
    当情况2确定的时候,相当于在做多重背包,而背包的条件因为2改变而改变,因而我们需要用g数组来暂存答案,用以更新f
    最后再用h数组对于f数组做一个多重背包,因为可能是一个森林.
*/
//defs=============================================
int N,K;
int L[55],M[55],P[55];//M单价,L上限
char ch[20];
//edge============================================
struct edge {
    int ed,nxt,vv;
}E[2000];
int head[55],Ecnt,deg[55];//入度
void addEdge(int st,int ed,int vv) {
    E[++Ecnt].ed=ed,E[Ecnt].nxt=head[st],head[st]=Ecnt;
    E[Ecnt].vv=vv;++deg[ed];
}
//dp==============================================
int f[55][105][2005];
int g[55][55][2005];
int h[55][2005];
void dp(int x) {
    //printf("dp in %d\n",x);
    if(head[x]==0) {//叶子节点
        L[x]=min(L[x],K/M[x]);//钱数限制
        for(int i=0;i<=L[x];++i) //上交几个
            for(int j=i;j<=L[x];++j) //制作几个
                f[x][i][j*M[x]]=(j-i)*P[x];
        return;
    }
    L[x]=0x3f3f3f3f;
    for(int i=head[x];i;i=E[i].nxt) {
        int ed=E[i].ed,vv=E[i].vv;
        dp(ed);
        L[x]=min(L[x],L[ed]/vv);
        M[x]+=M[ed]*vv;
    }
    L[x]=min(L[x],K/M[x]);//钱限制
//开始dp
    g[x][0][0]=0;//初始状态
    for(int l=L[x];l>=0;--l) {//倒序可以保证每一轮所选取的g[x][tot-1][j-k]中所包含的决策至少选取了l*vv个物品用于合成
        int tot=0;
        for(int i=head[x];i;i=E[i].nxt) {
            int ed=E[i].ed,vv=E[i].vv;
            ++tot;
            for(int j=0;j<=K;++j) {
                for(int k=0;k<=j;++k) {
                    g[x][tot][j]=max(g[x][tot][j],g[x][tot-1][j-k]+f[ed][l*vv][k]);
                }
            }
        }
        for(int i=0;i<=l;++i) {
            for(int j=0;j<=K;++j) {
                f[x][i][j]=max(f[x][i][j],g[x][tot][j]+P[x]*(l-i));
            }
        }
    }
}
//main============================================
int main() {
    SetMin(f),SetMin(g);
    N=rd(),K=rd();
    for(int i=1;i<=N;++i) {
        P[i]=rd();
        scanf("%s",ch);
        if(ch[0]=='B') {
            M[i]=rd(),L[i]=rd();
        } else {
            int up=rd();
            while(up--) {
                int v=rd(),num=rd();
                addEdge(i,v,num);
            }
        }
    }
    int tot=0;
    for(int x=1;x<=N;++x) {
        if(!deg[x]) {
            dp(x);++tot;
            for(int i=0;i<=K;++i) {//投入
                for(int j=0;j<=i;++j) {
                    for(int k=0;k<=L[x];++k) {//上交
                        h[tot][i]=max(h[tot][i],h[tot-1][j]+f[x][k][i-j]);
                    }
                }
            }
        }
    }
    //puts("End");
    int ans=0;
    for(int i=1;i<=K;++i) {
        ans=max(ans,h[tot][i]);
    }
    printf("%d\n",ans);
    return 0;
}
