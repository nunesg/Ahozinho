#include <bits/stdc++.h>

using namespace std;

#define N 201010
#define F first
#define S second

typedef pair<int, int> ii;
typedef pair<int, ii> iii;


int n, comp[N], m;
vector<iii> edge;

void init(){
	edge.clear();
	for(int i=0; i<=n; i++) comp[i] = i;
}

int find(int i){
	return (comp[i] == i) ? i : comp[i] = find(comp[i]);
}

bool same(int i, int j) {
	return find(i) == find(j);
}

void join(int i, int j){
	comp[find(i)] = find(j);
}

int MST(){
	
	sort(edge.begin(), edge.end());
	int ans=0;
	for(int i=0; i<m; i++){
		int u = edge[i].S.F, v = edge[i].S.S, w = edge[i].F;
		if(!same(u, v)){
			join(u, v);
			ans+=w;
		}
	}
	return ans;
}

int main(){
	while(scanf("%d %d", &n, &m)){
		if(!n && !m) break;
		init();
		int a, b, c, tot=0;
		for(int i=0; i<m; i++){
			scanf("%d %d %d", &a,&b,&c);
			edge.push_back(iii(c, ii(a, b)));
			tot+=c;
		}
		
		printf("%d\n", tot-MST());
	}
	
}
