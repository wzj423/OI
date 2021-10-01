#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define For(i, a, b) for (i = a; i <= b; i++)
using namespace std;
inline int read() {
    int res = 0; bool bo = 0; char c;
    while (((c = getchar()) < '0' || c > '9') && c != '-');
    if (c == '-') bo = 1; else res = c - 48;
    while ((c = getchar()) >= '0' && c <= '9')
        res = (res << 3) + (res << 1) + (c - 48);
    return bo ? ~res + 1 : res;
}
const int N = 23, C = (1 << 20) + 5, PYZ = 1e8 + 7;
int n, Cm, X[N], Y[N], to[N][N], f[C][N], cnt[C], ans;
bool check(int x1, int y1, int x2, int y2, int x3, int y3) {
    int x4 = x1 - x2, y4 = y1 - y2, x5 = x3 - x2, y5 = y3 - y2;
    if (x1 > x3) swap(x1, x3); if (y1 > y3) swap(y1, y3);
    return x4 * y5 == x5 * y4 && x1 <= x2 && x2 <= x3 && y1 <= y2 && y2 <= y3;
}
int main() {
    int i, j, k; n = read(); For (i, 1, n) X[i] = read(), Y[i] = read();
    For (i, 1, n) For (j, 1, n) if (i != j) For (k, 1, n)
        if (k != i && k != j && check(X[i], Y[i], X[k], Y[k], X[j], Y[j]))
            to[i][j] |= 1 << k - 1; Cm = (1 << n) - 1;
    For (i, 1, Cm) {
        For (j, 1, n) if ((i >> j - 1) & 1) cnt[i]++; For (j, 1, n) {
            if (!((i >> j - 1) & 1)) continue;
            if (cnt[i] == 1) {f[i][j] = 1; continue;}
            For (k, 1, n) if (((i >> k - 1) & 1) && j != k
                && (to[j][k] & i) == to[j][k])
                    f[i][j] = (f[i][j] + f[i ^ (1 << j - 1)][k]) % PYZ;
            if (cnt[i] > 3) ans = (ans + f[i][j]) % PYZ;
        }
    }
    cout << ans << endl; return 0;
}
