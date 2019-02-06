/*
	SPOJ - Horrible Queries

*/


#include <bits/stdc++.h>

using namespace std;

#define N 101010

typedef long long int ll;

struct no{
	ll val, lazy;
	no *left, *right;
	no() : val(0), lazy(0), left(NULL), right(NULL) {}
	
	
	
	void do_lazy(int l, int r){
		if(lazy==0) return;
		val+= ((r-l)+1)*lazy;
		if(l<r){
			if(!left) left = new no();
			if(!right) right = new no();
			left->lazy+=lazy;
			right->lazy+=lazy;
		}
		lazy = 0;
	}

	void update(int l, int r, int a, int b, ll v){
		do_lazy(l, r);
		
		if(l>b || r<a) return;
		if(a<=l && b>=r) {
			lazy+=v;
			do_lazy(l, r);
			return;
		}
		
		int mid = (l+r)>>1;
		if(left == NULL) left = new no();
			left->update(l, mid, a, b, v);
		
		if(right == NULL) right = new no();
			right->update(mid+1, r, a, b, v);
			
		val = left->val + right->val;
	}
	
	ll query(int l, int r, int a, int b){
		do_lazy(l, r);

		if(l>b || r<a) return 0;
		if(a<=l && b>=r) return val;
		
		int mid = (l+r)>>1;
		ll x = (left) ? left->query(l, mid, a, b) : 0;
		ll y = (right) ? right->query(mid+1, r, a, b) : 0;
		return x+y;
	}
	
	void destroy(){//nem todo problema precisa, mas pode dar merda se nao destruir
		if(left) {
			left->destroy();
			free(left);
		}
		if(right) {
			right->destroy();
			free(right);
		}
		return;
	}
};

int n;

int main(){
	int t, q, op, a, b, c;
	scanf("%d", &t);
	no *st;
	while(t--){
		st = new no();
		scanf("%d %d", &n, &q);
		for(int i=0; i<q; i++){
			scanf("%d %d %d", &op, &a, &b);
			if(op){
				printf("%lld\n", st->query(1, n, a, b));
			}else{
				scanf("%d", &c);
				st->update(1, n, a, b, c);
			}
		}
		st->destroy();
		delete st;
	}
}
