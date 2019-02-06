int n, m;
vector<int> g[MAXN];
char vis[MAXN];
vector<int> ts;

void dfs(int u){
	vis[u] = 1;
	
	int v;
	for (int i = 0; i < g[u].size(); i++)
	{
		v = g[u][i];
		if(!vis[v]){
			dfs(v);
		}
	}
	ts.pb(u);
}

int main(){
	// le o grafo
	// chama dfs
	// ordenação topológica invertida vai estar em ts
	
	
	return 0;
}
