#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define INF INT_MAX

typedef struct graph {
	int **adj;
	int nv;
} graph;


int allVisited(int a[], int n) {
	int i;
	for(i = 0; i < n; i++)
		if(a[i] != 1) return 0;
	return 1;
}

int min(int a, int b) {
	return (a < b)? a: b;
}

int* getShortestPath(graph *g, int source) {
	int i, j;
	
	int *visited = (int*)calloc(g->nv, sizeof(int)), *dist = (int*)calloc(g->nv, sizeof(int));
	for(i = 0; i < g->nv; i++) {
		visited[i] = 0;
		dist[i] = (i == source-1)? 0: INF;
	}

	int src_vertex = source-1;
	while(allVisited(visited, g->nv) == 0) {
		int index = -1, minDist = INF;
		for(j = 0; j < g->nv; j++) {
			if(j != src_vertex && visited[j] == 0 && g->adj[src_vertex][j] != 0) {
				dist[j] = min(dist[j], dist[src_vertex] + g->adj[src_vertex][j]);
				if(dist[j] < minDist) {
					index = j;
					minDist = dist[j];
				}
			}
		}
		visited[src_vertex] = 1;
		src_vertex = index;
	}

	return dist;
}


void init(graph *g) {	
	g->adj = (int **)calloc(g->nv, sizeof(int *));
	int i;
	for(i = 0; i < g->nv; i++) {
		g->adj[i] = (int *)calloc(g->nv, sizeof(int));
	}
}

void input(graph *g) {
	
	int M, A, B;
	scanf(fp, "%d", &(g->nv));
	init(g);
	int i, j;
	for(i = 0; i < g->nv; i++) {
		for(j = 0; j < g->nv; j++) {
			fscanf(fp, "%d", &(g->adj[i][j]));
		}
	}
	fclose(fp);
}

void showGraph(graph g) {
	int i, j;
	for(i = 0; i < g.nv; i++) {
		for(j = 0; j < g.nv; j++) {
			printf("%d\t", g.adj[i][j]);
		}
		printf("\n");
	}
}

int main() {

	graph *g = (graph *)malloc(sizeof(graph));	
	readFile(g);

	int i, j;
	
	showGraph(*g);

   	int *distances = getShortestPath(g, 1);

	printf("Shortest Distances from Source:\n");
	for(i = 0; i < g->nv; i++) {
		printf("%d ---------> %d :: %d\n", 1, i+1, distances[i]);
	}
	
	return 0;
}
