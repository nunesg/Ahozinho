int n, m;
int g[600][600];
int origem, destino;
set<int> parent[600];
char vis[600];
int dist[600];

void solve(int atual, int nxt){
	if(atual == origem){
		cout << origem << "\n";
		return;
	}
	
	cout << atual << " ";
	for (auto i : parent[atual])
	{
		int v = i;
		solve(v, atual);
	}
}

int dij(){
	priority_queue<pair<int, int> >pq;
	pq.push(mp(0, origem));
	parent[origem].insert(origem);
	dist[origem] = 0;
	
	int u, w, v;
	while (!pq.empty())
	{
		u = pq.top().S;
		pq.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		
		if(u==destino) return dist[destino];
		for (int i = 0; i < n; i++)
		{
			if(g[u][i]){
				v = i;
				w = g[u][i];
				if(dist[u] + w <= dist[v]){
					if(dist[u] + w < dist[v]) parent[v].clear();//se achou caminho menor: limpa vetor de parent
					parent[v].insert(u);
					dist[v] = dist[u] + w;
					pq.push(mp(-dist[v], v));
				}
			}
		}
		
	}
	return -1;
}

int main()
{
	reset();
	cout << dij() << endl;
	solve(destino, destino);//printa os caminhos invertidos: destino ... origem
	return 0;
}
