#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <sstream>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
typedef unsigned long long ULL;
const int MAXN=110,mod=19260817,base=199;
string f[110][110];
string a;
int ditnum[110];
int N;
ULL ha[MAXN];
ULL help[MAXN];
// code
ULL hash_val(int l,int r)
{
    if(!l)  return ha[r];
    else    return ((ha[r]-(ha[l-1]*help[r-l+1])%mod)%mod+mod)%mod;
}
int belong(int l,int r,int c,int d)//if it can be zipped,return the length of the zipped string. otherwise return MAXN;
{
    if((d-c+1)%(r-l+1)) return 2*MAXN;
    int k=(r-l+1);
    while(c<=d)
    {
        for(int i=0;i<k;++i)
            if(a[c+i]!=a[l+i])
                return 2*MAXN;
        c+=k;
    }
    return f[l][r].size()+2+ditnum[(d-l+1)/(r-l+1)];
}
string tostr(int x)
{
    stringstream ss;
    ss<<x;
    return ss.str();
}
int main()
{
    for(int i=1; i<=101; ++i)
        ditnum[i]=ditnum[i/10]+1;
    cin>>a;
    N=a.size();
    ha[0]=a[0];
    help[0]=1;
    for(int i=1; i<N; ++i)
        ha[i]=(ha[i-1]*base+a[i])%mod,help[i]=(help[i-1]*base)%mod;
    /*while(1)
    {
        int i,j,k;
        cin>>i>>k>>j;
        cout<<belong(i,k,k+1,j)<<endl;
    }*/
    int len=0;
    for(int j=0; j<N; ++j)
        for(int i=j; i>=0; --i)
        {
            f[i][j]=a.substr(i,j-i+1);
            len=f[i][j].size();
            for(int k=i; k<j; ++k)
            {
                if(belong(k+1,j,i,k)<len)
                {
                    f[i][j]=tostr((j-i+1)/(j-k))+'('+f[k+1][j]+')';
                    len=f[i][j].size();
                }
                if(f[i][k].size()+f[k+1][j].size()<len)
                {
                    f[i][j]=f[i][k]+f[k+1][j];
                    len=f[i][j].size();
                }
            }
            //printf("f[%d][%d]=%s\n",i,j,f[i][j].c_str());
        }
    //printf("%d\n",belong(0,3,4,7));
    cout<<f[0][N-1]<<endl;
    return 0;
}
