
Hash H;

bool ok(int tam){
	int l = 0;
	int r = tam-1;
	
	while (r < (int)H.s.size())
	{
		if(H.getRangeNormal(l, r) == H.getRangeInvertido(l, r)){
			return true;
		}
		
		l++; r++;
	}
	
	return false;
}

int longestPalindromicSubstring(string s, string &res){//retorna o tamanho da maior substring palindromo
	H = Hash(s);
	H.build();
	
	int lo = 1;
	int hi = (int)s.size();
	int mid;
	int ans = 0;
	
	while (lo <= hi)
	{
		mid = (lo+hi)/2;
		if(ok(mid) || ok(mid+1)){
			lo = mid+1;
			ans = max(ans, mid);
		}else{
			hi = mid-1;
		}
	}
	
	//recupera a primeira string palindromo de tamanho ans
	res.clear();
	int l = 0, r = ans-1;
	while (r < (int)H.s.size())
	{
		if(H.getRangeNormal(l, r) == H.getRangeInvertido(l, r)){
			res = H.s.substr(l, ans);
			break;
		}
	}
	
	return ans;
}

int main(){
	//le a string
	// chama a função
}
