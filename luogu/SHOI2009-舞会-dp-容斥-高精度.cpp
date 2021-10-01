int ____a;
#include <bits/stdc++.h>
#define re register
#define ll long long
using namespace std;
//bign===============================================
struct Int{
    static const int Bit=1e8;
    ll a[90],size;
    inline void operator = (const int x){
        memset(a,0,sizeof(a));
        a[size=1]=x;
    }
    Int(int x=0) {
        (*this)=x;
    }
    inline Int operator + (const Int t){
        Int c=*this;
        int sz=max(c.size,t.size);
        for (re int i=1;i<=sz;++i){
            c.a[i]+=t.a[i];c.a[i+1]+=c.a[i]/Bit;c.a[i]%=Bit;
        }
        if (c.a[sz+1])sz++;
        c.size=sz;
        return c;
    }
    inline Int operator -(const Int t) {
        Int c=*this;
        int sz=size;
        for(re int i=1;i<=sz;++i) {
            c.a[i]-=t.a[i];
            if(c.a[i]<0)
                c.a[i]+=Bit,c.a[i+1]--;
        }
        while(c.a[sz]==0) --sz;
        c.size=sz;
        return c;
    }
    inline Int operator * (const Int t){
        int sz=size+t.size-1;
        Int c;c=0;
        for (re int i=1;i<=size;++i)
            for (re int j=1;j<=t.size;++j)
                c.a[i+j-1]+=a[i]*t.a[j];
        for (re int i=1;i<=sz;i++)
            c.a[i+1]+=c.a[i]/Bit,c.a[i]%=Bit;
        if (c.a[sz+1])sz++;c.size=sz;
        return c;
    }
    inline void out(){
        printf("%d",a[size]);
        for (re int i=size-1;i;--i)
            printf("%08d",a[i]);
    }
}f[205][205],g[205],C[205][205],fac[210],ans;
//defs&tools==========================================
int N,K;
int a[210],b[210];
int p[210];
int ____b;
//main================================================
int main() {
    C[0][0]=1;
    for(int i=1;i<=200;++i)
        for(int j=0;j<=200;++j)
            if(j!=0) C[i][j]=C[i-1][j-1]+C[i-1][j];
            else    C[i][j]=C[i-1][j];

    fac[0]=1;
    for(int i=1;i<=200;++i) fac[i]=fac[i-1]*i;
    scanf("%d%d",&N,&K);    a[N+1]=0x3f3f3f3f;
    for(int i=1;i<=N;++i) scanf("%d",a+i);
    for(int i=1;i<=N;++i) scanf("%d",b+i);
    sort(a+1,a+N+1),sort(b+1,b+N+1);

    for(int i=1;i<=N;++i) {
        for(int j=p[i-1]+1;j<=N+1;++j) {
            if(a[j]>=b[i]) {
                p[i]=j-1;
                break;
            } else if(j==N) p[i]=j;
        }
    }
    //for(int i=1;i<=N+1;++i) printf("%d ",a[i]);puts("");
    //for(int i=1;i<=N;++i) printf("%d ",b[i]);puts("");
    //for(int i=1;i<=N;++i) printf("%d ",p[i]);

    f[0][0]=1;
    for(int i=1;i<=N;++i) {
        for(int j=0;j<=i;++j) {
            if(j!=0) {
                f[i][j]=f[i-1][j]+f[i-1][j-1]*max(0,(p[i]-(j-1)) );
            } else
                f[i][j]=f[i-1][j];
            //printf("f[%d][%d]=",i,j);f[i][j].out();printf("\n");
        }
    }
    for(int i=N;i>=0;--i) {
        g[i]=f[N][i]*fac[N-i];
        for(int j=i+1;j<=N;++j)
            g[i]=g[i]-g[j]*C[j][i];
    }
    for(int i=0;i<=K;++i)
        ans=ans+g[i];
    ans.out();
    //printf("\n%d",int((&____b)-(&____a))/1024/1024);system("pause");
    return 0;
}
