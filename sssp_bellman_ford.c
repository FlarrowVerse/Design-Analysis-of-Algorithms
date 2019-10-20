#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define INF INT_MAX

// each edge
typedef struct edge {
	int src, dest, wt;
} EDGE;

// the graph as an array of edges
typedef struct graph {
	int nv, ne;
	EDGE *e;
} graph;

int min(int a, int b) {
	return (a < b)? a: b;
}

int* getShortestPath(graph *g, int src) {
	int i, j, src_vertex = src-1;

	int *dist = (int *)calloc(g->nv, sizeof(int));
	
	for(i = 0; i < g->nv; i++) {
		if(i == src_vertex) dist[i] = 0;
		else dist[i] = INF;
	}
	
	
	for(i = 1; i < g->nv; i++) {
		for(j = 0; j < g->ne; j++) {
			if(dist[(g->e[j]).src] != INF) {
				dist[(g->e[j]).dest] = min(dist[(g->e[j]).dest], dist[(g->e[j]).src] + (g->e[j]).wt);
			}
		}
	}

	for(i = 0; i < g->ne; i++) {
		if(dist[(g->e[i]).src] != INF && dist[(g->e[i]).dest] > (dist[(g->e[i]).src] + (g->e[i]).wt)) {
			printf("Cannot print distances. Negative weight cycle present.\n\n");
			return NULL;
		}
	}
		
	return dist;
}

void readFile(graph *g) {
	FILE *fp = fopen("DirectedGraphEdges.txt", "r");

	fscanf(fp, "%d", &(g->nv));
	fscanf(fp, "%d", &(g->ne));
	
	g->e = (EDGE *)calloc(g->ne, sizeof(EDGE));
	int i, j, k = 0;
	for(i = 0; i < g->nv; i++) {
		for(j = 0; j < g->nv; j++) {
			int wt;
			fscanf(fp, "%d", &wt);
			if(j != i && wt != 0) {				
				(g->e[k]).src = i;
				(g->e[k]).dest = j;
				(g->e[k]).wt = wt;
				k++;
			}
		}
	}
	
	fclose(fp);
}

void showGraph(graph *g) {
	int i;
	for(i = 0; i < g->ne; i++) {
		printf("%d ---> %d :: %d\n", (g->e[i]).src+1, (g->e[i]).dest+1, (g->e[i]).wt);
	}	
}

int main() {

	graph *g = (graph *)malloc(sizeof(graph));	
	readFile(g);

	int i, j;
	
	showGraph(g);

   	int *distances = getShortestPath(g, 1);

	if(distances != NULL) {
		printf("Shortest Distances from Source:\n");
		for(i = 0; i < g->nv; i++) {
			printf("%d ---------> %d :: %d\n", 1, i+1, distances[i]);
		}
	}
	
	return 0;
}
