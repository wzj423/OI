#include <iostream>
#include <cstring>
#define MAX 101
using namespace std;
int map[MAX][MAX];
int main()
{
    int n, i, j, temp, k;
    
    while(scanf("%d", &n) != EOF)
    {
        memset(map, 0, sizeof(map));
        for(i = 1; i <= n; i++)
            for(j = 1; j <= n; j++)
            {
                scanf("%d", &temp);
                map[i][j] += map[i][j - 1] + temp;//这里表示第i行的前j列之和
            }
        int max = -100000;
        for(i = 1; i <= n; i++)
            for(j = i; j <= n; j++)
            {
                int sum = 0;
                for(k = 1; k <= n; k++)
                {
                    if(sum < 0)
                        sum = 0;
                    sum += map[k][j] - map[k][i  - 1];//这里表示前k行，i->j列之和
                    if(sum > max)
                        max = sum;
                }
            }
        printf("%d\n", max);
    }
return 0;
}