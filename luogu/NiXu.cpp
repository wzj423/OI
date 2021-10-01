#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>
using namespace std;

int N;
long long ans;
int a[500100],b[500100];
void merge_sort(int L,int R)
{
    if (L==R) return ;
    int mid = (L+R)>>1;
    merge_sort(L,mid);
    merge_sort(mid+1,R);
    int i = L, j = mid+1, k = L ;
    while (i<=mid && j<=R)
        if (a[i]<=a[j]) b[k++] = a[i++];
        else ans += mid-i+1, b[k++] = a[j++];
    while (i<=mid) b[k++] = a[i++];
    while (j<=R) b[k++] = a[j++];
    for (i=L; i<=R; ++i) a[i] = b[i];
}
int main()
{
    scanf("%d",&N);
    for (int i=1; i<=N; ++i)
        scanf("%d",&a[i]);
    merge_sort(1,N);
    printf("%lld",ans);
    return 0;
}