#include <bits/stdc++.h>

using namespace std;

#define N 101010

int n, sa[N], tmpsa[N], rk[N], tmprk[N], cont[N], lcp[N], inv[N];
string s;

void radix(int  k){
	
	memset(cont, 0, sizeof cont);
	int maxi = max(300, n);
	
	for(int  i=0; i<n; i++){
		cont[ (i+k)<n ?  rk[i+k] : 0 ]++;
	}
	
	for(int  i=1; i<maxi; i++) cont[i]+=cont[i-1];
	
	for(int  i=n-1; i>=0; i--){
		tmpsa[ --cont[ ( sa[i]+k ) < n   ?  rk[sa[i]+k] : 0 ] ] = sa[i];
	}
	for(int  i=0; i<n; i++) sa[i] = tmpsa[i];
}


void build_SA(){
	
	for(int  i=0; i<n; i++){
		rk[i] = s[i];
		sa[i] = i;
	}
	
	for(int  k=1; k<n; k<<=1){
		
		radix(k);
		radix(0);
		
		tmprk[sa[0]] = 0;
		int  r = 0;
		for(int  i=1; i<n; i++){
			tmprk[sa[i]] = (rk[sa[i]] == rk[sa[i-1]] && rk[sa[i]+k] == rk[sa[i-1]+k]) ? r : ++r;
		}
		
		for(int  i=0; i<n; i++){
			rk[sa[i]] = tmprk[sa[i]];
		}
		
		if(rk[sa[n-1]] == n-1) break;
	}
	
}

void build_lcp(){
	
	for(int  i=0; i<n; i++){
		inv[sa[i]] = i;
	}
	int  L=0;
	for(int  i=0; i<n; i++){
		if(inv[i] == 0){
			lcp[inv[i]] = 0;
			continue;
		}
		int  prev = sa[inv[i]-1];
		while(i+L<n && prev+L<n && s[i+L] == s[prev+L]) L++;
		
		lcp[inv[i]] = L;
		L = max(L-1, 0);
	}
}


int  solve(){
	//depende do problema
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	getline(cin, s);
	s.push_back('$');
	
	n = s.size();
	
	build_SA();
	build_lcp();
	
	solve();
}
