#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define INF INT_MAX

// the graph as an array of edges
typedef struct graph {
	int nv;
	int **adj;
} graph;

void readFile(graph *g) {
	FILE *fp = fopen("PrimsInput.txt", "r");

	fscanf(fp, "%d", &(g->nv));

	g->adj = (int **)calloc(g->nv, sizeof(int*));
	int i, j, k = 0;
	for(i = 0; i < g->nv; i++) {
		g->adj[i] = (int *)calloc(g->nv, sizeof(int));
		for(j = 0; j < g->nv; j++) {			
			fscanf(fp, "%d", &(g->adj[i][j]));
		}
	}
	
	fclose(fp);
}

int min_wt(int *in_mst, int *cost, int nv) {
	
	int min = INF, v = -1, i;
	
	for(i = 0; i < nv; i++) {
		if(in_mst[i] == 0 && cost[i] < min) {
			min = cost[i]; v = i;			
		}
	}
	return v;
}

int* prims_mst(graph *g) {
	
	int *mst_parent = (int *)calloc(g->nv, sizeof(int));
	
	int *cost = (int *)calloc(g->nv, sizeof(int));
	int *in_mst = (int *)calloc(g->nv, sizeof(int));
	
	int i, j;
	for(i = 0; i < g->nv; i++) {
		cost[i] = INF; in_mst[i] = 0;
	}

	cost[0] = 0;
	mst_parent[0] = -1; // root node
	
	for(i = 0; i < g->nv; i++) {
		int u = min_wt(in_mst, cost, g->nv); // vertex with min weight not in MST
		printf("OK\n");

		in_mst[u] = 1;

		for(j = 0; j < g->nv; j++) {
			if(g->adj[u][j] != 0 && in_mst[j] == 0 && g->adj[u][j] < cost[j]) {
				mst_parent[j] = u; cost[j] = g->adj[u][j];
			}
		}
	}
	
	return mst_parent;
}

void showMST(int *mst_parent, graph *g) {
	int i;
	for(i = 0; i < g->nv; i++) {
		printf("%d ----> %d ::: %d\n", mst_parent[i]+1, i+1, g->adj[i][mst_parent[i]]);
	}
}


int main() {

	graph *g = (graph *)malloc(sizeof(graph));

	readFile(g);
	
	int *mst_parent = prims_mst(g);
	showMST(mst_parent, g);

	return 0;
}
