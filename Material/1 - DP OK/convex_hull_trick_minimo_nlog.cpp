// ACQUIRE SPOJ

#include <bits/stdc++.h>

using namespace std;

#define N 101010

typedef long long int ll;

struct pt{
	ll x, y;
	pt(){x=y=0;}
	pt(ll a, ll b) : x(a), y(b) {}
};

struct line{
	ll a, b;
	line(){a=b=0;}
	line(ll i, ll j) : a(i), b(j) {}
	
	ll value_at(ll x){
		return a*x + b;
	}
};


struct cht{
	
	int sz;
	vector<line> ch;
	
	cht(){ch.clear(); sz=0;}
	
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
		
		int ini=0, fim = sz-1, meio, ans;
		ans = sz-1;
		
		while(ini<=fim){
			meio = (ini+fim)/2;
			
			if(ch[meio].value_at(x) > ch[meio+1].value_at(x)){
				ini = meio+1;
			}else{
				fim = meio-1;
				ans = meio;
			}
		}
		return ch[ans].value_at(x);
	}
	
};

cht CH;
pt vet[N];
ll n, dp[N];


int main(){
	
	scanf("%lld", &n);
	for(int i=1; i<=n; i++){
		scanf("%lld %lld", &vet[i].x, &vet[i].y);
	}
	
	sort(vet+1, vet+n+1, [](pt a, pt b){ return (a.x != b.x) ? a.x < b.x : a.y > b.y; } );
	
	//inicio preprocessa
	stack<pt> pilha;
	for(int i=1; i<=n; i++){
		while(pilha.size() && pilha.top().y < vet[i].y) pilha.pop();
		pilha.push(vet[i]);
	}
	n = pilha.size();
	for(int i=pilha.size(); i>0; i--) {
		vet[i] = pilha.top();
		pilha.pop();
	}
	//fim preprocessa
	
	dp[0] = 0;
	for(int i=1; i<=n; i++){
		CH.add_line(line(vet[i].y, dp[i-1]));
		dp[i] = CH.query(vet[i].x);
	}
	printf("%lld\n", dp[n]);
	
}
