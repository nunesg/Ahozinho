//OBS: usa a struct Hash

int sa[MAXN], lcp[MAXN];

string s;
Hash H;

int getLCP(int a, int b){//pega o LCP entre o sufixo começando em a e o sufix começando em b
	
	int lo = 0;
	int hi = min((int)s.size() - a, (int)s.size() - b);
	int mid;
	int ans = 0;
	
	while(lo <= hi){
		mid = (lo+hi)/2;
		if(H.getRangeNormal(a, a+mid-1) == H.getRangeNormal(b, b+mid-1)){
			lo = mid+1;
			ans = max(ans, mid);
		}else{
			hi = mid-1;
		}
	}
	
	return ans;
}

bool compareSA(int a, int b){//pega o LCP e compara o próximo caractere
	int len = getLCP(a, b);
	if(a+len == (int)s.size()) return true;
	if(b+len == (int)s.size()) return false;
	
	return s[a+len] < s[b+len];
}

void build_SA(){
	int tam = (int)s.size();
	for (int i = 0; i < tam; i++)
	{
		sa[i] = i;
	}
	sort(sa, sa + tam, compareSA);
}

void build_lcp(){
	lcp[0] = 0;
	for (int i = 1; i < (int)s.size(); i++)
	{
		lcp[i] = getLCP(sa[i], sa[i-1]);
	}
}

int main () {
	buildPot();//cuidado com o limite do MAXN
	cin >> s;
	H = Hash(s);
	H.build();
	
	build_SA();
	build_lcp();
	
	return 0;
}
