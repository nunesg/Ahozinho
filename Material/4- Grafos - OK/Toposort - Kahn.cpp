int grauEntrada[MAXN], u, v;
vector<int> g[MAXN];
vector<int> topoSort;
/*
	- Mantem na fila os vertices que nao tem aresta de entrada
	- Remove todas as arestas que saem de u, e diminui o grau de entrada de cada vizinho v de u
	- Se v passou a ter grau de entrada 1, adiciona ele na fila
	- Repete o processo até a fila esvaziar
*/

void Kahn(){
	queue<int> q;
	for (int i = 0; i < n; i++)
	{
		if(grauEntrada[i]==0) q.push(i);
	}
	
	while (!q.empty())
	{
		u = q.front(); q.pop();
		topoSort.pb(u);
		
		for (int i = 0; i < g[u].size(); i++)
		{
			v = g[u][i];
			grauEntrada[v]--;
			if(grauEntrada[v]==0){
				q.push(v);
			}
		}		
		g[u].clear();
	}	
}

void limpa(){
	for (int i = 0; i < n; i++)
	{
		g[i].clear();
		grauEntrada[i]=0;
	}
	nome.clear();
	mapa.clear();
	topoSort.clear();
}

int main()
{
	limpa();
	//monta grafo
	Kahn();
	//percorre topoSort e printa
	return 0;
}
