#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#define INF INT_MAX
#define all_visited (1<<(g->v))-1

typedef struct graph {
	int v;
	int **adj;
} graph;

void init(graph *g) {
	FILE *fp = fopen("tsp_graph.txt", "r");

	fscanf(fp, "%d", &(g->v));
	int i, j;
	
	g->adj = (int **)calloc(g->v, sizeof(int *)); 
	for(i = 0; i < g->v; i++) {
		g->adj[i] = (int *)calloc(g->v, sizeof(int));
		for(j = 0; j < g->v; j++) {
			fscanf(fp, "%d", &(g->adj[i][j]));
		}
	}
	
	fclose(fp);
}

void show(graph *g) {
	int i, j;
	for(i = 0; i < g->v; i++) {
		for(j = 0; j < g->v; j++) {
			printf("%d ", g->adj[i][j]);
		}
		printf("\n");
	}	
}

int min(int a, int b) {
	return (a < b)? a: b;
}

int getMinHamiltonian(graph *g, int curr, int mask, int org, int **dp) {
	if(mask == all_visited) {
		return g->adj[curr][org];
	}
	else if(dp[mask][curr] != -1) {
		return dp[mask][curr];
	}else {
		int i, dist = INF;
		for(i = 0; i < g->v; i++) {
			if((mask & (1 << i)) == 0) {
				int newDist = g->adj[curr][i] + getMinHamiltonian(g, i, mask | (1 << i), org, dp);
				dist = min(newDist, dist);
			}
		}
		dp[mask][curr] = dist;	
		return dist;
	}
}

int main() {

	graph *g = (graph *)malloc(sizeof(graph));
	init(g); show(g);

	int i,j;
	int **dp = (int**)calloc(pow(2, g->v), sizeof(int *));
	for(i = 0; i < pow(2, g->v); i++) {
		dp[i] = (int *)calloc(g->v, sizeof(int));
		for(j = 0; j < g->v; j++) {
			dp[i][j] = -1;
		}
	}
	
	int cost = getMinHamiltonian(g, 0, 1, 0, dp);
	printf("Cost of TSP:: %d\n", cost);
	
	return 0;
}
