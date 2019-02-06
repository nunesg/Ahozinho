#include <bits/stdc++.h>

using namespace std;

struct SparseTable{
	
	#define N 101010
	#define M 20
	
	int n, table[N][M];
	
	SparseTable() : n(0) {}
	
	SparseTable(int a) : n(a) {}

	void build(){//pressupoe que table[i][0] ja esteja calculado pra todo i
		for(int j=1; j<M; j++){
			for(int i=0; i+(1<<j)<=n; i++){//0-indexado. Pra 1-indexado faça: for(int i=1; i+(1<<j)<=n+1; i++)
				table[i][j] = min(table[i][j-1], table[i+(1<<(j-1))][j-1]);//se for soma, eh so trocar min por soma
			}
		}
	}
	
	int query_min(int l, int r){// pressupoe que l<=r
		int k = 31 - __builtin_clz(r-l+1); //se as variaveis forem long long, faça 63 - __builtin_clz(r-l+1)
		return min(table[l][k], table[r-(1<<k)+1][k]);
	}
	
	int query_soma(int l, int r){//pressupoe que a sparse table calculada seja de soma
		int ans=0;
		for(int j=M-1; j>=0; j--){
			if(l+(1<<j) > r+1) continue;
			ans+=table[l][j];
			l+=(1<<j);
		}
		return ans;
	}
	
};

SparseTable ST;

int main(){
}
