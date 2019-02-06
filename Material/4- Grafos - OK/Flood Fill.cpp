//expande todas as células com T onde tem A

#define MAXN 55
char vis[MAXN][MAXN];
char grid[MAXN][MAXN];
int n, m;
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};

bool pode(int x, int y){
	return x>=0 && x<n && y>=0 && y<m && !vis[x][y] && grid[x][y] == 'A';
}

void dfs(int x, int y){
	vis[x][y] = 1;
	grid[x][y] = 'T';
	
	for (int i = 0; i < 4; i++)
	{
		if(pode(x+dx[i], y+dy[i])){
			dfs(x+dx[i], y+dy[i]);
		}
	}
}

int main(){
	while (cin >> n >> m)
	{
		if(n==0 && m==0) break;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cin >> grid[i][j];
			}
		}
		memset(vis, 0, sizeof vis);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if(!vis[i][j] && grid[i][j] == 'T'){
					dfs(i, j);
				}
			}
		}
		
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cout << grid[i][j];
			}
			cout << "\n";
		}
		cout << "\n";
	}
	
	
	return 0;
}
