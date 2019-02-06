#include <bits/stdc++.h>

using namespace std;

#define N 50500//depende do problema
#define M 10100100//depende do problema
#define inf 10101010

typedef pair<int, int> ii;


struct ed{
	int to, c, f;
}edge[M];

int n, m, ptr[N], dist[N], curr, s, t;
vector<int> adj[N];
queue<int> q;


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

bool bfs(){
	
	q.push(s);
	memset(dist, -1, sizeof dist);
	dist[s] = 0;
	
	while(q.size()){
		int u =q.front(); q.pop();
		
		for(int i=0; i<adj[u].size(); i++){
			int e = adj[u][i];
			int v = edge[e].to;
			int w = edge[e].c - edge[e].f;
			
			if(dist[v] != -1 || w<=0) continue;
			
			q.push(v);
			dist[v] = dist[u]+1;
		}
	}
	
	return dist[t]!=-1;
}


int dfs(int u, int f){
	
	if(u == t) return f;
	
	for(; ptr[u]<adj[u].size(); ptr[u]++){
		
		int e = adj[u][ptr[u]];
		int v = edge[e].to;
		int w = edge[e].c - edge[e].f;
		
		if(dist[v]!=dist[u]+1) continue;
		
		if(w>0){
			if(int a = dfs(v, min(f, w))){
				edge[e].f+=a;
				edge[e^1].f-=a;
				return a;
			}
		}
	}
	return 0;
}


int dinic(){
	
	int flow = 0;
	
	while(1){
		
		if(!bfs()) break;
		
		memset(ptr, 0, sizeof ptr);
		
		while(int a = dfs(s, inf)){
			flow+=a;
		}
	}
	return flow;
}



int main(){
	
	//le grafo
	build_graph();
	
	int mf = dinic();
	
}
