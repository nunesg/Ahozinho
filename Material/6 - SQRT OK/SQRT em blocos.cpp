int n, q;
vector<int> block[600];
int block_size = 600;
int v[100010];
 
int ini(int blocoAtual){ return blocoAtual*block_size; }
int fim(int blocoAtual){ return min(ini(blocoAtual+1) - 1, n-1); }
 
int func(int blocoAtual, int X){//calcula quantos elementos <= X tem no blocoAtual
	int ans = upper_bound(block[blocoAtual].begin(), block[blocoAtual].end(), X) - block[blocoAtual].begin();
	return ans;
}
 
void update(int pos, int val){//atualiza só o bloco afetado
	int valAntigo = v[pos];
	int blocoAtual = pos / block_size;
	v[pos] = val;
	
	for(int i = 0; i < block[blocoAtual].size(); i++){
		if(block[blocoAtual][i] == valAntigo){
			block[blocoAtual][i] = val;
			break;
		}
	}
	sort(block[blocoAtual].begin(), block[blocoAtual].end());//ordena o bloco de novo
}

/*
int query(int L, int R, int X){
	int blocoL, blocoR;
	blocoL = L / block_size;
	blocoR = R / block_size;
	int pos;
	int ans = 0LL;
	
	for(pos = L; pos <= min(R, fim(blocoL)); pos++)
		if(v[pos] <= X) ans++;
	
	for (int i = blocoL+1; i <= blocoR-1; i++)
		ans += func(i, X);
	
	for(pos = max(pos, ini(blocoR)); pos <= R; pos++)
		if(v[pos] <= X) ans++;
	
	return ans;
}
*/

int query(int L, int R, int X){//retorna quantos elementos <= X tem em [L, R]
	int blocoL, blocoR;
	blocoL = L / block_size;
	blocoR = R / block_size;
	int pos;
	int ans = 0LL;
	//para blocos que não estão inteiros dentro do intervalo: percorre em O(n)
	//para blocos que estão inteiros dentr do intervalo: faz uma busca binária pra saber quantos elementos <= X existe
	for (int i = 0; i < block_size; i++)
	{
		if(ini(i) > R) break;
		if(ini(i) >= L && fim(i) <= R) ans += func(i, X);
		else{
			for(int j=max(ini(i), L); j<=min(fim(i), R); j++) ans += (v[j] <= X);
		}
	}
	return ans;
}
 
int main(){
	cin >> n >> q;
	
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
		block[i/block_size].pb(v[i]);//adiciona no bloco correspondente
	}
	for (int i = 0; i < block_size; i++)
	{
		if(block[i].size()==0) break;
		sort(block[i].begin(), block[i].end());//ordena cada bloco
	}
	
	char op;
	int L, R, X, pos, val;
	for (int i = 0; i < q; i++)
	{
		cin >> op;
		if(op=='C'){
			cin >> L >> R >> X;
			cout << query(L-1, R-1, X) << "\n";
		}else{
			cin >> pos >> val;
			update(pos-1, val);
		}
	}
	return 0;
}
 
