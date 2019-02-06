int rabin_karp(string &text, string &pattern){//retorna a posição da primeira ocorrência do padrão no texto, ou -1, se não existir
	Hash T = Hash(text);
	Hash P = Hash(pattern);
	T.build();
	P.build();
	
	int l = 0, r = pattern.size()-1;
	while (r < (int)text.size())
	{
		if(T.getRangeNormal(l, r) == P.hashNormal){
			return l;
		}
		l++; r++;
	}
	
	return -1;
}
