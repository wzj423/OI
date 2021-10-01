#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#define _TEST
#ifdef _TEST
#define TEST while(0)
#else
#define TEST
#endif // _TEST
using namespace std;
#define index id
struct p
{
    int id;
    int power;
    int score;
};
bool operator > (p a,p b)
{
    if(a.score==b.score)
        return a.id<b.id;
    else
        return a.score>b.score;
}

p people[2*100010],help[2*100010];
void MergeSort(int L,int R)
{
    if(L>=R)//Error1
        return;
    int l=L,r,mid=(L+R)/2;
    MergeSort(L,mid);
    MergeSort(mid+1,R);
    for(int i=L; i<=R; i++)
        help[i]=people[i];
    r=mid+1;
    for(int i=L; i<=R; i++)
    {
        if(l<=mid&&(r>/*=*/R||help[l]>help[r]))//Error2
            people[i]=help[l++];
        else
            people[i]=help[r++];
    }
}
int N,R,Q;

int main()
{
    std::ios::sync_with_stdio(false);
    cin>>N>>R>>Q;
    for(int i=1; i<=2*N; i++)
    {
        cin>>people[i].score;
        people[i].index=i;

    }
    for (int i=1; i<=2*N ; i++ )
    {
        cin>>people[i].power;
    }
        MergeSort(1,2*N);
    for (int i=1;i<=R;i++ )
    {
        for (int j=1;j<=2*N;j+=2)
        {
            if(people[j].power>people[j+1].power)
                people[j].score++;
            else
                people[j+1].score++;
        }
        MergeSort(1,2*N);
    }
    MergeSort(1,2*N);
    cout<<people[Q].id<<endl;
    TEST for(int i=1; i<=2*N; i++)
    {
        cout<<people[i].index<<" "<<people[i].score<<" "<<people[i].power<<endl;
    }
    return 0;
}
