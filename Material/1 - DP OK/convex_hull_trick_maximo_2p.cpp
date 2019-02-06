#include <bits/stdc++.h>

using namespace std;

#define N 1010100

typedef long long int ll;

struct line{
	ll a, b;
	line(){a=b=0;}
	line(ll i, ll j) : a(i), b(j) {}
	
	ll value_at(ll x){
		return a*x + b;
	}
};


struct cht{
	
	int sz, pos;
	vector<line> ch;
	
	cht(){ch.clear(); sz=pos=0;}
	
	bool can_pop(line ant, line top, line at){
		return (top.b - ant.b)*(ant.a - at.a) >= (at.b - ant.b)*(ant.a - top.a);
	}
	
	void add_line(line L){
		while(sz>1 && can_pop(ch[sz-2], ch[sz-1], L)){
			ch.pop_back();
			sz--;
		}
		ch.push_back(L);
		sz++;
	}
	
	ll query(int x){
		int ans = sz-1;
		for(int i=pos; i<sz-1; i++){
			if(ch[i].value_at(x) < ch[i+1].value_at(x)) pos++;
			else{
				ans=i;
				break;
			}
		}
		return ch[ans].value_at(x);
	}
	
};


cht CH;
ll n, dp[N], acc[N];


int main(){
	
	ll a, b, c, tc;
	
	scanf("%lld", &tc);
	while(tc--){
		
		scanf("%lld", &n);
		scanf("%lld %lld %lld", &a, &b, &c);
		for(int i=1; i<=n; i++){
			scanf("%lld", &acc[i]);
			acc[i]+=acc[i-1];
		}
		
		CH = cht();
		dp[0] = 0;
		CH.add_line(line(0, 0));
		for(int i=1; i<=n; i++){
			dp[i] = CH.query(acc[i]) + c + a*acc[i]*acc[i] + b*acc[i];
			CH.add_line(line(-2*a*acc[i],  dp[i]+a*acc[i]*acc[i]-b*acc[i]));
		}
		
		printf("%lld\n", dp[n]);
	}
	
	
}
