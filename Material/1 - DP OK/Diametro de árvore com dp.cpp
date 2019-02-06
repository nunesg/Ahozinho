#include <bits/stdc++.h>

using namespace std;
#define inf 1e9
#define pb push_back
#define mp make_pair
#define MAXN 100010

vector<int> g[MAXN];
int diameter;
int dp1[MAXN];//acha a altura da subárvore
int dp2[MAXN];//soma dos dois maiores filhos + 1

void dfs(int u, int pai){
	int mx1 = 0;
	int mx2 = 0;
	int v;
	
	dp1[u] = 1;
	dp2[u] = 1;
	
	for (int i = 0; i < (int)g[u].size(); i++) {
		v = g[u][i];
		if(v == pai) continue;
		dfs(v, u);
		dp1[u] = max(dp1[u], 1 + dp1[v]);
		
		if(dp1[v] > mx1){
			mx2 = mx1;
			mx1 = dp1[v];
		} else if(dp1[v] > mx2){
			mx2 = dp1[v];
		}
	}
		
	dp2[u] = max(dp2[u], 1 + mx1 + mx2);
	diameter = max(diameter, max(dp1[u], dp2[u]));
}

int main(){
	int n, u, v;
	cin >> n;
	for (int i = 0; i < n-1; i++) {
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	
	diameter = 0;
	dfs(1, 1);
	diameter--;
	cout << diameter << "\n";
	
	return 0;
}
