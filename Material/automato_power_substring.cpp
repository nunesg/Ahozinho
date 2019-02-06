#include <bits/stdc++.h>

using namespace std;


#define N 202020
#define ALF 30

typedef long long int ll;

struct state{
	int nxt[ALF], link, cnt, len;
	state(){
		link = -1;
		cnt=0;
		len=0;
		memset(nxt, 0, sizeof nxt);
	}
	
}st[N<<1];


int n, sz, last, forbid[N], seen[N];
string s, aux;


void add(char letra, int i){
	
	int curr = sz++;
	int p, q, clone, c=letra-'a';
	
	for(p = last; p>=0 && !st[p].nxt[c]; p = st[p].link) st[p].nxt[c] = curr;
	
	if(p<0){
		st[curr].link = 0;
	}else{
		q = st[p].nxt[c];
		if(st[q].len == st[p].len+1){
			st[curr].link = q;
		}else{
			
			clone = sz++;
			
			st[clone] = st[q];
			
			st[clone].len = st[p].len+1;
			st[q].link = st[curr].link = clone;
			
			st[clone].cnt = 0;
			
			for(; p>=0; p = st[p].link){
				if(st[p].nxt[c]) st[p].nxt[c] = clone;
			}
			
		}
	}
	
	st[curr].cnt = !forbid[i];
	st[curr].len = st[last].len+1;
	last = curr;
}

ll build(){
	sz=1;
	last = 0;
	for(int i=0; i<s.size(); i++) add(s[i], i);
	
	int grau[N<<1]; memset(grau, 0, sizeof grau);
	queue<int> q;
	for(int i=1; i<sz; i++) grau[st[i].link]++;
	for(int i=1; i<sz; i++) if(!grau[i]) q.push(i);
	ll ans = 0;
	while(q.size()){
		int u = q.front(); q.pop();
		if(u<0) continue;
		
		ans = max(ans, (ll)st[u].len * (ll)st[u].cnt);
		
		st[ st[u].link ].cnt += st[u].cnt;
		if(!(--grau[st[u].link])) q.push(st[u].link);
	}
	return ans;
}


int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	cin >> s;
	cin >> aux;
	for(int i=0; i<n; i++) forbid[i] = aux[i]=='1';
	
	cout << build() << endl;
}
