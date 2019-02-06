#include <bits/stdc++.h>

using namespace std;

#define N 3030
#define M 101010
#define inf 101010101010101LL
#define in(a, b) a
#define out(a, b) a+b
#define F first
#define S second

typedef long long int ll;
typedef pair<ll, ll> ii;

struct ed{
	ll to, c, f, cost;
}edge[M];


ll n, k, dist[N], p[N], seen[N], curr, s, t;
vector<int> adj[N];

void add_edge(ll a, ll b, ll c, ll cost){//arestas indo com custo positivo, e voltando com custo negativo
	
	edge[curr] = {b, c, 0, cost};
	adj[a].push_back(curr++);
	
	edge[curr] = {a, 0, 0, -cost};
	adj[b].push_back(curr++);
}


void build_graph(){
	
	s = curr = 0;
	t = N-2;
	//modelagem do grafo
}

ll augment(){
	ll mf = inf;
	ll ans = 0;
	for(ll u = t, e = p[u]; u!=s; u = edge[e^1].to, e = p[u]){
		mf = min(mf, edge[e].c - edge[e].f);
	}
	for(ll u = t, e = p[u]; u!=s; u = edge[e^1].to, e = p[u]){
		ans += mf*edge[e].cost;
		edge[e].f+=mf;
		edge[e^1].f-=mf;
	}
	return ans;
}

ll SPF(){
	
	for(ll i=0; i<N; i++) dist[i] = inf;
	p[s] = p[t] = -1;
	
	dist[s] = 0;  seen[s] = 1;
	queue<int> q; q.push(s);
	
	while(q.size()){
		
		ll u = q.front(); q.pop();
		
		seen[u] = 0;
		for(ll i=0; i<adj[u].size(); i++){
			ll e = adj[u][i];
			ll v = edge[e].to;
			ll w = edge[e].c - edge[e].f;
			
			if(w>0 && dist[v] > dist[u]+edge[e].cost){
				dist[v] = dist[u]+edge[e].cost;
				p[v] = e;
				if(!seen[v]){
					seen[v] = 1;
					q.push(v);
				}
			}
		}
		
	}
	
	if(p[t] == -1) return inf;
	return augment();
	
}

ll MCMF(){
	ll ans = 0;
	while(1) {
		ll a = SPF();
		if(a == inf) break;
		ans+=a;
	}
	return ans;
}


int main(){
	
	
	//leitura do grafo
	
	build_graph();
	
	ll x = MCMF();
	
	//
}
