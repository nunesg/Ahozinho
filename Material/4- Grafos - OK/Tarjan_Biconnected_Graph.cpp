#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define GRAY 1

int n, seen[N], in[N], low[N], id[N], tempo, bridges, diametro;
vector<int> adj[N], tr[N];//tr: arvore das componentes biconectadas
stack<int> pilha;

void tarjan(int u, int p, int op){//op == 0: calcula pra cada vertice qual componente que ele faz parte (id)
	
	seen[u] = GRAY;
	in[u] = low[u] = tempo++;
	
	if(!op) pilha.push(u);
	
	for(int v : adj[u]){
		if(v == p) continue;
		
		if(!seen[v]){
			tarjan(v, u, op);
			
			if(!op && low[v] > in[u]){
				while(pilha.size()){
					int x = pilha.top(); pilha.pop();
					id[x] = v;
					if(v == x) break;
				}
			}
			if(op && low[v]>in[u]){
				tr[id[u]].push_back(id[v]);
				tr[id[v]].push_back(id[u]);
			}
			
			low[u] = min(low[u], low[v]);
		}else low[u] = min(low[u], in[v]);
	}
}

void build_tarjan(int op){
	tempo = bridges = 0;
	memset(seen, 0, sizeof seen);
	
	tarjan(1, 0, op);
	
	if(op) return;
	while(pilha.size()){
		int x = pilha.top(); pilha.pop();
		id[x] = 1;
	}
}

int main(){
	
	int a, b, tc, m;
	scanf("%d %d", &n, &m);
	for(int i=0; i<m; i++){
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	build_tarjan(0);
	build_tarjan(1);
	
	//processa a arvore
}
