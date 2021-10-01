#include <bits/stdc++.h>

using namespace std;
int N,a[5000010],K;
int main() {
	scanf("%d",&N);
	for(int i=1;i<=N;++i) scanf("%d",a+i),K^=a[i];
	if(!K) {
		puts("lose");
		return 0;
	}
	for(int i=1;i<=N;++i) {
		if((a[i]^K)<a[i]) {

			printf("%d %d\n",a[i]-(a[i]^K),i);
			a[i]^=K;
			break;
		}
	}
	for(int i=1;i<=N;++i) printf("%d ",a[i]);
	puts("");
//	cout<<K<<endl;
//	int t;
//	for(t=31;t>=0;--t) if((K>>t)) break;
//	cout<<t<<endl;
	return 0;
}
