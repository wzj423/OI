#include <bits/stdc++.h>

using namespace std;
const int MAXN=200000;
//sam===========================
int ch[MAXN][26],fa[MAXN],l[MAXN],last=1,cnt=1;
int sz[MAXN];
void ins(int c) {
    int p=last,np=++cnt;
    last=np;l[np]=l[p]+1;
    for(;p&&!ch[p][c]; p=fa[p]) ch[p][c]=np;
    if(!p) fa[np]=1;
    else {
        int q=ch[p][c];
        if(l[q]==l[p]+1) fa[np]=q;
        else {
            int nq=++cnt;l[nq]=l[p]+1;
            memcpy(ch[nq],ch[q],sizeof ch[q]);
            fa[nq]=fa[q];fa[q]=fa[np]=nq;
            for(;ch[p][c]==q;p=fa[p]) ch[p][c]=nq;
        }
    }
    //sz[np]=1;
}
int tax[MAXN],b[MAXN];
void build_info() {
    for(int i=1;i<=cnt;++i) ++tax[l[i]];
    for(int i=1;i<=cnt;++i) tax[i]+=tax[i-1];
    for(int i=1;i<=cnt;++i) b[ tax[l[i]]-- ]=i;

    for(int i=1;i<=cnt;++i) ++sz[i];
    for(int i=cnt;i>=1;--i) {
        int u=b[i];
        for(int j=0;j<26;++j)
            sz[u]+=sz[ch[u][j]];
    }
}
//defs===========================
char s[MAXN];
int T,K,N;
//main==========================
int main() {
    scanf("%s",s);N=strlen(s);
    for(int i=0;i<N;++i) ins(s[i]-'a');
    build_info();

    if(0)for(int i=0;i<=cnt;++i) {
        printf("id=%d\n",i);
        for(int j=0 ;j<26;++j) if(ch[i][j] )printf("\tson[%c]=%d\n",char(j+'a'),ch[i][j]);
        printf("\tfa[%d]=%d sz[%d]=%d\n\n",i,fa[i],i,sz[i]);
    }

    scanf("%d",&T);
    while(T--) {
        scanf("%d",&K);
        int x=1;
        while(K) {    //            printf("\nat %d K=%d\n",x,K);
            for(int i=0;i<26;++i) {

                if(!ch[x][i]) continue;
                if(sz[ ch[x][i] ]>=K) {
                    putchar(i+'a');
                    --K;x=ch[x][i];
                    break;
                } else {
                    K-=sz[ ch[x][i] ];
                }
            }

        }
        putchar('\n');
    }
    return 0;
}