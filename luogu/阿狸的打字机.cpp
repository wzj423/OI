#include <bits/stdc++.h>

using namespace std;
//data=============================
const int MAXN=1e5+10;
int N,M;
char a[MAXN];
struct _q{
    int x,y,id;
    int ans;
}Q[MAXN];
int QBegin[MAXN];
bool cmpy(_q x,_q y) {
    return x.y<y.y;
}
bool cmpid(_q x,_q y) {
    return x.id<y.id;
}
//edge=========================
struct edge {
    int ed,nxt;
}E[MAXN*10];
int head[MAXN],Ecnt;
void addEdge(int st,int ed) {
    E[++Ecnt].ed=ed,E[Ecnt].nxt=head[st],head[st]=Ecnt;
}
//ACaotuma==========================
int c[MAXN][26],val[MAXN],fail[MAXN],cnt=1;
int fa[MAXN];
int rt[MAXN],rcnt;//rt_x 第x个串字符的fail树的根节点
queue<int> q;
int to[MAXN];//反向fail建树
void build() {//特殊的建自动机方式
    int now=1;
    //fail[1]=1;
    for(int i=0;i<N;++i) {
        int v=a[i];
        //printf("cur char = %c\n",v);
        if(v=='P') {
            val[now]=1;rt[++rcnt]=now;
        } else if(v=='B') {
            now=fa[now];
        } else {
            v-='a';
            if(!c[now][v])  c[now][v]=++cnt,fa[cnt]=now;
            now=c[now][v];
        }
       // printf("\t now at %d\n",now);
    }
    /////build_fail
    for(int i=0;i<26;++i)
        if(c[1][i]) fail[c[1][i]]=1,addEdge(1,c[1][i]),q.push(c[1][i]);
        else    c[1][i]=1;
    while(!q.empty()) {
        int u=q.front();q.pop();
        //printf("u=%d fail_u=%d\n",u,fail[u]);
        for(int i=0;i<26;++i) {
            if(c[u][i]) fail[c[u][i]]=c[fail[u]][i], addEdge(fail[c[u][i]],c[u][i]),q.push(c[u][i]);
            else    c[u][i]=c[fail[u]][i];
        }
    }
}
int query(char *s) {//测试用
    int len=strlen(s),now=1,ans=0;
    for(int i=0;i<len;++i) {
        now=c[now][s[i]-'a'];
        for(int t=now;t!=1;t=fail[t]) ans+=val[t];
    }
    return ans;
}
//BIT=================================
#define lowb(x) (x&(-x))
int num[MAXN*3];
void add(int id,int x) {
    for(;id<=cnt;id+=lowb(id)) num[id]+=x;
}
int sum(int id) {
    int ret=0;
    for(;id>0;id-=lowb(id)) ret+=num[id];
    return ret;
}
int interval(int L,int R) {
    return sum(R)-sum(L-1);
}
//tree==========================
int sid[MAXN],scnt;//从fail树到序列sequece的映射
int tid[MAXN];//从序列到树的映射
int sz[MAXN];//子树大小
void dfs_fail(int st=1) {
    sid[st]=++scnt;
    tid[scnt]=st;
    sz[st]=1;

    for(int i=head[st];i;i=E[i].nxt){
        int ed=E[i].ed;
        dfs_fail(ed);
        sz[st]+=sz[ed];
    }
    //printf("sid[%d]=%d sz[%d]=%d\n",st,sid[st],st,sz[st]);
}
void dfs_trie() {
    int now=1;
    int curs=0;//询问 子串编号
    for(int i=0;i<N;++i) {
        int v=a[i];
        //printf("cur char = %c now=%d\n",v,now);
        if(v=='P') {
            ++curs;
            for(int curq=QBegin[curs];Q[curq].y==curs;++curq) {
                //printf("CURS=%d CURQ=%d\n",curs,curq);
                int root=rt[Q[curq].x],x=Q[curq].x;
                Q[curq].ans=interval(sid[root],sid[root]+sz[root]-1);
                //printf("x=%d,root=%d,interval[%d,%d]\n",x,root,sid[root],sid[root]+sz[root]-1);
                //printf("ans=%d\n",Q[curq].ans);
            }
        } else if(v=='B') {
            add(sid[now],-1);
            now=fa[now];
        } else {
            v-='a';
            now=c[now][v];
            add(sid[now],1);
        }
       // printf("\t now at %d\n",now);
    }
}
//main================================
char p[100];
int main() {
    scanf("%s",a);N=strlen(a);
    build();
    //for(int i=1;i<=10;++i) 
    //    printf("id=%d A=%d B=%d val=%d fail=%d\n",i,c[i][0],c[i][1],val[i],fail[i]);
    /*while(true) {
        scanf("%s",p);
        cout<<query(p)<<endl;
    }*/
    dfs_fail();
    scanf("%d",&M);
    for(int i=1;i<=M;++i) {
        Q[i].id=i;
        scanf("%d%d",&Q[i].x,&Q[i].y);
    }
    sort(Q+1,Q+M+1,cmpy);
    //printf("  %d %d\n",Q[1].y,Q[0].y);
    for(int i=1;i<=M;++i)   if(Q[i].y!=Q[i-1].y)    QBegin[Q[i].y]=i;//,printf("QBegin[%d]=%d\n",Q[i].y,QBegin[Q[i].y]);
    //for(int i=1;i<=M;++i)   printf("%d %d\n",Q[i].x,Q[i].y);
    //for(int i=1;i<=5;++i)   printf("rt[%d]=%d\n",i,rt[i]);
    dfs_trie();
    sort(Q+1,Q+M+1,cmpid);
    for(int i=1;i<=M;++i)
        printf("%d\n",Q[i].ans);
    return 0;
}