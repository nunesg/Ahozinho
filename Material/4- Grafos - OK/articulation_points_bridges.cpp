#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define GRAY 1

int n, m, seen[N], in[N], low[N], tempo, root, bridges, AP;
vector<int> adj[N];

void tarjan(int u, int p){
	
	seen[u] = GRAY;
	in[u] = low[u] = tempo++;
	int any, child=any=0;
	
	for(int v : adj[u]){
		if(v == p) continue;
		
		if(!seen[v]){
			child++;
			tarjan(v, u);
			
			low[u] = min(low[u], low[v]);
			
			if(low[v] >= in[u]) any=1;
			if(low[v] > in[u]) bridges++;
		
		}else low[u] = min(low[u], in[v]);
	}
	
	if(child>1 && u == root) AP++;//caso especial: raiz é um vertice de articulacao
	else if(any && u!=root) AP++;
}


int main(){
	int a, b;
	scanf("%d %d", &n, &m);
	for(int i=0;i<m; i++){
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	root = 1;
	bridges = tempo = AP = 0;
	tarjan(1, 0);
	
	printf("Articulation points: %d\n", AP);
	printf("Bridges: %d\n", bridges);
}
