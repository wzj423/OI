#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
using namespace std;
int help[100][100];//help[M][N]��ʾM���������ΪN�������ϵķ�����
int M,N;
int main()
{
    cin>>N>>M;
    help[0][1]=1;//С��
    for(int i=1;i<=M;i++)//i    ����
        for(int j=1;j<=N;j++)//j    ���
            help[i][j]=help[i-1][j-1==0?N:j-1]+help[i-1][j+1==N+1?1:j+1];
    cout<<help[M][1]<<endl;
    return 0;
}
