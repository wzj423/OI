#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <cstring>
#include <string>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

char S[1000010];
int Next[1000010];
int len;
// code


int main()
{
    scanf("%d",&len);
    scanf("%s",S+1);
    int j;
    for(int i=2;i<=len;++i)
    {
        for(j=Next[i-1];j>0&&S[j+1]!=S[i];j=Next[j]);
        Next[i]=j+(S[j+1]==S[i]);
        //printf("%d\n",Next[i]);
    }
    printf("%d",len-Next[len]);
    return 0;
}
