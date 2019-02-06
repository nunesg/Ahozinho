struct query{
	int l, r, pos;
	query(){}
	query(int a, int b, int d){
		l = a;
		r = b;
		pos = d;
	}
};

//~ int block_size = sqrt(MAXN);

void add(int pos){
	//~ Faz alguma coisa: conta frequência, por exemplo
	//~ Adiciona o elemento v[pos] no intervalo
}

void del(int pos){
	//~ Faz alguma coisa: conta frequência, por exemplo
	//~ Remove o elemento v[pos] no intervalo
}

bool compare(query &a, query &b){
	if(a.l / block_size == b.l / block_size) return a.r < b.r;
	return a.l < b.l;
	//se o bloco do left for o mesmo, ordena pelo r, senão ordena por l
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)	//leitura do vetor de entrada
		cin >> v[i];
		
	int L, R;
	cin >> q;
	for (int i = 0; i < q; i++)	//leitura de query
	{
		cin >> L >> R;
		L--; R--;
		queries[i] = query(L, R, i);
	}
	sort(queries, queries+q, compare);//ordena as queries
	int currL = 0, currR = 0;
	
	for (int i = 0; i < q; i++)
	{
		L = queries[i].l;
		R = queries[i].r;
		while (currL < L) 
			del(currL++);	//remove elemento da posição currL
		while (currR <= R) 
			add(currR++);	//adiciona elemento da posição currR
		while (currL > L)
			add(--currL);	//adiciona elemento da posição currL-1
		while (currR > R+1)
			del(--currR);	//remove elemento da posição currR-1
		
		saida[queries[i].pos] = resposta;	//reordena a saída		
	}
	for (int i = 0; i < q; i++)
		cout << saida[i] << "\n";
	return 0;
}
