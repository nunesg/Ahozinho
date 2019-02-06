//responde qual vertice alcanca a maior quantidade de vertices num grafo com N<=100000

#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define GRAY 1
#define BLACK 2

int n, m, seen[N], low[N], dp[N], in[N], comp[N], sz[N], tempo, comp_cont;
vector<int> adj[N], g[N];//adj eh o grafo normal, g eh o grafo das componentes
stack<int> pilha;

void tarjan_scc(int u, int op){//op == 0: calcula as scc de cada vertice, op == 1: monta o grafo das scc
	
	seen[u] = GRAY;
	in[u] = low[u] = tempo++;
	pilha.push(u);
	
	for(int v : adj[u]){
		if(seen[v] == BLACK) {
			if(op == 1)   g[comp[u]].push_back(comp[v]);
			continue;
		}
		
		if(!seen[v]){
			tarjan_scc(v, op);
			
			if(op == 1 && seen[v] == BLACK){
				g[comp[u]].push_back(comp[v]);
			}

			low[u] = min(low[v], low[u]);
		}else low[u] = min(low[u], in[v]);
	}
	
	if(low[u] == in[u]){
		comp_cont++;

		while(pilha.size()){
			int v = pilha.top(); pilha.pop();
			seen[v] = BLACK;
			
			if(!op) comp[v] = comp_cont;
			if(!op) sz[comp_cont]++;


			if(u == v) break;
		}
	}
	
}


void build_tarjan(int op){
	memset(seen, 0, sizeof seen);
	comp_cont=tempo=0;
	
	for(int i=1; i<=n; i++){
		if(!seen[i]) tarjan_scc(i, op);
	}
	
	if(!op) return;
	
	for(int i=1; i<=comp_cont; i++){//tira as arestas repetidas do grafo das scc
		if(!g[i].size()) continue;
		
		sort(g[i].begin(), g[i].end());
		
		g[i].resize( distance( g[i].begin(),  unique(g[i].begin(), g[i].end())  ) );//tira repetições
	}
}


void solve(int u){
	if(dp[u]!=0) return;
	dp[u] = sz[u];
	for(int v : g[u]){
		solve(v);
		dp[u]+=dp[v];
	}
}


int main(){
	int a, b, op;
	scanf("%d %d", &n, &m);
	for(int i=0; i<m; i++){//recebe um grafo direcionado
		scanf("%d %d %d", &a, &b, &op);
		adj[a].push_back(b);
		if(op == 2) adj[b].push_back(a);
	}
	
	build_tarjan(0);
	build_tarjan(1);
	memset(dp, 0, sizeof dp);
	
	for(int i=1; i<=comp_cont; i++) solve(i);
	
	int ans=1;
	for(int i=1; i<=n; i++){
		if(dp[comp[i]] > dp[comp[ans]]) ans=i;
	}
	
	printf("%d\n", ans);
}
