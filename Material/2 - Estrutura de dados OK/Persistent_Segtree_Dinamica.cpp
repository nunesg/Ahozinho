/*
 * 	SPOJ - MKTHNUM
 */

#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define inf 1000000100

struct no{
	
	no *left, *right;
	int val;
	
	no() : val(0), left(NULL), right(NULL) {}
	
	int join(no *a, no *b){
		int x = a ? a->val : 0;
		int y = b ? b->val : 0;
		return x+y;
	}
	
	no * update(int l, int r, int pos, int v){
		
		no *at = new no();
		*at = *this;
		
		if(l == r){
			at->val+=v;
			return at;
		}
		
		int mid = (l+r)>>1;
		
		if(pos<=mid){
			if(!left) left = new no();
			at->left = left->update(l, mid, pos, v);
		}else{
			if(!right) right = new no();
			at->right = right->update(mid+1, r, pos, v);
		}
		
		at->val = join(at->left, at->right);
		return at;
	}

};


no *root[N];
int vet[N], aux[N], inv[N];

int query_k(no *no1, no *no2, int l, int r, int k){
	
	if(l == r) return l;
	int a = (no1 && no1->left) ? no1->left->val : 0;
	int b = (no2 && no2->left) ? no2->left->val : 0;
	int x = b-a;
	
	int mid = (l+r)>>1;
	if(x>=k) return query_k( no1 ? no1->left : NULL,   no2 ? no2->left : NULL, l, mid, k );
	return query_k( no1 ? no1->right : NULL,   no2 ? no2->right : NULL, mid+1, r, k-x );
	
}


int main(){
	
	int n, q;
	scanf("%d %d", &n, &q);
	root[0] = new no();
	
	for(int i=1; i<=n; i++){
		scanf("%d", &vet[i]);
		aux[i] = vet[i];
	}
	int a, b, c;
	sort(aux+1, aux+n+1);
	for(int i=1; i<=n; i++){
		a = lower_bound(aux+1, aux+n+1, vet[i]) - aux;
		inv[a] = vet[i];
		vet[i] = a;
		root[i] = root[i-1]->update(1, n, vet[i], 1);
	}
	
	for(int i=0; i<q; i++){
		scanf("%d %d %d", &a, &b, &c);
		printf("%d\n", inv[query_k(root[a-1], root[b], 1, n, c)]);
	}
}
