#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
char a[1010];
int N,len;
char dict[1010][500];
int dlen[500];
int f[1010];
// code

int main()
{
    scanf("%s",a+1);
    scanf("%d",&N);
    for(int i=1;i<=N;++i)
    {
        scanf("%s",dict[i]+1);
        dlen[i]=strlen(dict[i]+1);
    }
    len=strlen(a+1);
    for(int i=1;i<=len;++i)
        for(int j=1;j<N;++j)
            if(i-1+dlen[j]<=len&&memcmp(a+i,dict[j]+1,dlen[j])==0)
                for(int k=i-1+dlen[j];k<=len;++k)
                    f[k]=max(f[k],f[i-1]+1);
    printf("%d",f[len]);
    return 0;
}