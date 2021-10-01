/**
立体图
Luogu P1058
NOIp2008 PJ T4
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cmath>
#include <cctype>
#include <string>
#include <cstring>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
/**
倒序输入
输出宽度L=4*n+2*m+1;
i:行 j:列 k:高
(i,j,k)方块左下角位移计算:
    (
*/
const char single[6][10]=
{
    "@@+---+",
    "@/   /|",
    "+---+ |",
    "|   | +",
    "|   |/@",
    "+---+@@",
};
int a[60][60];
int M,N;
char out[1000][1000];

inline int _x(int i,int j)
{
    return 2*(i-1)+1+4*(j-1);
}
inline int _y(int i,int k)
{
    return 3*(k-1)+2*(i-1)+1;
}
void printSingle(int x,int y)
{
    for(int i=5; i>=0; i--)
        for(int j=0; j<=6; j++)
            if(single[i][j]!='@')
                out[y+5-i][x+j]=single[i][j];
}
int main()
{
    std::ios::sync_with_stdio(false);
    cin>>M>>N;
    for(int i=0;i<=999;i++)
        for(int j=0;j<=999;j++)
            out[i][j]=46;
    int yMax=-1000000;
    for(int i=M; i>=1; i--)
        for(int j=1; j<=N; j++)
            cin>>a[i][j];
    for(int i=M; i>=1; i--)
        for(int j=1; j<=N; j++)
            for(int k=1; k<=a[i][j]; k++)
            {
                int x=_x(i,j);
                int y=_y(i,k);
                yMax=max(yMax,y);
                printSingle(x,y);
            }
    yMax+=5;
    for(int i=yMax; i>=1; i--)
    {
        for(int j=1; j<=4*N+2*M+1; j++)
            cout<<out[i][j];
        cout<<endl;
    }
    return 0;
}
