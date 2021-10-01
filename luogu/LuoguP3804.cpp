#include <bits/stdc++.h>

using namespace std;
//definitions =============================
long long ans;
char s[2000005];
int a[2000005],c[2000005],sz[2000005],N;
struct SuffixAutoma {
    int link[4000000],tran[4000000][30],len[4000000];
    int last,cnt;
    void insert(int c) {//cur <=> np
        int cur= ++cnt,p=last;
        last=cur,len[cur]=len[p]+1;
        for(; p && !tran[p][c]; p=link[p])   tran[p][c]=cur;
        if(!p)  link[cur]=1;
        else {
            int q=tran[p][c];//q状态
            if(len[p]+1==len[q])    link[cur]=q;//情况一,直接转移
            else { //clone <=> nq
                int clone=++cnt;
                len[clone]=len[p]+1;
                memcpy(tran[clone],tran[q],sizeof(tran[q]));
                link[clone]=link[q];
                link[q]=link[cur]=clone;
                for(; tran[p][c]==q ; p=link[p] ) tran[p][c]=clone;

            }
        }
        sz[cur]=1;
    }
    void build() {
        scanf("%s",s+1);
        int length=strlen(s+1);
        last=cnt=1;//// !!!
        for(int i=1; i<=length; ++i)  insert(s[i]-'a');
    }
    void calc() {
        for(int i=1; i<=cnt; ++i) c[len[i]]++;
        for(int i=1; i<=cnt; ++i) c[i]+=c[i-1];
        for(int i=1; i<=cnt; ++i) a[ c[len[i]]-- ]=i;
        for(int i=cnt; i; --i) {
            int p=a[i];
            sz[link[p]]+=sz[p];
            if(sz[p]>1) ans=max(ans,1LL*sz[p]*len[p]);
        }
        printf("%lld\n",ans);
    }
} sam;

//codes ===================================

//main ====================================
int main()
{
    sam.build();
    sam.calc();
    return 0;
}