//codeforces 660F

#include <bits/stdc++.h>

using namespace std;

#define N 202020
#define inf 1010101010101010LL

typedef long long int ll;

struct line{
	
	ll a, b, id;
	
	line(){ a=b=0;}
	line(ll x, ll y, ll c) : a(x), b(y), id(c) {}
	
	ll value_at(ll x){
		return a*x + b;
	}
	
	double x_intersect(line g){
		return (1.0*(g.b - b))/(1.0*(a - g.a));
	}
	
};

vector< line > ch;
ll n, vet[N], acc[N], aux[N], input[N], dp[N];


bool can_pop(line ant, line top, line at){
	ll p = (ant.b - at.b)*(top.a - ant.a);
	ll q = (ant.b - top.b)*(at.a - ant.a);
	return p>=q;
	
}

void add_line(line at){
	ll sz = ch.size();
	while(sz>1 && can_pop(ch[sz-2], ch[sz-1], at)) {
		ch.pop_back();
		sz--;
	}
	ch.push_back(at);	
}

bool check(ll i, ll x){
	
	ll at = ch[i].value_at(x), ant = ch[i-1].value_at(x);
	if(ant > at) return true;
	return false;
}

ll busca(ll x){
	
	ll ini, fim, meio, meio_, sz = ch.size();
	ini = 1; fim = sz-1;
	
	ll ans=0;
	
	while(ini<=fim){
		
		meio = (ini+fim)/2;
		
		if(check(meio, x)) {
			ini = meio+1;
			ans = meio;
		}else fim = meio-1;
	}
	return ch[ans].value_at(x);
}

int main(){
	
	cin >> n;
	
	for(ll i=1; i<=n; i++){
		scanf("%lld", &input[i]);
		
		acc[i] = acc[i-1]+input[i];
		vet[i] = vet[i-1] + i*input[i];
		aux[i] = aux[i-1]+acc[i];
	}
	
	ll answer=0;
	for(ll i=1; i<=n; i++){
		ll a = i-1;
		ll b = (i==1) ? 0 : -aux[i-2];
		add_line(line(a, b, i));
		
		ll k = busca(acc[i]);
		dp[i] = vet[i] - k;
		if(dp[i] > answer){
			answer = max(answer, dp[i]);
		}
	}
	
	printf("%lld\n", answer);
	
}
