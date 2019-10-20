#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int* input(int len) {
	int *a = (int *)calloc(len, sizeof(int));
	int i;
	for(i = 0; i < len; i++) {
		printf("d%d:: ", i);
		scanf("%d", &a[i]);
	}
	return a;
}

int** makeTable(int **memo, int size) {
	memo = (int **)calloc(size, sizeof(int *));
	int i;
	for(i = 0; i < size; i++) {
		memo[i] = (int *)calloc(size, sizeof(int));
	}
	return memo;
}

void showTable(int **memo, int size) {
	int i, j;
	for(i = 0; i < size; i++) {
		for(j = 0; j < size; j++) printf("%d\t", memo[i][j]);
		printf("\n");
	}
}

void memoize(int **memo, int *d, int size) {
	int i, j, k, l;	
	
	char *par[size][size];
	
	for(i = 0; i < size; i++) {
		for(j = 0; j < size; j++) {
			par[i][j] = (char *)malloc(size * 2 * sizeof(char));
			if(i == j) sprintf(par[i][j], "%c%d", 'A', i+1);
		}
	}
	
	for(i = size-2; i >= 0; i--) {
		for(j = i+1; j < size; j++) {						
			int m = INT_MAX;
			for(k = i, l = 0; k <= j-1; k++) {			
				int val = memo[i][k] + memo[k+1][j] + d[i]*d[k+1]*d[j+1];
				if(val < m) {
					m = val;
					sprintf(par[i][j], "( %s * %s )", par[i][k], par[k+1][j]);
				}
			}
			memo[i][j] = m;
		}
	}
	
	printf("Optimal Parenthesisation: %s\n", par[0][size-1]);
}


int main() {

	int **memo, size, len;	
	printf("Number of matrices: ");
	scanf("%d", &size);
	len = size+1;
	int *d = input(len);
	
	memo = makeTable(memo, size);
	printf("Before memoization::\n");
	showTable(memo, size);	

	memoize(memo, d, size);	
	printf("After memoization::\n");
	showTable(memo, size);
	
	printf("Minimum number of multiplications is: %d\n", memo[0][size-1]);
	return 0;
}
