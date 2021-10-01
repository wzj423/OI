#include<bits/stdc++.h>
#define N 2000005
typedef long long ll;
using namespace std;
char s[N];
int a[N],c[N],size[N],n;
ll ans=0;
struct SuffixAutoMaton{
    int last,cnt;int tran[N<<1][26],link[N<<1],len[N<<1];
    void ins(int c){
        int p=last,cur=++cnt;last=cur;len[cur]=len[p]+1;
        for(;p&&!tran[p][c];p=link[p])tran[p][c]=cur;
        if(!p)link[cur]=1;
        else{
            int q=tran[p][c];
            if(len[p]+1==len[q])link[cur]=q;
            else{
                int clone=++cnt;len[clone]=len[p]+1;
                memcpy(tran[clone],tran[q],sizeof(tran[q]));
                link[clone]=link[q];link[q]=link[cur]=clone;
                for(;tran[p][c]==q;p=link[p])tran[p][c]=clone;
            }
        }
        size[cur]=1;
    }
    void build(){
        scanf("%s",s+1);int len=strlen(s+1);
        last=cnt=1;for(int i=1;i<=len;i++)ins(s[i]-'a');
    }
    void calc(){
        for(int i=1;i<=cnt;i++)c[len[i]]++;
        for(int i=1;i<=cnt;i++)c[i]+=c[i-1];
        for(int i=1;i<=cnt;i++)a[c[len[i]]--]=i;
        for(int i=cnt;i;i--){
            int p=a[i];
            size[link[p]]+=size[p];
            if(size[p]>1)ans=max(ans,1LL*size[p]*len[p]);
        }
        printf("%lld\n",ans);
    }
}sam;
int main(){
    sam.build();
    sam.calc();
}