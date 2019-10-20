#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INF INT_MAX
#define ERR INT_MIN

/*-----------------------------DATA STRUCTURE DEFINITIONS--------------------------------------------------*/
typedef struct STACK {
	int top, size;
	int *a;
} stack;

typedef struct QUEUE {
	int front, rear, size;
	int *a;
} queue;

typedef struct GRAPH {
	int nv;
	int **adj;
} graph;

/*----------------------------STACK METHODS--------------------------------------------*/
int emptyS(stack *s) {
	return (s->top == -1)? 1: 0;
}

int pop(stack *s) {
	if(emptyS(s)) return ERR;
	else {
		s->top = s->top - 1;
		return s->a[(s->top)+1];
	}
}

void push(stack *s, int data) {
	s->a[++(s->top)] = data;
}

/*----------------------------QUEUE METHODS--------------------------------------------*/
int emptyQ(queue *q) {
	return (q->rear == -1 && q->front == -1)? 1: 0;
}

int dequeue(queue *q) {
	if(emptyQ(q)) return ERR;
	else {
		int data = q->a[q->front];
		if(q->front == q->rear) {
			q->front = -1; q->rear = -1;
		}else {
			q->front = (q->front + 1)%(q->size);
		}
		return data;
	}
}

void enqueue(queue *q, int data) {
	q->rear = (q->rear + 1)%(q->size);
	q->a[q->rear] = data;
}

/*---------------------------TRAVERSAL ALGORITHMS---------------------------------------*/
int* traverse_dfs(graph *g) {
	
	int *dfs = (int *)calloc(g->nv, sizeof(int)), index = -1; // to store the bfs traversal
	
	// Stack initializtion
	stack *s = (stack *)malloc(sizeof(stack));
	s->size = g->nv; s->top = -1;
	s->a = (int *)calloc(s->size, sizeof(int));
	push(s, 0);
		

	int *visited = (int *)calloc(g->nv, sizeof(int));

	while(emptyS(s) == 0) {
		int curr = pop(s);		
		if(visited[curr] == 0) {
			visited[curr] = 1;
			dfs[++index] = curr;
			int j;
			for(j = g->nv-1; j >= 0; j--) {
				if(g->adj[curr][j] == 1 && visited[j] == 0) push(s, j);
			}			
		}		
	}	
	return dfs;
}

int* traverse_bfs(graph *g) {
	
	int *bfs = (int *)calloc(g->nv, sizeof(int)), index = -1; // to store the bfs traversal

	// Queue initializtion
	queue *q = (queue *)malloc(sizeof(queue));
	q->size = g->nv; q->front = -1; q->rear = -1;
	q->a = (int *)calloc(q->size, sizeof(int));
	enqueue(q, 0);

	int *visited = (int *)calloc(g->nv, sizeof(int));

	while(emptyQ(q) == 0) {
		int curr = dequeue(q);
		if(visited[curr] == 0) {
			visited[curr] = 1;
			bfs[++index] = curr;
			int j;
			for(j = 0; j < g->nv; j++) {
				if(g->adj[curr][j] == 1 && visited[j] == 0) enqueue(q, j);
			}			
		}		
	}	
	return bfs;
}

/*----------------------------------------IMPLEMENTATION------------------------------------------*/
void readFile(graph *g, int opt) {
	
	FILE *fp;
	
	if(opt == 1) fp = fopen("DFSinput.txt", "r");
	if(opt == 2) fp = fopen("BFSinput.txt", "r");

	fscanf(fp, "%d", &(g->nv));
	
	int i, j;
	g->adj = (int **)calloc(g->nv, sizeof(int*));
	for(i = 0; i < g->nv; i++) {
		g->adj[i] = (int *)calloc(g->nv, sizeof(int));
		for(j = 0; j < g->nv; j++) {
			fscanf(fp, "%d", &(g->adj[i][j]));
		}
	}
	
	fclose(fp);
}

int main() {

	int i;

	graph *g1 = (graph *)malloc(sizeof(graph));
	readFile(g1, 1);

	int *dfs = traverse_dfs(g1);
	printf("\nDEPTH-FIRST SEARCH TRAVERSAL:: ");
	for(i = 0; i < g1->nv; i++) {
		printf("%d\t", dfs[i]);
	}

	graph *g2 = (graph *)malloc(sizeof(graph));
	readFile(g2, 2);

	int *bfs = traverse_bfs(g2);
	printf("\nBREADTH-FIRST SEARCH TRAVERSAL:: ");
	for(i = 0; i < g2->nv; i++) {
		printf("%d\t", bfs[i]);
	}
	printf("\n\n");
	
	return 0;
}
