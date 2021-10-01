#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <string>
#include <cstring>
#include <cmath>
#include <cctype>
#include <ctime>

#include <queue>
#include <stack>
#include <algorithm>

using namespace std;
int N;
int a[40010];
int t[40010];
int MergeSort(int l,int r)
{
    //cout<<l<<" "<<r<<endl;
    if(l>=r)
        return 0;
    int mid=(l+r)/2;
    int d1=MergeSort(l,mid);
    int d2=MergeSort(mid+1,r);
    int left=l;
    int right=mid+1;
    int m=r-l+1;
    int ans=0;
    for(int i=l;i<=r;i++)
    {
        if(left>mid)
            t[i]=a[right++];
        else if(right>r)
            t[i]=a[left++];
        else if(a[left]<=a[right])
            t[i]=a[left++];
        else
        {
            t[i]=a[right++];
            ans+=mid-left+1;
        }
    }
    for(int i=l;i<=r;i++)
        a[i]=t[i];
    return ans+d1+d2;
}
int main()
{
    std::ios::sync_with_stdio(false);
    cin>>N;
    for(int i=0;i<N;i++)
        cin>>a[i];
    cout<<MergeSort(0,N-1);
    /*for(int i=0;i<N;i++)
        cout<<a[i]<<" ";*/
    return 0;
}
