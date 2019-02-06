int v[MAXN];

struct SEGTREE_LAZY{
	int st[MAXN * 4];
	int lazy[MAXN * 4];
	
	SEGTREE_LAZY(){}
	
	void reset(){
		memset(st, 0, sizeof st);
		memset(lazy, 0, sizeof lazy);
	}
	
	int merge(int a, int b){
		return a+b;
	}
	
	void build(int no, int l, int r){
		if(l==r){
			st[no] = v[l];
			lazy[no] = 0;
			return;
		}
		int mid = (l+r)>>1;
		int nxt = no<<1;
		
		build(nxt, l, mid);
		build(nxt+1, mid+1, r);
		
		st[no] = merge(st[nxt], st[nxt+1]);
		lazy[no] = 0;
	}
		
	void propagate(int no, int l, int r){
		if(!lazy[no]) return;
		
		int mid = (l+r)>>1;
		int nxt = no<<1;
		
		st[no] += (r-l+1)*lazy[no];
		
		if(l!=r){
			lazy[nxt] += lazy[no];
			lazy[nxt+1] += lazy[no];
		}
		lazy[no] = 0;
	}	
	
	int query(int no, int l, int r, int i, int j){
		propagate(no, l, r);
		
		if(i<=l && r<=j) return st[no];
		if(i>r || j<l) return 0;
		
		int mid = (l+r)>>1;
		int nxt = no<<1;
		return merge(query(nxt, l, mid, i, j), query(nxt+1, mid+1, r, i, j));
	}

	void update(int no, int l, int r, int i, int j, int val){
		propagate(no, l, r);
		
		if(i>r || j<l) return;
		if(i<=l && r<=j){
			lazy[no] += val;
			propagate(no, l, r);
			return;
		}
		
		int mid = (l+r)>>1;
		int nxt = no<<1;
		
		update(nxt, l, mid, i, j, val);
		update(nxt+1, mid+1, r, i, j, val);
		
		st[no] = merge(st[nxt], st[nxt+1]);
	}
};

int main(){
	SEGTREE_LAZY root;
	root.reset();
	//le o vetor v
	root.build(1, 0, n-1);
	
	
	return 0;
}
