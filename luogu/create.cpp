#include <bits/stdc++.h>

using namespace std;
string target = "space";
int N, M, dataid;
int main( int argc, char *argv[] )
{
    srand( time( 0 ) );
    dataid = atoi( argv[1] );
    target += char( dataid + '0' );
    target += ".in";
    puts( target.c_str() );
    freopen( target.c_str(), "w+", stdout );
    printf( "%s %s\n", argv[2], argv[3] );
    N = atoi( argv[2] );
    M = atoi( argv[3] );
    for( int i = 1; i <= M; ++i ) {
        int flag = rand() % 3 + 1;
        printf( "%d ", flag );
        if( flag == 1 ) {
            int pos, x, y, v;
            pos = rand() % ( N ) + 1, x = rand() % 3 + 1, y = rand() % 3 + 1, v = rand();
            printf( "%d %d %d %d\n", pos, x, y, v );
        } else if( flag == 2 ) {
            int pos = rand() % ( N - 1 ) + 1;
            printf( "%d\n", pos );
            ++N;
        } else {
            int l=rand()%N+1,r=rand()%N+1,dest=rand()%3+1;
            if(l>r) swap(l,r);
            printf("%d %d %d\n",l,r,dest);
        }
    }
    return 0;
}
