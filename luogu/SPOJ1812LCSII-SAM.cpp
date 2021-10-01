#include <bits/stdc++.h>
const int MAXN=250010;
using namespace std;
//defs-----------------------------------------
char s[MAXN];int N;
//sam===========================================
int ch[MAXN*2][26],fa[MAXN*2],l[MAXN*2],last=1,cnt=1;
int sz[MAXN*2];
void ins(int c) {
    int p=last,np=++cnt;
    last=np;l[np]=l[p]+1;
    for(;p && !ch[p][c];p=fa[p]) ch[p][c]=np;
    if(!p)  fa[np]=1;
    else {
        int q=ch[p][c];
        if(l[q]==l[p]+1) fa[np]=q;
        else {
            int nq=++cnt; l[nq]=l[p]+1;
            memcpy(ch[nq],ch[q],sizeof (ch[q]));
            fa[nq]=fa[q]; fa[q]=fa[np]=nq;
            for(;ch[p][c]==q;p=fa[p]) ch[p][c]=nq;
        }
    }
    sz[np]=1;
}
int tax[MAXN],b[MAXN];
void Rsort() {
    for(int i=1;i<=cnt;++i) tax[i]=0;
    for(int i=1;i<=cnt;++i) tax[l[i]]++;
    for(int i=1;i<=cnt;++i) tax[i]+=tax[i-1];
    for(int i=1;i<=cnt;++i) b[ tax[l[i]]-- ] = i;
}
void cmx(int &a,int b) {
    if(a<b) a=b;
}
void cmn(int &a,int b) {
    if(a>b) a=b;
}
int mxv[MAXN];//储存每一个节点在匹配某一个串时候的最大值
int mnv[MAXN];//储存每一个节点在匹配之前所有串时候的总的最小值
/*
    一个节点的答案要更新为parent树内子树的答案
    否则如果parent子树之内有两个节点在不同串匹配时分别取到最大值
    不更新到父节点就会出错
*/
void cal() {
    int x=1,val=0,c;
    for(int i=0;i<N;++i) {
        c=s[i]-'a';
        while(x&&!ch[x][c]) x=fa[x],val=l[x];
        if(x) ++val,x=ch[x][c],cmx(mxv[x],val);
        else x=1,val=0;
    }
    for(int i=cnt;i>=1;--i) {
        int x=b[i],f=fa[x];
        //printf("x=%d,f=%d\n",x,f);
        cmx(mxv[f],min(mxv[x],l[f]) );//向上更新
        cmn(mnv[x],mxv[x]);
        mxv[x]=0;
    }
}
//main-------------------------------------------
int main() {
    freopen("in/1812.in","r",stdin);
    scanf("%s",s);N=strlen(s);
    for(int i=0;i<N;++i) ins(s[i]-'a');
    memset(mnv,0x3f,sizeof mnv);
    //puts("Inserted");
    int enc=0;
    Rsort();
    while(true) {
        s[0]=s[1]=0;
        scanf("%s",s);N=strlen(s);
        //printf("N=%d str=|%s|\n",N,s);
        if(N==0) break;
        ++enc;
        //printf("enc=%d\n",enc);
        cal();
        //printf("edn sub cal\n");
    }
    //puts("End cal");
    int ans=0;
    for(int i=1;i<=cnt;++i) {
        cmx(ans,mnv[i]);
    }
    printf("%d\n",ans);
    //puts("End");
    return 0;
}