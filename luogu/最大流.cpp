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
int N,M;
char a[25][25];
int mat[410][410];
// code

void init()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i)
        for(int j=1;j<=M;++j)
            cin>>a[i][j];
}
void work()
{

}
int main()
{
    init();
    work();
    system("pause");
    return 0;
}