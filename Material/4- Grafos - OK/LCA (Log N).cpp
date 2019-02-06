const ll N = 30100;
const ll M = log2(N) + 2;
ll lca[N][M], h[N];
ll minAresta[N][M];

void dfs(ll x, ll ult, ll peso_ult_x) {
	lca[x][0] = ult;
	minAresta[x][0] = peso_ult_x;
	
	for(ll i = 1; i < M; ++i){
		lca[x][i] = lca[lca[x][i - 1]][i - 1];
		minAresta[x][i] = min(minAresta[x][i-1], minAresta[lca[x][i-1]][i-1]);
	}
	ll y;
	for(ll i=0; i<g[x].size(); i++) {
		y = g[x][i].first;
		if(y == ult) continue;
		h[y] = h[x] + 1;
		dfs(y, x, g[x][i].second);
	}
}

ll getLca(ll a, ll b) {
	menorAresta = 10000000;
	if(h[a] < h[b]) swap(a, b);
	ll d = h[a] - h[b];
	for(ll i = M - 1; i >= 0; --i){
		if((d >> i) & 1){
			menorAresta = min(menorAresta, minAresta[a][i]);
			a = lca[a][i];
		}
	}
	if(a == b) return a;
	for(ll i = M - 1; i >= 0; --i){
		if(lca[a][i] != lca[b][i]){
			menorAresta = min(menorAresta, minAresta[a][i]);
			menorAresta = min(menorAresta, minAresta[b][i]);
			a = lca[a][i];
			b = lca[b][i];
		}
	}
	menorAresta = min(menorAresta, minAresta[a][0]);
	menorAresta = min(menorAresta, minAresta[b][0]);
	return lca[a][0];
}
