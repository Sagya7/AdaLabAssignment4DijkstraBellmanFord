#include <iostream>

int findMinDistanceOfAdjacencyNodes(int* dist, bool* is_vertex_finalised, int number_of_vertices)
{
	// Initialize min value to maximum
	int min = INT_MAX, min_index;

	for (int v = 0; v < number_of_vertices; v++)
	{
		if (is_vertex_finalised[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;
	}
	return min_index;
}

void printDijkstra(int* dist, int number_of_vertices)
{
	std::cout << "Vertex \t Distance from Source" << std::endl;
	for (int i = 0; i < number_of_vertices; i++)
		std::cout << i << " \t\t" << dist[i] << std::endl;
}

void dijkstra()
{
	std::cout << "Enter the number of vertices in the graph ";
	int number_of_vertices = 0;
	std::cin >> number_of_vertices;
	int* graph = (int*)malloc((number_of_vertices* number_of_vertices) * sizeof(int));
	for (int i = 0; i < number_of_vertices; i++)
	{
		for (int j = 0; j < number_of_vertices; j++)
		{
			graph[(i*number_of_vertices) + j] = 0;
		}
	}

	std::cout << "Enter number of edges present in the graph ";
	int number_of_edges = 0;
	std::cin >> number_of_edges;
	std::cout << "Enter the edges and its weight. Example: 1 2 8 this says there is edge between 1 and 2 with weight 8\n";
	int u, v, weight;
	for (int i = 0; i < number_of_edges; i++)
	{
		std::cin >> u;
		std::cin >> v;
		std::cin >> weight;
		graph[u * number_of_vertices + v] = weight;
		graph[v * number_of_vertices + u] = weight;
	}

	//holds shortest distance.
	int* dist = (int*)malloc(number_of_vertices * sizeof(int));

	//array of flag to indicate whether distance is finalized.
	bool* distFinalized = (bool*)malloc(number_of_vertices * sizeof(bool));

	//initialize dist and distFinalized arrays
	for (int i = 0; i < number_of_vertices; i++)
	{
		dist[i] = INT_MAX;
		distFinalized[i] = false;
	}

	// src distance to itself.
	int src = 0;
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < number_of_vertices - 1; count++)
	{
		int u = findMinDistanceOfAdjacencyNodes(dist, distFinalized, number_of_vertices);

		// uth vertex's distance from source is finalized.
		distFinalized[u] = true;

		for (int v = 0; v < number_of_vertices; v++)
		{
			if (!distFinalized[v] && graph[(u*number_of_vertices) + v] && dist[u] != INT_MAX
				&& dist[u] + graph[(u*number_of_vertices) + v] < dist[v])
			{
				dist[v] = dist[u] + graph[(u*number_of_vertices)+v];
			}
		}
	}
	printDijkstra(dist, number_of_vertices);
}


void printBellmanAndFord(int dist[], int n)
{
	printf("Vertex Distance from Source\n");
	for (int i = 0; i < n; ++i)
		printf("%d \t\t %d\n", i, dist[i]);
}

void bellmanAndFord()
{
	std::cout << "Enter the number of vertices in the graph ";
	int number_of_vertices = 0;
	std::cin >> number_of_vertices;
	int V = number_of_vertices;

	std::cout << "Enter number of edges present in the graph ";
	int number_of_edges = 0;
	std::cin >> number_of_edges;
	int E = number_of_edges;
	int* edges = (int*)malloc(sizeof(int) * E * 3);
	std::cout << "Enter the edges and its weight Example: 1 2 8 this says there is edge between 1 and 2 with weight 8\n";
	int u, v, weight;
	for (int i = 0; i < number_of_edges; i++)
	{
		std::cin >> u;
		std::cin >> v;
		std::cin >> weight;
		edges[(i * 3) + 0] = u;
		edges[(i * 3) + 1] = v;
		edges[(i * 3) + 2] = weight;
	}

	int* dist = (int*)malloc(sizeof(int) * number_of_vertices);
	int src = 0;

	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX;
	dist[src] = 0;

	for (int i = 1; i <= V - 1; i++) 
	{
		for (int j = 0; j < E; j++)
		{
			int u = edges[j*3];
			int v = edges[j*3 + 1];
			int weight = edges[(j * 3) + 2];
			if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
				dist[v] = dist[u] + weight;
		}
	}

	// to detect negative cycle do nth time relaxation.
	for (int i = 0; i < E; i++)
	{
		int u = edges[i * 3];
		int v = edges[i * 3 + 1];
		int weight = edges[i * 3 + 2];
		if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
		{
			printf("Graph contains negative weight cycle");
			return;
		}
	}

	printBellmanAndFord(dist, V);
	return;
}

int main()
{
	while (true)
	{
		std::cout << "Plese note: If there are n vertices then first vertice is 0 and last vertice is n-1. Folow this notation throughout....\n\n";
		std::cout << "Press D to run dijkstra algorithm or B to run Bellman and Ford algorithm or q to quit\n";
		char next;
		std::cin >> next;
		if (next == 'D')
			dijkstra();
		else if (next == 'B')
			bellmanAndFord();
		else if (next == 'q')
			break;
		std::cout << "\n..............................................\n" << std::endl;
	}
	return 0;
}

