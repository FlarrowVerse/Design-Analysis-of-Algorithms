#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// each edge
typedef struct edge {
	int src, dest, wt;
} EDGE;

// the graph as an array of edges
typedef struct graph {
	int nv, ne;
	EDGE *e;
} graph;

void readFile(graph *g) {
	FILE *fp = fopen("GraphInput.txt", "r");

	fscanf(fp, "%d", &(g->nv));
	fscanf(fp, "%d", &(g->ne));
	g->e = (EDGE *)calloc(g->ne, sizeof(EDGE));
	int i, j, k = 0;
	for(i = 0; i < g->nv; i++) {
		for(j = 0; j < g->nv; j++) {
			int wt;
			fscanf(fp, "%d", &wt);
			if(j > i && wt > 0) {				
				(g->e[k]).src = i;
				(g->e[k]).dest = j;
				(g->e[k]).wt = wt;
				k++;
			}
		}
	}
	
	printf("Vertices: %d\nEdges: %d\n", g->nv, g->ne);
		
	fclose(fp);
}

void showGraph(graph *g) {
	int i;
	for(i = 0; i < g->ne; i++) {
		printf("%d ---> %d :: %d\n", (g->e[i]).src+1, (g->e[i]).dest+1, (g->e[i]).wt);
	}	
}

void merge(graph *g, int lb, int mid, int ub) {
	EDGE temp[ub-lb+1]; 
    int i, j, k;
    for(i = lb, j = mid+1, k = 0; i <= mid && j <= ub; ) {
        if((g->e[i]).wt < (g->e[j]).wt) {
            temp[k++] = g->e[i++];
        }
        else if((g->e[i]).wt == (g->e[j]).wt) {
            temp[k++] = g->e[i++];
            temp[k++] = g->e[j++];
        }else {
            temp[k++] = g->e[j++];
        }
    }

    while(i <= mid) temp[k++] = g->e[i++] ;
    while(j <= ub) temp[k++] = g->e[j++];
    for(i = lb; i <= ub; i++) {
        g->e[i] = temp[i-lb];
    }
}

void sortEdges(graph *g, int lb, int ub) {
	if(lb < ub) {
		int mid = (lb+ub)/2;
		sortEdges(g, lb, mid);
		sortEdges(g, mid+1, ub);
		merge(g, lb, mid, ub);
	}
}

int formsCycle(EDGE *mst, int curr_edges, EDGE new_edge) {
	int i, src_flag = 0, dest_flag = 0;
	for(i = 0; i <= curr_edges; i++) {
		if(mst[i].src == new_edge.src) src_flag = 1;
		if(mst[i].dest == new_edge.dest) dest_flag = 1;
	}
	return (src_flag & dest_flag);
}

EDGE* kruskal_mst(graph *g) {
	EDGE *mst = (EDGE *)calloc(g->nv-1, sizeof(EDGE));
	mst[0] = g->e[0];
	int i, j = 1;
	for(i = 1; i < g->ne && j < g->nv; i++) {
		if(formsCycle(mst, j, g->e[i]) == 0) {
			mst[j++] = g->e[i];
		}
	}
	
	return mst;
}

void showMST(EDGE *mst, int len) {
	int i;
	for(i = 0; i < len; i++) {
		printf("%d ----%d---- %d\n", mst[i].src+1, mst[i].wt, mst[i].dest+1);
	}
}


int main() {

	graph *g = (graph *)malloc(sizeof(graph));

	readFile(g);
	printf("Before Sorting: \n");
	showGraph(g);
	sortEdges(g, 0, g->ne-1);
	printf("After Sorting: \n");
	showGraph(g);

	EDGE *mst = kruskal_mst(g);
	showMST(mst, g->nv-1);

	return 0;
}
