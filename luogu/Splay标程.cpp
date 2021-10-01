#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 1e5 + 10;
const int MAX_MAT = 4, mod = 1e9 + 7;
int N, M;
// code
//matrix
struct mat {
    ll a[5][5];
    mat() {
        memset( a, 0, sizeof a );
        for( int i = 1; i <= MAX_MAT; ++i )
            a[i][i] = 1;
    }
    void display(int prespace=0) {
        for( int i = 1; i <= MAX_MAT; ++i ) {
            for(int j=1;j<=prespace;++j)
                printf(" ");
            for( int j = 1; j <= MAX_MAT; ++j )
                printf( "%lld ", a[i][j] );
            puts( "" );
        }
    }
};

mat operator *( mat x, mat y ) {
    mat ret;
    for( int i = 1; i <= MAX_MAT; ++i )
        for( int j = 1; j <= MAX_MAT; ++j )
            for( int k = 1; k <= MAX_MAT; ++k )
                ret.a[i][j] = ( ret.a[i][j] + x.a[i][k] * y.a[k][j] ) % mod;
    return ret;
}
//splay
struct node {
    int father, ch[2];
    int sum;
    mat mul, vv;
};
struct SPLAY {
    node e[MAXN * 4];
    int cnt;
#define root e[0].ch[1]
#define lson(x) (e[x].ch[0])
#define rson(x) (e[x].ch[1])
#define dad(x)  (e[x].father)
    void connect( int x, int f, int son ) {
        dad( x ) = f;
        e[f].ch[son] = x;
    }
    void update( int x ) {
        e[x].sum = e[lson( x )].sum + e[rson( x )].sum + 1;
        e[x].mul = e[lson( x )].mul * e[x].mul * e[rson( x )]. mul;
    }
    /*void pushdown( int x ) {
        if( x && e[x].rtag ) {
            e[lson( x )].rtag ^= 1, e[rson( x )].rtag ^= 1;
            swap( lson( x ), rson( x ) );
            e[x].rtag = 0;
        }
    }*/
    int verify( int x ) {
        return rson( dad( x ) ) == x;
    }
    int create( int father ) {
        e[++cnt].father = father, e[cnt].sum = 1;
        return cnt;
    }
    int getroot() {
        return root;
    }
    void rotate( int x ) {
        int y = dad( x ), yson = verify( x );
        int mroot = dad( y ), mrootson = verify( y );
        int B = e[x].ch[yson ^ 1];
        connect( B, y, yson ), connect( y, x, yson ^ 1 ), connect( x, mroot, mrootson );
        update( y ), update( x );
    }
    void build( int L, int R, int father = 0, bool rela = 1 ) {
        if( L > R ) return;
        //printf("build in [%d,%d] father=%d father value=%d\n",L,R,father,e[father].vv);
        int mid = ( L + R ) >> 1, pos = create( father );
        if( rela )  rson( father ) = pos;
        else      lson( father ) = pos;
        if( L == R )    return;
        build( L, mid - 1, pos , 0 ), build( mid + 1, R, pos, 1 );
        update( pos );
    }
    void display( int now , int dep = 0 ) {
        if( lson( now ) )   display( lson( now ) , dep + 1 );
        for( int i = 1; i <= dep; ++i ) printf( " " );
        printf( " id=%d sum=%d\n", now, e[now].sum);
        for( int i = 1; i <= dep; ++i ) printf( " " );
        printf("mul matrix:\n");
        for( int i = 1; i <= dep; ++i ) printf( " " );
        e[now].mul.display(dep);
        for( int i = 1; i <= dep; ++i ) printf( " " );
        printf("vv matrix\n");
        for( int i = 1; i <= dep; ++i ) printf( " " );
        e[now].vv.display(dep);
        if( rson( now ) )   display( rson( now ) , dep + 1 );
    }
    void splay( int at, int to ) {
        to = dad( to );
        int up;
        while( ( up = dad( at ) ) != to )
            if( dad( up ) == to ) rotate( at );
            else    rotate( verify( up ) == verify( at ) ? up : at ), rotate( at );
    }
    int atrank( int k ) {
        int now = root;
        while( true ) {
            int minused = e[lson( now )].sum + 1;
            if( k == minused )  return now;
            if( k < minused )   now = lson( now );
            else    k -= minused, now = rson( now );
        }
        return 0;
    }
    void update_chain(int x)
    {
        if(x)       update(x);
        if(x!=root) update_chain(dad(x));
    }
    void modify(int rank,int x,int y,int v)
    {
        int id=atrank(rank);
        e[id].vv.a[x][y]+=v;
        update_chain(id);
    }
    void insert(int rank)///在rank后面新建一个节点
    {
        int lid=atrank(rank),rid=atrank(rank+1);
        splay(lid,root);
        splay(rid,rson(root));
        lson(rid)=create(rid);
        update_chain(lson(rid));
    }
    /*void rever( int L, int R ) { //(L,R)
        splay( L, root ), splay( R, rson( L ) );
        //display(getroot());puts("");
        e[lson( R )].rtag ^= 1;
        //display(getroot());puts("");
    }
    void print( int now ) {
        pushdown( now );
        if( lson( now ) )   print( lson( now ) );
        if( e[now].vv <= N + 1 && e[now].vv >= 2 )    printf( "%d ", e[now].vv - 1 );
        if( rson( now ) )   print( rson( now ) );
    }*/
} S;

int main() {
    scanf( "%d%d", &N, &M );
    S.build( 1, N + 2, S.getroot() );
    S.display(S.getroot());
    // puts("");
    for( int i = 1; i <= M; ++i ) {
    }
    return 0;
}
