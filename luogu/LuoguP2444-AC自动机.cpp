#include <bits/stdc++.h>

using namespace std;
const int MAXN=300010;
char p[MAXN];
int N;
struct AC_Automaton {
    int c[MAXN][2],val[MAXN],fail[MAXN],cnt;
    queue<int> Q;
    void insert(char *s) {
        int len=strlen(s),now=0;
        for(int i=0;i<len;++i) {
            int v=s[i]-'0';
            if(!c[now][v])  c[now][v]=++cnt;
            now=c[now][v];
        }
        ++val[now];
    }
    void build() {
        for(int i=0;i<2;++i) if(c[0][i]) Q.push(c[0][i]);
        while(!Q.empty()) {
            int u=Q.front();Q.pop();
            for(int i=0;i<2;++i) {
                if(c[u][i]) fail[c[u][i]]=c[fail[u]][i],val[c[u][i]]+=val[fail[c[u][i]]],Q.push(c[u][i]);
                else c[u][i]=c[fail[u]][i];
            }
        }
    }
    int vis[MAXN],ins[MAXN];
    void dfs(int u) {
        //printf("dfs in %d\n",u);
        if(ins[u]) {
            puts("TAK");
            exit(0);
        }
        if(vis[u])  return;
        ins[u]=true,vis[u]=true;
        for(int i=0;i<2;++i) {
            int v=c[u][i];
            if(v && 0==val[v])   dfs(v);
        }
        ins[u]=false;
        //printf("exit dfs in %d\n",u);
    }
}AC;
int main() {
    scanf("%d",&N);
    for(int i=1;i<=N;++i){
        scanf("%s",p);
        AC.insert(p);    
    }
    AC.build();
    //for(int i=0;i<=11;++i) {
    //    printf("id=%d ls=%d rs=%d val=%d fail=%d\n",i,AC.c[i][0],AC.c[i][1],AC.val[i],AC.fail[i]);
    //}
    AC.dfs(0);
    puts("NIE");
    return 0;
}