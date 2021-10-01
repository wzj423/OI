/**
神经网络
Luogu P1038
*/
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
int N,K,P;
int color[2000010];
int price[2000010];
int beforeSameColorNum[2000010];//之前有多少相同颜色的咖啡店(包括本下标)
int beforeSameColorId[2000010];//上一个同色的Id
int beforeCafeNum[2000010];//之前有多少符合条件的咖啡店(包括本下标)
int effort[2000010];

int lastColorId[50];
int lastColorNum[50];
// code
void init()
{
    //scanf("%d%d%d",&N,&K,&P);
    cin>>N>>K>>P;
    //cout<<N<<" "<<K<<" "<<P<<endl;
    for(int i=1; i<=N; ++i)
    {
        //scanf("%d%d",&color[i],&price[i]);
        cin>>color[i]>>price[i];
        //cout<<color[i]<<" "<<price[i]<<endl;
    }
}
void preCalc()
{
    //cout<<__func__<<endl;
    int cafeNum=0;

    for(int i=1; i<=N; ++i)
    {
        if(price[i]<=P)
            cafeNum++;
        beforeCafeNum[i]=cafeNum;//统计咖啡店

        beforeSameColorId[i]=lastColorId[color[i]];
        lastColorId[color[i]]=i;//上一个同种颜色的标号

        beforeSameColorNum[i]=beforeSameColorNum[beforeSameColorId[i]]+1;
    }
    if(0)for(int i=1;i<=N;++i)
    {
        printf("%d %d %d\n",beforeCafeNum[i],beforeSameColorId[i],beforeSameColorNum[i]);
    }
}

void work()
{
    int ans=0;
    for(int i=1; i<=N; ++i)
    {
        int before=beforeSameColorId[i];
        if(before>0&&beforeCafeNum[i]>beforeCafeNum[before-1])
        {
            effort[i]=beforeSameColorNum[before];
            ans+=effort[i];
        }
        else
        {
            effort[i]=effort[before];
            ans+=effort[i];
        }
        //cout<<effort[i]<<endl;
    }
    cout<<ans<<endl;
}
int main()
{
    init();
    preCalc();
    work();
    return 0;
}

