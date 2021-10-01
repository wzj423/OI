#include <bits/stdc++.h>

using namespace std;
const int MAXN=300010;
int N,M;
//edge=====================================
struct edge {
    int ed,next;
}E[MAXN*4];
int Ecnt,head[MAXN];
void addEdge(int st,int ed) {
    E[++Ecnt].ed=ed,E[Ecnt].next=head[st],head[st]=Ecnt;
}
//dp=========================================
/*
f[i][0] 不含父节点,以该节点为终点的worm大小
f[i][1] 不含父节点,经过该节点的worm大小

f[i][0]= max{ f[son of i][0] +son[i]+1-1 }
f[i][1]= fst+scd+son[i]+1-2
*/
int f[MAXN][2];
int son[MAXN];//儿子个数
int fa[MAXN];//父亲
void dfs(int st) {
    int fst=0,scd=0;
    for(int i=head[st];i;i=E[i].next) {
        int ed=E[i].ed;
        if(ed!=fa[st]) {
            ++son[st];
            fa[ed]=st;
            dfs(ed);

            if(f[ed][0]>scd) {
                scd=f[ed][0];
                if(scd>fst) {
                    swap(scd,fst);
                }
            }
        }
    }
    if(scd) {
        f[st][0]=fst+son[st]+1-1;
        f[st][1]=fst+scd+son[st]+1-2;        
    } else if (fst) {
        f[st][0]=fst+son[st]+1-1;
        f[st][1]=f[st][0];
    } else {
        f[st][0]=f[st][1]=1;
    }

    //printf("id=%d f[0]=%d f[1]=%d son=%d\n",st,f[st][0],f[st][1],son[st]);
}
//main====================================
int main() {
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;++i) {
        int x,y;
        scanf("%d%d",&x,&y);
        addEdge(x,y),addEdge(y,x);
    }
    dfs(1);
    int ans=max(f[1][0],f[1][1]);
    for(int i=2;i<=N;++i) {
        ans=max(f[i][0]+1,ans);
        ans=max(f[i][1]+1,ans);
    }
    printf("%d\n",ans);
    return 0;
}