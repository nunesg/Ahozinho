#include <bits/stdc++.h>

using namespace std;

#define N 505
#define M 10101
#define inf 10101010

struct ed{
	int to, c, f;
}edge[M];


int n, m, seen[N], tempo, curr, p[N], nxt[N], dist[N], s, t;
vector<int> adj[N];


void add_edge(int a, int b, int c, int rev){
	
	edge[curr].to = b;
	edge[curr].c = c;
	edge[curr].f = 0;
	adj[a].push_back(curr++);
	
	edge[curr].to = a;
	edge[curr].c = rev;
	edge[curr].f = 0;
	adj[b].push_back(curr++);
}

int augment(){
	int ans = inf;
	for(int u=t, e = p[u];      u!=s;        u = edge[e^1].to, e = p[u]){
		int w = edge[e].c - edge[e].f;
		ans = min(ans, w);
	}

	for(int u=t, e = p[u];      u!=s;        u = edge[e^1].to, e = p[u]){
		edge[e].f+=ans;
		edge[e^1].f-=ans;
	}
	return ans;
}

int bfs(){
	
	p[t] = -1;
	queue<int> q;
	q.push(s);
	
	while(q.size()){
		int u = q.front(); q.pop();
		if(u == t) break;
		for(int i=0; i<adj[u].size(); i++){
			int e = adj[u][i];
			int v = edge[e].to;
			if(seen[v] < tempo && edge[e].c - edge[e].f > 0){
				q.push(v);
				seen[v] = tempo;
				p[v] = e;
			}
		}
	}
	if(p[t] == -1) return 0;
	return augment();
}


int edmonds_karp(){
	int flow=0;
	memset(seen, 0, sizeof seen);
	tempo = 1;
	
	while(int a = bfs()){
		flow+=a;
		tempo++;
	}
	return flow;
}


int main(){
	
	cin >> n >> m;
	int a, b, c;
	curr=0;
	for(int i=0; i<m; i++){
		cin >> a >> b >> c;
		add_edge(a, b, c, 0);
		add_edge(b, a, c, 0);
	}
	s = 1; t = 2;
	cout << "Max flow = " << edmonds_karp() << endl;
}
