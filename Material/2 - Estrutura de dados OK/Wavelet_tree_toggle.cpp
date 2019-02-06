/*
 * 	ILKQUERY 2 - toggle
 */

#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define inf 1000000001

int vet[N], n, q, state[N];

typedef long long int ll;

struct BIT{
	vector<int> bit;
	int sz;
	
	BIT(){ bit.clear(); sz=0;}
	
	BIT(int n){
		sz=n;
		bit.assign(n+1, 0);
	}
	
	void update(int pos, int v){
		for(; pos<=sz; pos+= (pos&(-pos))) bit[pos]+=v;
	}
	
	int sum(int pos){
		int ans=0;
		for(; pos; pos-=(pos&(-pos))) ans+=bit[pos];
		return ans;
	}
};


struct wavelet{
	int low, high;
	vector<int> b;
	BIT bit;//a bit guarda a quantidade de elementos inativos no intervalo
	wavelet *left, *right;
	
	
	wavelet(int *from, int *to, int l, int h){
		low = l, high = h;
		left = right = NULL;
		
		bit = BIT(to-from+1);
		if(from == to || l==h) return;
		
		
		int mid = int( (ll(l) + ll(h) )>>1LL);
		
		auto f = [mid](int i){ return i<=mid; };
		
		b.push_back(0);
		for(int *it = from;  it!=to;  it++){
			b.push_back(b.back()+f(*it));
		}
		
		int *pivo = stable_partition(from, to, f);
		left = new wavelet(from, pivo, l, mid);
		right = new wavelet(pivo, to, mid+1, h);
	}
	
	int count_active(int l, int r){
		int x= (r-l+1) - bit.sum(r) + bit.sum(l-1);//qtd de elementos ativos: |range| - qtd inativos no range
		return x;
	}
	
	void toggle(int pos, int v){
		bit.update(pos, v);
		if(low == high) return;
		
		int rb = b[pos];
		int lb = b[pos-1];
		int c = rb-lb;
		
		if(c) left->toggle(lb+1, v);
		else right->toggle(pos-rb, v);
	}
	
	int query(int l, int r, int k){//quantos elementos igual a k ativos existem no intervalo
		if(l>r) return 0;
		if(low == high) return (low == k) ? count_active(l, r) : 0;
		
		int mid = int( (ll(low)+ ll(high))>>1LL );
		int rb = b[r];
		int lb = b[l-1];
		if(k<=mid) return (left) ? left->query(lb+1, rb, k) : 0;
		else return (right) ? right->query(l-lb, r-rb, k) : 0;
	}
};

wavelet *WT;

int main(){
	
	scanf("%d %d", &n, &q);
	int menor=inf, maior=-inf;
	for(int i=1; i<=n; i++){
		scanf("%d", &vet[i]);
		maior = max(maior, vet[i]);
		menor = min(menor, vet[i]);
		state[i] = 1;
	}
	
	WT = new wavelet(vet+1, vet+n+1, menor, maior);
	
	int op, a, b, k;
	while(q--){
		scanf("%d", &op);
		if(op){
			scanf("%d", &a); a++;
			if(state[a]) WT->toggle(a, 1);
			else WT->toggle(a, -1);
			
			state[a]^=1;
		}else{
			scanf("%d %d %d", &a, &b, &k); a++; b++;
			printf("%d\n", WT->query(a, b, k));
		}
	}
}
