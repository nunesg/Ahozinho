/*
 * 	Cf 161D : quantos pares de vertices com distancia = k
 */

#include <bits/stdc++.h>

using namespace std;

#define N 101010

typedef long long int ll;

int n, k, dist[N], h[N], sz[N], block[N];
ll answer;
vector<int> adj[N];


void build_sz(int u, int p){
	sz[u] = 1;
	for(int v : adj[u]){
		if(v == p || block[v]) continue;
		build_sz(v, u);
		sz[u]+=sz[v];
	}
}

int find_centroid(int u, int p, int tam){
	for(int v : adj[u]){
		if(v == p || block[v]) continue;
		if(sz[v]*2 > tam) return find_centroid(v, u, tam);
	}
	return u;
}

void dfs(int u, int p, int d){
	dist[d]++;
	for(int v : adj[u]){
		if(v == p || block[v]) continue;
		dfs(v, u, d+1);
	}
}

void solve(int u, int p, int d){
	
	if(d>=k) return;
	answer+= (ll)dist[k-d];
	for(int v : adj[u]){
		if(v == p || block[v]) continue;
		solve(v, u, d+1);
	}
}

void decompose(int u){
	
	build_sz(u, u);
	u = find_centroid(u, u, sz[u]);
	block[u] = 1;
	
	for(int v : adj[u]){
		if(block[v]) continue;
		solve(v, u, 1);
		dfs(v, u, 1);
	}
	
	answer+= (ll)dist[k];
	for(int i=1; dist[i] > 0; i++) dist[i] = 0;
	
	for(int v : adj[u]){
		if(block[v]) continue;
		decompose(v);
	}
}


int main(){
	
	int a, b;
	scanf("%d %d", &n, &k);
	for(int i=1; i<n; i++){
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	answer = 0;
	decompose(1);
	printf("%lld\n", answer);
}
