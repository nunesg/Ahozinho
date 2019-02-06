#include <bits/stdc++.h>

using namespace std;

#define N 2020
#define inf 101010101010101010LL

typedef long long int ll;

int n, opt[N][N];
ll acc[N], dp[N][N];
string answer;

void knuth(){
	
	for(int i=1; i<=n; i++) {
		dp[i][i] = acc[i]-acc[i-1];
		opt[i][i] = i;
	}
	
	for(int s = 2; s<=n; s++){
		for(int l=1; l+s-1<=n; l++){
			int r = l+s-1;
			
			int optL = opt[l][r-1];
			int optR = opt[l+1][r];
			int opt_ = optL;
			ll best = inf;
			
			for(int i=optL; i<=min(optR, r-1); i++){
				if(dp[l][i] + dp[i+1][r] < best){
					best = dp[l][i]+dp[i+1][r];
					opt_ = i;
				}
			}
			if(best == inf) best = 0;
			opt[l][r] = opt_;
			dp[l][r] = best+acc[r]-acc[l-1];
		}
	}
}

void solve(int l ,int r){
	if(r<l) return;
	if(l == r){
		cout << answer << endl;
		return;
	}
	
	answer.push_back('0');
	solve(l, opt[l][r]);
	answer.back()='1';
	solve(opt[l][r]+1, r);
	answer.pop_back();
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	while(cin >> n){
		for(int i=1; i<=n; i++){
			cin >> acc[i];
			acc[i]+=acc[i-1];
		}
		
		knuth();
		solve(1, n);
	}
}
