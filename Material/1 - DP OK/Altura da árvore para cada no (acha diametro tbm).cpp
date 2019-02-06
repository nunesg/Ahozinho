#include <bits/stdc++.h>

using namespace std;
#define inf 1e9
#define pb push_back
#define mp make_pair
#define MAXN 100010

vector<int> g[MAXN];
int in[MAXN];
int out[MAXN];
int diameter;

// in[u]: altura da subárvore do u com a raiz prefixada (raiz é sempre o 1)
// out[u]: altura fora da subárvore do u, pode ir pra algum dos irmãos do u ou para fora da subárvore do pai do u

void dfs(int u, int pai){
	int v;
	in[u] = 0;
	
	for (int i = 0; i < (int)g[u].size(); i++) {
		v = g[u][i];
		if(v == pai) continue;
		dfs(v, u);
		in[u] = max(in[u], 1 + in[v]);//calcula a altura caso a raiz fosse sempre o 1
	}
}

void dfs2(int u, int pai){
	int mx1 = -1;
	int mx2 = -1;
	int v;
	
	diameter = max(diameter, max(in[u], out[u]));
	
	//for para pegar os dois maiores filhos do pai
	for (int i = 0; i < (int)g[u].size(); i++) {
		v = g[u][i];
		if(v == pai) continue;
		if(in[v] > mx1){
			mx2 = mx1;
			mx1 = in[v];
		} else if(in[v] > mx2){
			mx2 = in[v];
		}
	}
	
	//for para calcular o out de cada um dos filhos
	for (int i = 0; i < (int)g[u].size(); i++) {
		v = g[u][i];
		if(v == pai) continue;
		if(in[v] == mx1){//nesse caso eu nao posso pegar o mx1, pois é o proprio in do filho que estou olhando (contaria vertice repetido no caminho)
			out[v] = max(out[v], 2 + mx2);
		} else{
			out[v] = max(out[v], 2 + mx1);
		}
		out[v] = max(out[v], 1 + out[u]);//indo para fora da subárvore do pai
		dfs2(v, u);//chama para calcular o out do resto
	}	
}

int main(){
	int n, u, v;
	cin >> n;
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	
	diameter = 0;
	dfs(1, 1);
	out[1] = -inf;
	dfs2(1, 1);
	
	//~ cout << "   in  out\n";
	//~ for (int i = 0; i < n; i++)
	//~ {
		//~ cout << i+1 << ": " << in[i+1] << "   " << out[i+1] << endl;
	//~ }
	
	cout << diameter << "\n";
	
	return 0;
}
