#include <bits/stdc++.h>

using namespace std;

#define N 1010

typedef long long int ll;

ll n, K, pos[N], peso[N], acc[N], acc2[N], dp[2][N];

void build_cost(){
	acc[0] = acc2[0] = 0;
	for(ll i=1; i<=n; i++){
		acc[i] = peso[i]+acc[i-1];
		acc2[i] = acc2[i-1] + peso[i]*pos[i];
	}
}

ll get_cost(ll i, ll j){
	return  pos[j]*(acc[j-1]-acc[i-1]) - (acc2[j-1] - acc2[i-1]);
}

void func(ll at, ll l, ll r, ll optL, ll optR){
	if(l>r) return;
	ll mid = (l+r)>>1;
	ll opt = 1;
	ll best = dp[at^1][mid];
	
	for(ll i=optL; i<=min(mid-1, optR); i++){
		ll c = get_cost(i+1, mid);
		if(dp[at^1][i]+c < best){
			best = dp[at^1][i] + c;
			opt = i;
		}
	}
	
	dp[at][mid] = best;
	
	func(at, l, mid-1, optL, opt);
	func(at, mid+1, r, opt, optR);
}


int main(){
	
	while(scanf("%lld %lld", &n, &K)!=EOF){
	
		for(ll i=1; i<=n; i++){
			scanf("%lld %lld", &pos[i], &peso[i]);
		}
		
		build_cost();
		dp[1][0] = 0;
		for(ll i=1; i<=n; i++){
			dp[1][i] = get_cost(1, i);
		}
		ll at=0;
		for(ll k=2; k<=K; k++){
			func(at, 1, n, 1, n);
			at^=1;
		}
		at^=1;
		printf("%lld\n", dp[at][n]);
	}
}
