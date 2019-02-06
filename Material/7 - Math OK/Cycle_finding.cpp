
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

//Floyd's Cycle Finding Algorithm. Complexidade: O(tamanho maximo do ciclo)
int f(int x){
	//dado pelo problema
}

ii solve(int L){	
	int cycle_len, cycle_begin;
	int x=f(L), y = f(f(L));
	
	while(x!=y) {  //faz os dois ponteiros se encontrarem
		x = f(x);
		y = f(f(y));
	}
	
	cycle_len = 1;
	y = f(x);
	while(x!=y){   //anda com um e descobre o tamanho do ciclo
		cycle_len++;
		y = f(y);
	}
	
	x = y = L;
	for(int i=0; i<cycle_len; i++) y = f(y);
	
	cycle_begin = 0;
	while(x!=y){   //acha o começo do ciclo
		x = f(x);
		y = f(y);
		cycle_begin++;
	}
	return ii(cycle_begin, cycle_len);
}

int main(){
	
}