#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <cstdlib>

using namespace std;
#define IS_DIS(a,b,c,d) ((a-c)*(a-c)+(b-d)*(b-d)==5)
/// ////////
#define map map1
long long int map[30][30][2];
int ctrlDot[8][2]={-1,-2,-2,-1,1,2,2,1,/**/-2,-1,1,2,2,1,-1,-2};
int N,M;
int h_n,h_m;
int main()
{
    cin>>N>>M;
    cin>>h_n>>h_m;
    map[h_n][h_m][1]=-1;
    for(int i=0;i<=N;i++)
    {
        for(int j=0;j<=M;j++)
        {
            if(IS_DIS(i,j,h_n,h_m))
            {
                map[i][j][1]=-1;
                map[i][j][0]=0;
            }
        }
    }
    for(int i=0;i<=N;i++)
        {
            if(map[i][0][1]!=-1)
                map[i][0][0]=1;
            else
                break;
        }
    for(int i=0;i<=M;i++)
        {
            if(map[0][i][1]!=-1)
                map[0][i][0]=1;
            else
                break;
        }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(map[i][j][1]!=-1)
            {
                map[i][j][0]=map[i-1][j][0]+map[i][j-1][0];
            }
        }
    }
    /*for(int i=0;i<=N;i++)
    {
        for(int j=0;j<=M;j++)
        {
            cout<<map[i][j][0]<<"\t";
        }
        cout<<endl;
    }*/
    cout<<map[N][M][0];
    return 0;
}
