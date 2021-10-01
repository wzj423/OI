#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 201
#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))

int n, ans = ~(1 << 31);
int f[N][40001], sum[N];
//f[i][j]表示前i个人，A队打饭时间为j的最优解

struct node
{
    int a, b;
} p[N];

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + ch - '0';
    return x * f;
}

inline bool cmp(node x, node y)
{
    return x.b > y.b;
}

int main()
{
    int i, j, k;
    n = read();
    for(i = 1; i <= n; i++)
    {
        p[i].a = read();
        p[i].b = read();
    }
    std::sort(p + 1, p + n + 1, cmp);
    for(i = 1; i <= n; i++) sum[i] = sum[i - 1] + p[i].a;
    memset(f, 127 / 3, sizeof(f));
    f[0][0] = 0;
    for(i = 1; i <= n; i++)
        for(j = 0; j <= sum[i - 1]; j++)
        {
            f[i][j] = min(f[i][j], max(f[i - 1][j], sum[i - 1] - j + p[i].a + p[i].b));
            f[i][j + p[i].a] = min(f[i][j + p[i].a], max(f[i - 1][j], j + p[i].a + p[i].b));
        }
    for(i = 1; i <= n; i++)
        for(j = 0; j <= sum[i - 1]; j++)
        {
            printf("f[%d][%d]=%d\n",i,j,f[i][j]);
        }
    for(i = 0; i <= sum[n]; i++) ans = min(ans, f[n][i]);
    printf("%d\n", ans);
    return 0;
}