#define ABRE 0 
#define QUERY 1 
#define FECHA 2 

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


//OKKKKKK
ll cross(pv a, pv b){
	return a.x * b.y - a.y * b.x;
}

struct event{
	pv pt;
	int tipo, quadrante, id;
	event(){}
	event(pv _pt, int _tipo, int _quadrante, int _id){
		pt = _pt;
		tipo = _tipo;
		quadrante = _quadrante;
		id = _id;
	}
	bool operator < (event other) const{
		ll c;
		if(quadrante == other.quadrante){
			c = cross(pt, other.pt);
			if(c == 0){
				return tipo < other.tipo;
			}
			return c > 0;
		}
		return quadrante < other.quadrante;
	}
};

struct seg{
	pv a, b;
	int id;
	seg(){}
	seg(pv _a, pv _b){
		a = _a;
		b = _b;
		id = -1;
	}
	seg(pv _a, pv _b, int _id){
		a = _a;
		b = _b;
		id = _id;
	}
};


//OKKKKKKK
ld distPt(pv a, pv b){
	return hypot(a.x-b.x, a.y-b.y);
}


//OKKKKKK
ll dot(pv a, pv b){
	return a.x * b.x + a.y * b.y;
}

//retorna o sinal de um número OKKK
int sinal(ll res){
	if(res > 0) return 1;
	if(res < 0) return -1;
	return 0;
}

//checa se 2 segmentos se cruzam (pode ser na borda)   OKKKK
bool temInterSegmento(seg r, seg s){
	pv a = r.a;
	pv b = r.b;
	pv c = s.a;
	pv d = s.b;
	
	return sinal(cross(b-a, d-a)) != sinal(cross(b-a, c-a)) && sinal(cross(d-c, a-c)) != sinal(cross(d-c, b-c));
}

void printaPonto(pv a){
	printf("(%lld, %lld)  ", a.x, a.y);
	
}

vector<pv> crianca;
vector<seg> parede, tmpParede;
vector<event> eve;
int qtdParede, qtdCrianca, qtdProcura;
pv origin;

bool compareSet(int id1, int id2){
	pv a = tmpParede[id1].a;
	pv b = tmpParede[id1].b;
	pv c = tmpParede[id2].a;
	pv d = tmpParede[id2].b;
	
	return cross(d-a, b-a) > 0;
}

//~ set<int, bool(*)(int, int)> active(compareSet);
set<int> active;

int getQuadrante(pv pt){
	ll x = pt.x;
	ll y = pt.y;
	if(x >= 0 && y >= 0) return 1;
	if(x < 0 && y >= 0) return 2;
	if(x <= 0 && y < 0) return 3;
	if(x > 0 && y < 0) return 4;
}

bool needCut(seg r){
	return r.a.y < 0 && r.b.y > 0;
}

int visivel(pv pt){
	//inicio bruta
	for (auto i : active)
	{
		seg r = tmpParede[i];
		if(temInterSegmento(seg(pv(0, 0), pt), r)) return 0;
	}
	return 1;
	
	//fim bruta
	if((int)active.size() == 0) return 1;
	seg r = tmpParede[*active.begin()];
	if(temInterSegmento(seg(pv(0, 0), pt), r)) return 0;
	return 1;
}

int sweep(){
	sort(eve.begin(), eve.end());
	
	int ans = 0;
	
	for (int i = 0; i < (int)eve.size(); i++)
	{
		if(eve[i].tipo == ABRE){
			active.insert(eve[i].id);
		}
		else if(eve[i].tipo == FECHA){
			active.erase(eve[i].id);
		}else ans += visivel(eve[i].pt);
	}
	return ans;
}

int solve(int idx){
	origin = crianca[idx];
	eve.clear();
	tmpParede.clear();
	pv pt;
	for (int i = 0; i < qtdCrianca; i++)
	{
		if(i==idx) continue;
		pt = crianca[i] - origin;
		eve.pb(event(pt, QUERY, getQuadrante(pt), -1));
	}
	
	int cnt = 0;
	seg nw;
	for (int i = 0; i < qtdParede; i++)
	{
		nw = seg(parede[i].a - origin, parede[i].b - origin, cnt);
		if(!needCut(nw)){
			if(cross(nw.a, nw.b) > 0){
				eve.pb(event(nw.a, ABRE, getQuadrante(nw.a), cnt));
				eve.pb(event(nw.b, FECHA, getQuadrante(nw.b), cnt));
			}else{
				eve.pb(event(nw.b, ABRE, getQuadrante(nw.b), cnt));
				eve.pb(event(nw.a, FECHA, getQuadrante(nw.a), cnt));
			}
			tmpParede.pb(nw);
			cnt++;
		}else{
			if(cross(nw.b - nw.a, pv(0, 0) - nw.a) > 0){
				eve.pb(event(pv(1,0), ABRE, 1, cnt));
				eve.pb(event(nw.b, FECHA, getQuadrante(nw.b), cnt));
				eve.pb(event(nw.a, ABRE, getQuadrante(nw.a), cnt));
				eve.pb(event(pv(1, 0), FECHA, 4, cnt));
			}else{
				eve.pb(event(nw.b, ABRE, getQuadrante(nw.b), cnt));
				eve.pb(event(pv(-1, 0), FECHA, 2, cnt));
				eve.pb(event(pv(-1, 0), ABRE, 3, cnt));
				eve.pb(event(nw.a, FECHA, getQuadrante(nw.a), cnt));
			}
			tmpParede.pb(nw);
			cnt++;
		}
	}
	return sweep();
}

void reset(){
	eve.clear();
	tmpParede.clear();
	parede.clear();
	crianca.clear();
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	ll x, y, x0, y0;
	while (cin >> qtdProcura >> qtdCrianca >> qtdParede)
	{
		reset();
		for (int i = 0; i < qtdCrianca; i++)
		{
			cin >> x >> y;
			crianca.pb(pv(x, y));
		}
		for (int i = 0; i < qtdParede; i++)
		{
			cin >> x >> y >> x0 >> y0;
			if(y < y0) parede.pb(seg(pv(x, y), pv(x0, y0), -1));
			else parede.pb(seg(pv(x0, y0), pv(x, y), -1));
		}
		for (int i = 0; i < qtdProcura; i++)
		{
			cout << solve(i) << "\n";
		}
	}
	
	
	return 0;
}
