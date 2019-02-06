/*
 * 	dp[mask][i] = quantas submasks X existem tais que X e mask só se diferenciam nos primeiros i bits
 * 	F[mask] = quantas submasks X existem tal que X&mask == X
 */

#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define M 21

int n, vet[N], freq[1<<M];
int dp[1<<M][M+1];
int F[1<<M];

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tc;
	cin >> tc;
	
	while(tc--){
		cin >> n;
		for(int i=0; i<n; i++){
			cin >> vet[i];
			freq[vet[i]]++;
		}
		
		//SOS		
		memset(dp, 0, sizeof dp);
		for(int mask=0; mask<(1<<M); mask++){
			dp[mask][0] = freq[mask];
			for(int i=1; i<=M; i++){
				if(mask&(1<<(i-1))) dp[mask][i] = dp[mask^(1<<(i-1))][i-1];
				dp[mask][i] += dp[mask][i-1];
			}
		}
		
		//economizando memoria
		memset(F, 0, sizeof F);
		for(int mask=0; mask<(1<<M); mask++){
			F[mask] = freq[mask];
		}
		
		for(int i=1; i<=M; i++){
			for(int mask = 0; mask<(1<<M); mask++){
				if(mask&(1<<(i-1))) F[mask]+= F[mask^(1<<(i-1))];
			}
		}		
	}
}
