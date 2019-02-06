#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define GRAY 1
#define BLACK 2

int n, m, seen[N], low[N], in[N], comp[N], tempo, comp_cont;
vector<int> adj[N];
stack<int> pilha;

void tarjan_scc(int u){
	
	seen[u] = GRAY;
	in[u] = low[u] = tempo++;
	pilha.push(u);
	
	for(int v : adj[u]){
		if(seen[v] == BLACK) continue;
		
		if(!seen[v]){
			tarjan_scc(v);
			
			low[u] = min(low[v], low[u]);
		}else low[u] = min(low[u], in[v]);
	}
	
	if(low[u] == in[u]){
		comp_cont++;
		while(pilha.size()){
			int v = pilha.top(); pilha.pop();
			seen[v] = BLACK;
			comp[v] = comp_cont;
			if(u == v) break;
		}
	}
	
}


int main(){
	int a, b, op;
	scanf("%d %d", &n, &m);
	for(int i=0; i<m; i++){//recebe um grafo direcionado
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
	}
	
	memset(seen, 0, sizeof seen);
	comp_cont=tempo=0;
	
	for(int i=1; i<=n; i++){
		if(!seen[i]) tarjan_scc(i);
	}
	printf("%d\n", comp_cont == 1);//printa 1 se for fortemente conexo
}
