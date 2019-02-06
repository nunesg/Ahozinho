/*
 * 	E da final brasileira de 2016
 */

#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define inf 1e9

int n, vet[N], q;

struct wavelet{
	int low, high;
	vector<int> b;
	wavelet *left, *right;
	
	wavelet(int *from, int *to, int l, int h){//l e h sao o menor e o maior elemento do alfabeto
		low = l, high = h;
		if(from == to || l == h) return;
		
		int mid = (l+h)>>1;
		
		auto f = [mid](int i){ return i<=mid; };
		
		b.push_back(0);
		for(int *it = from; it!=to; it++){
			b.push_back( b.back() + f(*it) );
		}
		
		int *pivo = stable_partition(from, to, f);
		left = new wavelet(from, pivo, l, mid);
		right = new wavelet(pivo, to, mid+1, h);
	}
	
	int kth(int l, int r, int k){
		if(low == high) return low;
		int lb = b[l-1];
		int rb = b[r];
		int c = rb-lb;
		if(c>=k) return left->kth(lb+1, rb, k);
		else return right->kth(l-lb, r-rb, k-c);
	}
	
	bool esq(int p){
		return b[p] == b[p-1]+1;
	}
	
	void update(int p){//swap p e p+1
		if(low == high) return;
		
		if(esq(p) && !esq(p+1)){
			swap(b[p], b[p+1]);
			b[p]--;
			return;
		}
		
		if(!esq(p) && esq(p+1)){
			b[p]++;
			return;
		}
		if(esq(p)) left->update(b[p]);
		else right->update(p-b[p]);
	}
	
};

int main(){
	
	scanf("%d %d", &n, &q);
	for(int i=1; i<=n; i++) scanf("%d", &vet[i]);
	wavelet *root = new wavelet(vet+1, vet+n+1, 0, inf);
	int a, b, c;
	char op;
	while(q--){
		scanf(" %c", &op);
		if(op == 'Q'){
			scanf("%d %d %d", &a, &b, &c);
			printf("%d\n", root->kth(a, b, c));
		}else{
			scanf("%d", &a);
			root->update(a);
		}
	}
}
