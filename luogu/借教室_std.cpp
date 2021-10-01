#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 2010, V = 310;
int a[N], b[N];
double d[V][V];
double c[N];
double f[N][N][2];
int cnt = 0;
int n, m, v, e;
void init()
{
    for (int i=0; i<V; i++)
        for (int j=0; j<V; j++)
            if (i == j) d[i][j] = 0;
            else d[i][j] = 1e9;
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            f[i][j][0] = f[i][j][1] = 1e9;
    f[1][0][0] = 0; f[1][1][1] = 0;
}
void floyd()
{
    for (int k=1; k<=v; k++)
        for (int i=1; i<=v; i++)
            for (int j=1; j<=v; j++)
                if (d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j];
}
int main()
{
    scanf("%d%d%d%d", &n, &m, &v, &e);
    for (int i=1; i<=n; i++) scanf("%d", &a[i]);
    for (int i=1; i<=n; i++) scanf("%d", &b[i]);
    for (int i=1; i<=n; i++) scanf("%lf", &c[i]);
    init();
    for (int i=1; i<=e; i++)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        if (x == y) continue;
        if (z < d[x][y]) d[x][y] = z;
        d[y][x] = d[x][y]; //注意题目里说的会有重边的问题。
    }
    floyd();
    printf("%d->%d=%d\n",2,1,d[2][1]);
    printf("%d->%d=%d\n",2,2,d[2][2]);
    for (int i=2; i<=n; i++)
    {
        f[i][0][0] = f[i-1][0][0] + d[a[i-1]][a[i]];
        for (int j=1; j<=min(m, i); j++)
        {
            f[i][j][0] = min(f[i-1][j][0] + d[a[i-1]][a[i]], f[i-1][j][1] + d[a[i-1]][a[i]] * (1.0-c[i-1]) + d[b[i-1]][a[i]] * c[i-1]);
            f[i][j][1] = f[i-1][j-1][0] + d[a[i-1]][a[i]] * (1.0-c[i]) + d[a[i-1]][b[i]] * c[i];
            double t = f[i-1][j-1][1] + d[a[i-1]][a[i]] * (1.0-c[i-1]) * (1.0-c[i]);
            t += d[b[i-1]][a[i]] * c[i-1] * (1.0-c[i]);
            t += d[a[i-1]][b[i]] * (1.0-c[i-1]) * c[i];
            t += d[b[i-1]][b[i]] * c[i-1] * c[i];
            f[i][j][1] = min(f[i][j][1], t); //式子太长分开写。
            printf("%.2f %.2f\n",f[i][j][0],f[i][j][1]);
        }
    }
    double ans = f[n][0][0];
    for (int i=1; i<=m; i++)
    {
        ans = min(ans, min(f[n][i][0], f[n][i][1]));
        printf("%.2f %.2f \n",f[n][i][0],f[n][i][1]);
    }
    printf("%.2lf", ans);
    system("pause");
    return 0;
}