/**
垃圾陷阱
luogu P1156
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
#define INF 0x3f3f3f3f
#define DBG while(0)
const int _MIN_INF=-1061109559;
/**
状态转移方程定义
dp[i][j]    第i个垃圾扔下,生命还剩j小时时最大的高度
状态转移方程:
dp[i][j]=max(
            dp[i-1][j+(t[i]-t[i-1])]+hei[i],//不吃
            dp[i-1][j+(t[i]-t[i-1])-live[i]]//吃
             )
初始化:
dp[0][10]=0;
*/

void quickSort(int *a,int _l,int _r)
{
    if(_l >=_r)
        return;
    int l=_l,r=_r;
    int stand=a[(l+r)/2];
    while(l<r)
    {
        while(a[l]<stand&&l<_r) l++;
        while(a[r]>stand&&r>_l) r--;
        if(l<=r)
            swap(a[l++],a[r--]);
    }
    if(l<_r)
        quickSort(a,_l,l);
    if(r>_l)
        quickSort(a,r,_r);
}
void QuickSort(int *Array,int Left,int Right)
{
    int l=Left;
    int r=Right;
    int stand=Array[(Left+Right)/2];
    while(l<=r)
    {
        while(Array[l]<stand&&l<Right) l++;
        while(Array[r]>stand&&r>Left) r--;
        if(l<=r)
            swap(Array[l++],Array[r--]);
    }
    if(l<Right) QuickSort(Array,l,Right);
    if(r>Left)  QuickSort(Array,Left,r);
}
int arr[5]= {5,4,3,1,2};
int main()
{
    std::ios::sync_with_stdio(false);
    for(int i=0; i<=4; i++)
        cout<<arr[i]<<endl;
    system("pause");
    quickSort(arr,0,4);
    for(int i=0; i<=4; i++)
        cout<<arr[i]<<endl;
    return 0;
}
