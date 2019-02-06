int trie[MAXN][26];
char fim[MAXN];
int counter[MAXN];
string s;
int cnt = 2;

void add(){
	int no = 1;//1 é a raiz
	int c;
	
	for (int i = 0; i < (int)s.size(); i++)
	{
		c = s[i]-'a';
		if(!trie[no][c]){
			trie[no][c] = cnt++;
		}
		no = trie[no][c];
		counter[no]++;
	}
	fim[no] = 1;
}

int main(){
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> s;
		add();
	}
	
	
	return 0;
}
