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

int min(long int a, long int b) {
	return (a < b)? a: b;
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

void copyGraph(graph *dest, graph *src) {
	dest->nv = src->nv;
	dest->adj = (int **)calloc(dest->nv, sizeof(int *));
	int i, j;
	for(i = 0; i < dest->nv; i++) {
		dest->adj[i] = (int *)calloc(dest->nv, sizeof(int));
		for(j = 0; j < dest->nv; j++) {
			dest->adj[i][j] = src->adj[i][j];
		}
	}
}

graph* floyd_warshall_apsp(graph *g) {
	int i, j, k;
	
	graph *dist = (graph *)malloc(sizeof(graph));
	copyGraph(dist, g);

	for(k = 0; k < dist->nv; k++) {
		for(i = 0; i < dist->nv; i++) {
			for(j = 0; j < dist->nv; j++) {
				if(dist->adj[i][k] == INF || dist->adj[k][j] == INF) {
					continue;
				}
				dist->adj[i][j] = min(dist->adj[i][j], dist->adj[i][k] + dist->adj[k][j]);
			}
		}
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

void readFile(graph *g) {
	
	FILE *fp = fopen("DirectedGraphInput.txt", "r");
	
	fscanf(fp, "%d", &(g->nv));
	init(g);
	int i, j;
	for(i = 0; i < g->nv; i++) {
		for(j = 0; j < g->nv; j++) {
			int wt;
			fscanf(fp, "%d", &wt);
			if(wt == 0 && i != j) g->adj[i][j] = INF;
			else g->adj[i][j] = wt;
		}
	}
	fclose(fp);
}

int main() {

	graph *g = (graph *)malloc(sizeof(graph));	
	readFile(g);

	int i, j;
	
	showGraph(*g);

   	graph *distances = floyd_warshall_apsp(g);

	printf("\n\nShortest Distances from Source:\n\n");
	showGraph(*distances);
	
	return 0;
}
