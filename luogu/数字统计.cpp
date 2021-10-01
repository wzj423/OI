#include<cstdio>
#include<iostream>
#include<algorithm>//快排要用的头文件
#define MAXN 200001
/**
水水水
*/
using namespace std;
long int a[MAXN]= {0};
int main()
{
    int n,i,s,num,sum=1;
    cin>>n;
    for(i=1; i<=n; i++)
        cin>>a[i];//输入数据==
    sort(a,a+n+1);//对数据进行排序==
    for(i=1; i<=n; i++)
    {
        if(a[i]==a[i+1])
        {
            sum++;    //如果与下一位相等则出现次数+1
            continue;
        }
        else
        {
            printf("%d %d\n",a[i],sum);    //不等时输出此数与sum 并将sum初始化
            sum=1;
        }
    }
    return 0;
}
