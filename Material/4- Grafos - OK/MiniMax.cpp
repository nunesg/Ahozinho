/*
To understand maximin paths (often called bottleneck paths) in a graph, consider the following problem. 
You have a road map of a country as a graph where each node represents an intersection and each edge 
represents a road. Each road has a weight limit, and if you drive a truck that exceeds the limit over 
that road it will break. You have a truck that you want to drive from some start location to some end 
location, and you want to put the maximum possible amount of weight on it. Given this, what path 
should you drive the truck in order to send the maximum possible weight?

If you think about this problem, for any path that you take in the graph, the maximum weight you can 
send along that path is going to be determined by the edge on that path with the minimum capacity. 
As a result, you want to find the path from the start to the destination whose minimum-capacity edge
 is maximized. The path with this property is called the maximin path or bottleneck path, and can be
  found with a straightforward set of modifications to mot shortest-path algorithms.

The minimax path represents the opposite idea - the path between two points that minimizes the 
maximum edge capacity.

Hope this helps!

Minimax: arv. ger. min e maior aresta
Maximin: arv. ger. max e menor aresta
*/
int N, E;
int main()
{
	int i, u, v, w, q;
	int g[200][200];
	int caso=1;

	while(scanf("%d %d %d", &N, &E, &q), N != 0) {	
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				g[i][j]=10000000;
				if(i==j) g[i][j]=0;
			}			
		}

		for(i = 0; i < E; i++) {
			scanf("%d %d %d", &u, &v, &w);
			g[u][v]=w;
			g[v][u]=w;
		}
		
		for(int k = 1; k <= N; k++)
		   for(int i = 1; i <= N; i++)
			  for(int j = 1; j <= N; j++)
				 g[i][j] = min(g[i][j], max(g[i][k], g[k][j]));//pega a maior aresta do caminho (so existe um caminho, é uma arvore)		
	}

	return 0;
}
