/*
 * 	SPOJ - MKTHNUM
 */

#include <bits/stdc++.h>

using namespace std;

#define N 101010

struct no{
	int l, r, val;
	no() : l(0), r(0), val(0) {}
}st[10101010];


int n, q, root[N], vet[N], inv[N], aux[N], nxt;

int update(int no1, int l, int r, int pos, int v){
	
	int no2 = nxt++;
	st[no2] = st[no1];
	if(l == r){
		st[no2].val+=v;
		return no2;
	}
	
	int mid = (l+r)>>1;
	if(pos<=mid) st[no2].l = update(st[no1].l, l, mid, pos, v);
	if(pos>mid) st[no2].r = update(st[no1].r, mid+1, r, pos, v);
	
	st[no2].val = st[st[no2].l].val + st[st[no2].r].val;
	return no2;
}

int query_k(int no1, int no2, int l, int r, int k){
	if(l == r) return l;
	int x = st[st[no2].l].val - st[st[no1].l].val;
	int mid = (l+r)>>1;
	
	
	if(x >= k) return query_k(st[no1].l, st[no2].l, l, mid, k);
	return query_k(st[no1].r, st[no2].r, mid+1, r, k-x);
}


int main(){
	
	scanf("%d %d", &n, &q);
	for(int i=1; i<=n; i++){
		scanf("%d", &vet[i]);
		aux[i] = vet[i];
	}
	
	sort(aux+1, aux+n+1);
	root[0] = 0;
	nxt = 1;
	for(int i=1; i<=n; i++){
		int a = lower_bound(aux+1, aux+n+1, vet[i]) - aux;
		inv[a] = vet[i];
		vet[i] = a;
		root[i] = update(root[i-1], 1, n, a, 1);
	}
	
	int a, b, c;
	for(int i=0; i<q; i++){
		scanf("%d %d %d", &a, &b, &c);
		printf("%d\n", inv[query_k(root[a-1], root[b], 1, n, c)]);
	}
	
}
