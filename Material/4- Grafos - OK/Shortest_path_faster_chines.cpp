#include <bits/stdc++.h>

using namespace std;

#define N 502020
#define inf 2101010101
#define F first
#define S second

typedef pair<int, int> ii;

int n, m, dist[N], pai[N], in[N], s, t;
vector<ii> adj[N];

int SPF(){
	memset(pai, -1, sizeof pai);
	memset(in, 0, sizeof in);
	for(int i=0; i<n; i++) dist[i] = inf;
	dist[s] = 0;
	queue<int> q;
	q.push(s);
	
	while(q.size()){
		int u = q.front(); q.pop();
		
		in[u] = 0;
		for(ii f : adj[u]){
			int v = f.F, w = f.S;
			if(dist[v] > dist[u]+w){
				pai[v] = u;
				dist[v] = dist[u]+w;
				if(!in[v]){
					q.push(v);
					in[v] = 1;
				}
			}
		}
	}
	return (pai[t] == -1) ? -1 : dist[t];
}

int main(){
	int tc, a, b, c, x=1;
	scanf("%d", &tc);
	while(tc--){
		scanf("%d %d %d %d", &n, &m, &s, &t);
		for(int i=0; i<=n; i++) adj[i].clear();
		for(int i=0; i<m; i++){
			scanf("%d %d %d", &a, &b, &c);
			adj[a].push_back(ii(b, c));
			adj[b].push_back(ii(a, c));
		}
		a = SPF();
		
		if(a>=0) printf("Case #%d: %d\n", x++, a);
		else printf("Case #%d: unreachable\n", x++);
	}
}
