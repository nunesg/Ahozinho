#include <bits/stdc++.h>

using namespace std;

#define N 101010

struct state{
	int len, link;
	map< char, int >  nxt;//se possivel nao usar map
	state(){
		len = 0; link = -1; nxt.clear();
	}
}st[N<<1];

string s;
int sz, last, fim[N<<1], diff_sub;

void add_caracter(char c){
	int curr = ++sz;
	int p, clone, q;
	for( p = last; p>=0 && !st[p].nxt.count(c); p = st[p].link) {
		st[p].nxt[c] = curr;
	}
	
	if(p==-1){
		st[curr].link = 0;
	}else{
		
		q = st[p].nxt[c];
		if(st[p].len + 1 == st[q].len){
			st[curr].link = q;
		}else{
			
			clone = ++sz;
			
			st[clone] = st[q];
			st[clone].len = st[p].len+1;
			diff_sub-= st[q].len - st[st[q].link].len;
			
			st[q].link = st[curr].link = clone;
			
			diff_sub+= st[q].len - st[clone].len;
			diff_sub+= st[clone].len - st[st[clone].link].len;
			
			for(; p>=0; p = st[p].link){
				if(st[p].nxt[c]) st[p].nxt[c] = clone;
			}
			
		}
	}
	
	
	st[curr].len = st[last].len+1;
	diff_sub+= st[curr].len - st[st[curr].link].len;
	last = curr;
}

string aux;

void dfs(int u){//printa todos os sufixos da string ordenados
	if(fim[u]) cout << aux << endl;
	for(auto p : st[u].nxt){
		char c = p.first;
		int v = p.second;
		aux.push_back(c);
		dfs(v);
		aux.pop_back();
	}
}

void build(){
	sz = last = diff_sub = 0;
	for(int i=0; i<s.size(); i++){
		add_caracter(s[i]);
		printf("diff_substring = %d\n", diff_sub);
	}
	
	for(int p = last; p; p = st[p].link) fim[p] = 1; //só quando for necessario
	
	dfs(0);
}


int main(){
	cin >> s;
	
	build();
}
