#include <bits/stdc++.h>

using namespace std;

#define N 10040//depende do problema
#define M 1010101//depende do problema
#define inf 10101010//depende do problema

struct ed{
	int to, c, f;
}edge[M];


int n, curr, seen[N], tempo, s, t;
vector<int> adj[N];


void add_edge(int a, int b, int c, int r){
	
	edge[curr].to = b;
	edge[curr].c = c;
	edge[curr].f = 0;
	adj[a].push_back(curr++);
	
	edge[curr].to = a;
	edge[curr].c = r;
	edge[curr].f = 0;
	adj[b].push_back(curr++);
}


void build_graph(){
	
	s = curr = 0;
	t = N-2;
	//modelagem do grafo
}

int dfs(int u, int f){
	
	if(u == t) return f;
	
	seen[u] = tempo;
	
	for(int i=0; i<adj[u].size(); i++){
		int e = adj[u][i];
		int v = edge[e].to;
		int w = edge[e].c - edge[e].f;
		
		if(seen[v]<tempo && w>0){
			if(int a = dfs(v, min(f, w))){
				edge[e].f+=a;
				edge[e^1].f-=a;
				return a;
			}
		}
	}
	return 0;
}


int ford_fulk(){
	
	memset(seen, 0, sizeof seen);
	tempo = 1;
	int flow = 0;
	
	while(int a = dfs(s, inf)){
		flow+=a;
		tempo++;
	}
	return flow;
}


int main(){
	
	
	//le grafo
	
	//monta o grafo
	
	build_graph();
	
	int mf = ford_fulk();
}
