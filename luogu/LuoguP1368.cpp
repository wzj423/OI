#include <bits/stdc++.h>

using namespace std;
//define====================================
const int MAXN = 300010;

struct _SAM {
    int fa[MAXN * 4], tran[MAXN * 4][30], len[MAXN * 4];
    int last, cnt;
    void insert( int c ) {
        int cur = ++cnt, p = last;
        last = cur, len[cur] = len[p] + 1;
        for( ; p && !tran[p][c]; p = fa[p] ) tran[p][c] = cur;
        if( !p )  fa[cur] = 1;
        else {
            int q = tran[p][c];
            if( len[p] + 1 == len[q] ) fa[cur] = q;
            else {
                int clone = ++cnt;
                len[clone] = len[p] + 1;
                memcpy( tran[clone], tran[q], sizeof( tran[q] ) );
                fa[clone] = fa[q];
                fa[q] = fa[cur] = clone;
                for( ; tran[p][c] == q; p = fa[p] )    tran[p][c] = clone;
            }
        }
    }
};
//code=====================================

//main=====================================
int main()
{

    return 0;
}