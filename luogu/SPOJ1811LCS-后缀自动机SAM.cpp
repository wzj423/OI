#include <bits/stdc++.h>
const int MAXN=3e5+10;
using namespace std;
//SAM=======================
int sz[MAXN*2];
int ch[MAXN*2][26],fa[MAXN*2],l[MAXN*2];//l->最长长度
int last,cnt;
void ins(int c) {
    int p=last,np=++cnt;
    last=np;l[np]=l[p]+1;
    for(; p && ch[p][c]==0; p=fa[p]) ch[p][c]=np;
    if(!p) fa[np]=1;//节点标号从1开始
    else {
        int q=ch[p][c];
        if(l[q]==l[p]+1) fa[np]=q;
        else {
            int nq=++cnt; l[nq]=l[p]+1;
            memcpy(ch[nq],ch[q],sizeof (ch[q]));
            fa[nq]=fa[q];
            fa[q]=fa[np]=nq;
            for(;ch[p][c]==q;p=fa[p]) ch[p][c]=nq;
        }
    }
    sz[np]=1;
}
//defs==========================
char A[MAXN],B[MAXN];
int N;
//main=========================
int main() {
    last=cnt=1;//Error1
    scanf("%s",A);
    for(int i=0;A[i]!='\0';++i) ins(A[i]-'a');

    if(0) for(int i=0;i<=cnt;++i) {
        printf("id=%d\n",i);
        for(int j=0 ;j<26;++j) if(ch[i][j] )printf("son[%c]=%d\n",char(j+'a'),ch[i][j]);
        printf("fa[%d]=%d\n\n",i,fa[i]);
    }
    scanf("%s",B);N=strlen(B);
    //printf("N=%d\n",N);
    int ans=0,curv=0,now=1;
    for(int i=0;i<N;++i) {
        int v=B[i]-'a';
        if(ch[now][v]) now=ch[now][v],++curv;
        else {
            while(now&&!ch[now][v]) now=fa[now];
            if(!now) now=1,curv=0;
            else {
                curv=l[now]+1;
                now=ch[now][v];
            }
        }
        ans=max(ans,curv);
    }
    printf("%d\n",ans);
    return 0;
}