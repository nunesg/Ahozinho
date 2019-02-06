//inicializa com 1 onde tem aresta e 0 onde não tem

for (int k = 0; k < V; k++)
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			dist[i][j] |= (dist[i][k] & dist[k][j]);
