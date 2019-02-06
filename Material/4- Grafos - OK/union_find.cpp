#include <bits/stdc++.h>

using namespace std;

#define N 101010

int n, sz[N], comp[N], cont_comp, maior;

void init(){
	cont_comp = n;
	maior = 1;
	for(int i=0; i<=n; i++) {
		comp[i] = i;
		sz[i] = 1;
	}
}

int find(int i){
	return (comp[i] == i) ? i : comp[i] = find(comp[i]);
}

bool same(int i, int j){
	return find(i) == find(j);
}

void join(int i, int j){
	int x = find(i), y = find(j);
	if(x == y) return;
	
	comp[y] = x;
	sz[x]+=sz[y];
	sz[y] = 0;
	cont_comp--;
	maior = max(maior, sz[x]);
}

int main(){
	int q, a, b;
	char op;
	scanf("%d %d", &n, &q);
	
	init();
	
	while(q--){
		scanf(" %c", &op);
		if(op == 'T'){
			printf("%d %d\n", cont_comp, maior);
			continue;
		}
		scanf("%d %d", &a, &b);
		
		if(op=='F') {
			join(a, b);
		}else{
			printf(find(a) == find(b) ? "sim\n" : "nao\n");
		}
	}
}
