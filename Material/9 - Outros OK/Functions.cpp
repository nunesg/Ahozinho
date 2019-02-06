bool a(int x){
	if(x>10) {
		return true;
	}
	return false;
}
bool b(int x){
	if(x>100) {
		return true;
	}
	return false;
}
bool c(int x){
	if(x>1000) {
		return true;
	}
	return false;
}

void printa(int x){
	if(x==1) printf("<100\n");
	else if(x==2) printf("<1000\n");
	else if(x == 3) printf(">1000\n");
	else printf("<10\n");
}

int main(){
	vector<  function<bool(int)>  > vet;
	vet.push_back(a);
	vet.push_back(b);
	vet.push_back(c);
	int x;
	function<int(int)> f = [x](int i){
			return i<=x;
	};
	
	auto f_ = [x](int i){
			return i<=x;
	};
	
	scanf("%d", &x);
	for(int i=0; i<vet.size(); i++){
		if( !vet[i](x) ){
			printa(i);
			return 0;
		}
	}
	printa(vet.size());
	
}
