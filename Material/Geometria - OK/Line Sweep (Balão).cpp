struct pv{
	ll x, y;
	pv(){}
	pv(ll _x, ll _y){
		x = _x;
		y = _y;
	}
	pv operator - (pv other){
		return pv(x-other.x, y-other.y);
	}
};

struct event{
	pv p;
	int tipo, id;
	event(){}
	event(pv _p, int _tipo, int _id){
		p = _p;
		tipo = _tipo;
		id = _id;
	}
	bool operator < (event other) const{
		if(p.x == other.p.x) return tipo < other.tipo;
		return p.x < other.p.x;
	}
};

struct seg{
	pv a, b;
	seg(){}
	seg(pv _a, pv _b){
		a = _a;
		b = _b;
	}
};


int dp[MAXN][LOG];
int qtdSeg, qtdBalao;
vector<seg> segmento;
vector<event> evento;
vector<pv> vertice;
vector<int> g[MAXN];

ll cross(pv a, pv b){
	return a.x*b.y - a.y*b.x;
}

ll func(pv a, pv b, pv c){
	return cross(b-a, c-b);
}

bool compare(int _1, int _2){
	pv a = segmento[_1].a;
	pv b = segmento[_1].b;
	pv c = segmento[_2].a;
	pv d = segmento[_2].b;
	
	if(a.x < c.x){
		if(func(a, c, b) > 0)
			return false;
		return true;
	}else{
		if(func(c, a, d) > 0)
			return true;
		return false;
	}
}
set<int, bool(*)(int, int)> s(compare);

void adicionar(int id){
	s.insert(id);
	set<int, bool(*)(int, int)>::iterator it;
	if(segmento[id].a.y > segmento[id].b.y){
		it = s.find(id);
		it++;
		if(it == s.end()){
			vertice[id] = pv(segmento[id].a.x, INF);
		}else{
			if(segmento[*it].a.y == segmento[*it].b.y){
				vertice[id] = pv(segmento[id].a.x, segmento[*it].a.y);
			}else{
				g[id].pb(*it);
			}
		}
	}
}

void remover(int id){
	set<int, bool(*)(int, int)>::iterator it;
	if(segmento[id].a.y < segmento[id].b.y){
		it = s.find(id);
		it++;
		if(it==s.end()){
			vertice[id] = pv(segmento[id].b.x, INF);
		}else{
			if(segmento[*it].a.y == segmento[*it].b.y){
				vertice[id] = pv(segmento[id].b.x, segmento[*it].a.y);
			}else{
				g[id].pb(*it);
			}
		}
	}
	s.erase(id);
}

void consultar(int id, int x){
	set<int, bool(*)(int, int)>::iterator it;
	if(s.size()==0){
		vertice[id] = pv(x, INF);
	}else{
		it = s.begin();
		if(segmento[*it].a.y == segmento[*it].b.y){
			vertice[id] = pv(x, segmento[*it].a.y);
		}else{
			g[id].pb(*it);
		}
	}
}

void sweep(){
	sort(evento.begin(), evento.end());
	for (int i = 0; i < evento.size(); i++)
	{
		if(evento[i].tipo == ABRE)
			adicionar(evento[i].id);
		else if(evento[i].tipo == FECHA)
			remover(evento[i].id);
		else
			consultar(evento[i].id, evento[i].p.x);
	}
}

void build(){
	for (int i = 0; i < qtdSeg + qtdBalao; i++)
	{
		if(g[i].size() == 0){
			dp[i][0] = i;
		}else{
			dp[i][0] = g[i][0];
		}
	}
	for (int j = 1; j < LOG; j++)
	{
		for (int i = 0; i < qtdSeg + qtdBalao; i++)
		{
			dp[i][j] = dp[dp[i][j-1]][j-1];
		}
	}
}

int pula(int u){
	int d = MAXN;
	for (int i = 0; i < LOG; i++)
	{
		if(d & (1<<i)){
			u = dp[u][i];
		}
	}
	return u;
}

void reset(){
	segmento.clear();
	evento.clear();
	vertice.clear();
	for (int i = 0; i < qtdSeg+qtdBalao; i++)
	{
		g[i].clear();
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	while(cin >> qtdSeg >> qtdBalao){
		reset();
		ll x, y, X2, Y2;
		for (int i = 0; i < qtdSeg; i++)
		{
			cin >> x >> y >> X2 >> Y2;
			if(x < X2){
				segmento.pb(seg(pv(x, y), pv(X2, Y2)));
			}else{
				segmento.pb(seg(pv(X2, Y2), pv(x, y)));
			}
			evento.pb(event(segmento[i].a, ABRE, i));
			evento.pb(event(segmento[i].b, FECHA, i));
			vertice.pb(pv(-1, -1));
		}
		
		for (int i = 0 + qtdSeg; i < qtdBalao + qtdSeg; i++)
		{
			cin >> x;
			evento.pb(event(pv(x, 0), CONSULTA, i));
			vertice.pb(pv(-1, -1));
		}
		
		sweep();
		build();
		int ult;
		for (int i = 0 + qtdSeg; i < qtdBalao+qtdSeg; i++)
		{
			ult = pula(i);
			if(vertice[ult].y == INF) cout << vertice[ult].x << "\n";
			else cout << vertice[ult].x << " " << vertice[ult].y << "\n";
		}
	}
	return 0;
}
