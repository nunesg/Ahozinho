//~ CONTAR QUANTOS PESOS DISTINTOS TEM NO CAMINHO DE U PRA V

struct query{
	int l, r, lca, pos;
	query(){}
	query(int a, int b, int c, int d){
		l = a;
		r = b;
		lca = c;
		pos = d;
	}
};

query queries[MAXN];
int lca[MAXN][LOG];
int valor[MAXN];
unordered_map<string, int> mapa;
unordered_map<string, int>::iterator it;
vector<int> g[MAXN];
int ini[MAXN];
int fim[MAXN];
int h[MAXN];
int ans[MAXN];
int f[MAXN];
int n, q;
vector<int> euler;
int block_size = 450;
int counter = 0;
int total = 0;
char vis[MAXN];

inline bool compare(const query &a, const query &b){
	if(a.l/block_size == b.l/block_size) return a.r < b.r;
	return a.l < b.l;
}

inline void dfs(int u, int pai){
	lca[u][0] = pai;
	for(int i = 1; i < LOG; i++)
		lca[u][i] = lca[lca[u][i-1]][i-1];
	
	euler.pb(u);
	int v;
	ini[u] = counter++;
	for (int i = 0; i < g[u].size(); i++)
	{
		v = g[u][i];
		if(v==pai) continue;
		h[v] = h[u]+1;
		dfs(v, u);
	}
	fim[u] = counter++;
	euler.pb(u);
}

inline int getLca(int u, int v){
	if(h[u] < h[v]) swap(u, v);
	int dist = abs(h[u]-h[v]);
	
	for (int i = LOG-1; i >= 0; i--)
	{
		if(dist & (1<<i))
			u = lca[u][i];
	}
	if(u==v) return u;
	
	for (int i = LOG-1; i >= 0; i--)
	{
		if(lca[u][i] != lca[v][i]){
			u = lca[u][i];
			v = lca[v][i];
		}
	}
	return lca[u][0];
}

inline void add(int pos){
	int u = euler[pos];
	int val = valor[u];
	if(vis[u]){
		f[val]--;
		if(f[val]==0) total--;
	}else{
		f[val]++;
		if(f[val]==1) total++;
	}
	vis[u] ^= 1;
}

inline void del(int pos){
	add(pos);
}

int main(){
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	
	int nxtIdx=0, u, v;
	string s;
	cin >> n >> q;
	for (int i = 0; i < n; i++)
	{
		cin >> s;
		it = mapa.find(s);
		if(it == mapa.end()){
			mapa[s] = nxtIdx++;
		}
		valor[i] = mapa[s];
	}
	
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		u--; v--;
		g[u].pb(v);
		g[v].pb(u);
	}
	
	h[0] = 0;
	dfs(0, 0);
	int p;
	for (int i = 0; i < q; i++)
	{
		cin >> u >> v;
		u--; v--;
		if(ini[u] > ini[v]) swap(u, v);
		p = getLca(u, v);
		if(p==u){
			queries[i] = query(ini[u], ini[v], -1, i);
		}else{
			queries[i] = query(fim[u], ini[v], p, i);
		}
	}
	
	sort(queries, queries+q, compare);
	int L, R;
	int currL=0, currR=0;
	for (int i = 0; i < q; i++)
	{
		L = queries[i].l;
		R = queries[i].r;
		
		while (currR <= R)
		{
			add(currR);
			currR++;
		}
		while (currL > L)
		{
			add(currL-1);
			currL--;
		}
		while (currL < L)
		{
			del(currL);
			currL++;
		}
		while (currR > R+1)
		{
			del(currR-1);
			currR--;
		}
		
		if(queries[i].lca!=-1){
			add(ini[queries[i].lca]);
		}
		
		ans[queries[i].pos] = total;
		
		if(queries[i].lca!=-1){
			del(ini[queries[i].lca]);
		}
	}
	
	for (int i = 0; i < q; i++)
	{
		cout << ans[i] << "\n";
	}
	
	
	
	
	
	return 0;
}
