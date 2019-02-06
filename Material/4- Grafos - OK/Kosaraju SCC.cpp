int n, m;
vector<int> g[MAXN];
vector<int> t[MAXN];//grafo transposto
char vis[MAXN];
stack<int> p;

void dfs(int u, int op){
	vis[u] = 1;
	
	int v;
	if(op == 1){
		for (int i = 0; i < g[u].size(); i++)
		{
			v = g[u][i];
			if(!vis[v]){
				dfs(v, op);
			}
		}
		p.push(u);
	}else{
		for (int i = 0; i < t[u].size(); i++)
		{
			v = t[u][i];
			if(!vis[v]){
				dfs(v, op);
			}
		}
	}
}

int kosaraju(){//retorna quantas componentes fortemente conexas existe
	memset(vis, 0, sizeof vis);
	
	while (!p.empty())
		p.pop();
	
	for (int i = 0; i < n; i++)
	{
		if(!vis[i]) dfs(i, 1);
	}
	
	int u;
	int qtd = 0;
	memset(vis, 0, sizeof vis);
	while (!p.empty())
	{
		u = p.top();
		p.pop();
		if(!vis[u]){
			qtd++;
			dfs(u, 0);
		}
	}
	
	return qtd;
}

void reset(){
	for (int i = 0; i < n; i++)
	{
		g[i].clear();
		t[i].clear();
	}
}

int main(){
	reset();
	//le o grafo normal e transposto
	int ans = kosaraju();
	
	return 0;
}
