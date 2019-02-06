int v[MAXN];

struct SEGTREE{
	int st[MAXN * 4];
	
	SEGTREE(){}
	
	void reset(){
		memset(st, 0, sizeof st);
	}
	
	int merge(int a, int b){
		return a+b;
	}
	
	void build(int no, int l, int r){
		if(l==r){
			st[no] = v[l];
			return;
		}
		int mid = (l+r)>>1;
		int nxt = no<<1;
		build(nxt, l, mid);
		build(nxt+1, mid+1, r);
		st[no] = merge(st[nxt], st[nxt+1]);
	}
		
	int query(int no, int l, int r, int i, int j){
		if(i<=l && r<=j) return st[no];
		if(i>r || j<l) return 0;
		
		int mid = (l+r)>>1;
		int nxt = no<<1;
		return merge(query(nxt, l, mid, i, j), query(nxt+1, mid+1, r, i, j));
	}

	void update(int no, int l, int r, int pos, int val){
		if(pos<l || pos>r) return;
		if(l==r){
			st[no] = val;
			return;
		}
		
		int mid=(l+r)>>1;
		int nxt = no<<1;
		update(nxt, l, mid, pos, val);
		update(nxt+1, mid+1, r, pos, val);
		st[no] = merge(st[nxt], st[nxt+1]);
	}
};

int main(){
	SEGTREE root;
	root.reset();
	//le o vetor v
	root.build(1, 0, n-1);
	
	return 0;
}
