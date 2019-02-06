struct seg{
	ll y, tipo;
	seg(){}
	seg(ll a, ll b){
		y = a;
		tipo = b;
	}
	bool operator < (seg other) const{
		return y > other.tipo;
	}
};

struct event{
	ll x, y, y0, tipo;
	event(){}
	event(ll a, ll b, ll c, ll d){
		x = a;
		y = b;
		y0 = c;
		tipo = d;
	}
	bool operator < (event other) const{
		return x < other.x;
	}
};

ll ABRE = 0;
ll FECHA = 1;

multiset<pair<ll, ll>, greater<pair<ll, ll> > > ativo;
vector<event> evento;

ll sweep(){
	ll area=0;
	ll x=0, x1=0;
	event eve;
	ll cnt = 0;
	ll U=0;
	ll D=0;
	//~ ll ans = 0;
	
	for (ll i = 0; i < evento.size(); i++)
	{
		eve = evento[i];
		cnt = 0;
		x1 = eve.x;
		//~ prllf("%s em x=%d\n", eve.tipo==ABRE ? "abre" : "fecha", eve.x);
		for(auto it : ativo){
			//~ oioi;
			if(it.S == ABRE){
				if(cnt==0) U = it.F;
				cnt++;
			}else if(it.S==FECHA){
				if(cnt==1){
					D = it.F;
					//~ prllf("x = %d  x1 = %d  U = %d  D = %d\n", x, x1, U, D);
					area += (x1-x)*(U-D);
				}
				cnt--;
			}
		}
		
		if(eve.tipo == ABRE){
			ativo.insert(mp(eve.y0, ABRE));
			ativo.insert(mp(eve.y, FECHA));
		}else{
			//~ for(auto i : ativo){
				//~ if(i.F==eve.y && i.S==ABRE) ativo.erase(i);
				//~ if(i.F==eve.y0 && i.S==FECHA) ativo.erase(i);
			//~ }
			ativo.erase(ativo.find(mp(eve.y0, ABRE)));
			ativo.erase(ativo.find(mp(eve.y, FECHA)));
		}
		x = x1;
		//~ x1 = eve.x;
	}
	
	return area;
}

int main () {
	ll n, x, y, larg, alt, x0, y0;
	cin >> n;
	for (ll i = 0; i < n; i++)
	{
		cin >> x >> y >> x0 >> y0;
		evento.pb(event(x, y, y0, ABRE));
		evento.pb(event(x0, y, y0, FECHA));
	}
	sort(evento.begin(), evento.end());
	
	ll area = sweep();
	//~ cout << "Area total = " << area << endl;
	cout << area << endl;
	
	return 0;
}
