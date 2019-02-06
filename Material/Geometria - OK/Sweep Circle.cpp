//funcao que junta as partes de cima e baixo
void merge(vector<pv> &cima, vector<pv> &baixo, vector<pv> &v){
	v.clear();
	int i = 0, j = 0;
	
	while (i < (int)cima.size() && j < (int)baixo.size())
	{
		if(cross(cima[i], baixo[j]) <= 0) v.pb(cima[i++]);
		else v.pb(baixo[j++]);
	}
	while (i < (int)cima.size())
	{
		v.pb(cima[i++]);
	}
	while (j < (int)baixo.size())
	{
		v.pb(baixo[j++]);
	}
}

//ordena pelo angulo polar, separa em cima e baixo e depois junta.
void build(vector<pv> &v){
	sort(v.begin(), v.end(), comparePolarAngle);
	vector<pv> cima, baixo;
	for (int i = 0; i < (int)v.size(); i++)
	{
		if((v[i].x >= 0 && v[i].y >= 0) || (v[i].x < 0 && v[i].y > 0)){//esta na parte de cima
			cima.pb(v[i]);
		}else{//esta na parte de baixo
			baixo.pb(v[i]);
		}
	}
	
	merge(cima, baixo, v);
}

int main(){
	int x, y, n;
	vector<pv> v;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y;
		v.pb(pv(x, y));
	}
	build(v);
	return 0;
}

