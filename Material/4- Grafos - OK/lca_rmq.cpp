//SPOJ LCA

#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define M 22

int n, vet[N<<1], in[N], h[N<<1], dist[N], grau[N], table[N][M], tempo;
vector<int> adj[N];

void dfs(int u, int d, int pai){
	
	in[u] = tempo;
	h[tempo] = dist[u] = d+1;
	vet[tempo++] = u;
	
	for(int v : adj[u]){
		if(v == pai) continue;
		dfs(v, d+1, u);
		h[tempo] = d+1;
		vet[tempo++] = u;
	}
}

void build_table(){
	int sz = tempo;
	for(int i=0; i<sz; i++) table[i][0] = vet[i];
	for(int j=1; j<M; j++){
		for(int i=0; i+(1<<j)<=sz; i++){
			int u = table[i][j-1];
			int v = table[i+(1<<(j-1))][j-1];
			table[i][j] = (dist[u] < dist[v]) ? u : v;
		}
	}
}

int query(int l, int r){
	int k = 31 - __builtin_clz(r-l+1);
	int u = table[l][k];
	int v = table[r-(1<<k)+1][k];
	return (dist[u] < dist[v]) ? u : v;
}

int get_lca(int u, int v){
	if(in[u] > in[v]) swap(u, v);
	return query(in[u], in[v]);
}

int main(){
	int tc, t=1;
	cin >> tc;
	while(tc--){
		scanf("%d", &n);
		for(int i=1; i<=n; i++) adj[i].clear();
		memset(grau, 0, sizeof grau);
		int a, b, x, y;
		for(int i=1; i<=n; i++){
			
			scanf("%d", &x);
			for(int j=0; j<x; j++){
				scanf("%d", &a);
				adj[i].push_back(a);
				grau[a]++;
			}
		}
		tempo=1;
		for(int i=1; i<=n; i++) if(grau[i]==0) dfs(i, 0, 0);
		
		build_table();
		
		
		int q;
		scanf("%d", &q);
		printf("Case %d:\n", t++);
		for(int i=0; i<q; i++){
			scanf("%d %d", &a, &b);
			printf("%d\n", get_lca(a, b));
		}
		
	}
}
