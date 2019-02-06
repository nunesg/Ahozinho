#include <bits/stdc++.h>

using namespace std;
#define MAXN 100
#define INF 1000000000

int n;
int dist[MAXN][MAXN];
int pai[MAXN][MAXN];

void reset(){
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++) {
			dist[i][j] = INF;
			if(i==j) dist[i][j]=0;
			
			pai[i][j] = i;
		}
	}
}

void printPath(int i, int j) {
	if (i != j) printPath(i, pai[i][j]);
	printf(" %d", j+1);
}

int main(){
	int m;
	cin >> n >> m;
	reset();
	
	int u, v, w;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		u--; v--;
		dist[u][v] = w;
		dist[v][u] = w;
	}
	
	for(int k = 0; k < n; k++){
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					pai[i][j] = pai[k][j];
				}
			}
		}
	}
	
	while (cin >> u >> v)
	{
		u--; v--;
		cout << "dist = " << dist[u][v] << "\n";
		cout << "path = "; printPath(u, v); cout << "\n";
	}
	
	

	
	return 0;
}
