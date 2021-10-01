#include <bits/stdc++.h>
const int MAXN=500010;
#define ll long long
using namespace std;
//defs==============================
int N;
char a[MAXN];
//sam===============================
struct _SAM {
    int last,cnt;
    int ch[MAXN*2][26],fa[MAXN*2],l[MAXN*2];
    ll sz[MAXN*2];
    void ins(int c) {
        int p=last,np=++cnt;
        last=np;l[np]=l[p]+1;
        for(;p && !ch[p][c];p=fa[p]) ch[p][c]=np;
        if(!p) fa[np]=1;
        else {
            int q=ch[p][c];
            if(l[p]+1==l[q]) fa[np]=q;
            else {
                int nq=++cnt; l[nq]=l[p]+1;
                memcpy(ch[nq],ch[q],sizeof (ch[q]));
                fa[nq]=fa[q];fa[q]=fa[np]=nq;
                for(;ch[p][c]==q;p=fa[p]) ch[p][c]=nq;
            }
        }
        sz[np]=1;
    }
    void build() {
		last=cnt=1;
		for(int i=1;i<=N;++i) ins(a[i]-'a');
    }
    int b[MAXN*2],c[MAXN*2];ll sum[MAXN*2];
    ll calc() {
        ll ret=0;
        for(int i=1;i<=cnt;++i) ++c[l[i]];
        for(int i=1;i<=cnt;++i) c[i]+=c[i-1];
        for(int i=1;i<=cnt;++i) b[c[l[i]]--]=i;
        for(int i=cnt;i;--i) {
            int x=b[i],f=fa[x];
            ret+=(ll)sz[f]*sz[x]*l[f];
            sz[f]+=sz[x];
        }
        return ret;
    }
}sam;
//main==============================
int main() {
	scanf("%s",a+1);N=strlen(a+1);
    //reverse(a+1,a+N+1);
    sam.build();
	cout<<(ll)(N-1)*N*(N+1)/2-2ll*sam.calc()<<endl;
	return 0;
}
