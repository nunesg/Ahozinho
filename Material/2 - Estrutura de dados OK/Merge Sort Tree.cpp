int n, k, q;
int v[MAXN];

struct MERGESORT_TREE{
	vector<int> st[4*MAXN];
	
	MERGESORT_TREE(){}
	void reset(){
		for (int i = 0; i < 4*MAXN; i++)
		{
			st[i].clear();
		}
	}
	
	vector<int> merge(const vector<int> &a, const vector<int> &b){
		vector<int> ans;
		int i = 0, j = 0;
		while (ans.size() < k)
		{
			if(i==a.size() && j==b.size()) break;
			if(i==a.size()){
				ans.pb(b[j++]);
			}else if(j==b.size()){
				ans.pb(a[i++]);
			}else{
				if(a[i] > b[j]){
					ans.pb(a[i++]);
				}else{
					ans.pb(b[j++]);
				}
			}
		}
		return ans;
	}
	
	void build(int no, int l, int r){
		if(l==r){
			st[no].pb(v[l]);
			return;
		}
		int nxt = 2*no;
		int mid = (l+r)/2;
		build(nxt, l, mid);
		build(nxt+1, mid+1, r);
		st[no] = merge(st[nxt], st[nxt+1]);
	}
	
	vector<int> query(int no, int l, int r, int i, int j){
		vector<int> ans;
		if(r<i || l>j) return ans;
		if(i<=l && r<=j) return st[no];
		int nxt = 2*no;
		int mid = (l+r)/2;
		
		return merge(query(nxt, l, mid, i, j), query(nxt+1, mid+1, r, i, j));
	}

};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k >> q;
	MERGESORT_TREE tr;
	
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	tr.build(1, 0, n-1);
	
	vector<int> res;
	int l, r;
	ll ans;
	for (int i = 0; i < q; i++)
	{
		cin >> l >> r;
		l--; r--;
		res.clear();
		res = tr.query(1, 0, n-1, l, r);
		
		ans = res[0];
		for (int j = 1; j < res.size(); j++)
		{
			if(res[j]!=0){
				ans = (ans * 1LL * res[j])%MOD;
			}
		}
		
		cout << ans << "\n";
	}
	
	
	return 0;
}
