#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int* getPart(int *a, int size, int offset, int *len) {
	int i, j = 0;
	for(i = 0; i < size; i++) if(abs(a[i] % 2) == offset) (*len)++;
	int *part = (int *)calloc(*len, sizeof(int));
	
	for(i = 0; i < size; i++) if(abs(a[i]%2) == offset) part[j++] = a[i];
	
	return part;
}


int getMax(int *a, int start, int end) {
	if(end == start) return a[start];
	else if(end-start == 1) {
		return ((a[start] > a[end])? a[start]: a[end]);
	}else {
		int mid = (start+end)/2;
		int max1 = getMax(a, start, mid);
		int max2 = getMax(a, mid+1, end);
		return ((max1 > max2)? max1: max2);
	}	
}

int getMin(int *a, int start, int end) {
	if(end == start) return a[start];
	else if(end-start == 1) {
		return ((a[start] < a[end])? a[start]: a[end]);
	}else {
		int mid = (start+end)/2;
		int min1 = getMin(a, start, mid);
		int min2 = getMin(a, mid+1, end);
		return ((min1 < min2)? min1: min2);
	}	
}

int* readFile(int *n) {
	FILE *infile = fopen("InputData.txt", "r");
	int *a;
	if(infile == NULL) {
		printf("No such file!!\n");
		return NULL;
	}
	fscanf(infile, "%d\n", n);
	
	int i;
	a = (int *)calloc(*n, sizeof(int));
	for(i = 0; i < *n; i++) {
		fscanf(infile, "%d", &a[i]);
	}	
	fclose(infile);
	return a;
}

void writeFile(int *a, int n, int max, int min) {
	FILE *outfile = fopen("OutputData.txt", "a");
	if(outfile == NULL) {
		printf("No such file!!\n");
		return;
	}
	fprintf(outfile, "Data Array: ");
	
	int i;
	for(i = 0; i < n; i++) {
		fprintf(outfile, "%d ", a[i]);
	}
	fprintf(outfile, "\nMaximum element: %d\nMinimum Element: %d", max, min);
	fprintf(outfile, "\n--------------------------------------------------------------------------------------------------------------------\n");
	fclose(outfile);
}

int main() {

	int n, *a, e_size, o_size, i;

	a = readFile(&n);

	if(a == NULL) return 1;
	
	int *even = getPart(a, n, 0, &e_size);
	int *odd = getPart(a, n, 1, &o_size);
	
	for(i = 0; i < n; i++) printf("%d ", a[i]);
	
	printf("\nEven elements: ");
	for(i = 0; i < e_size; i++) printf("%d ", even[i]);
	printf("\nMax using Divide and conquer: %d\n", getMax(even, 0, e_size-1));
	printf("Min using Divide and conquer: %d\n", getMin(even, 0, e_size-1));
	
	printf("Odd elements: ");
	for(i = 0; i < o_size; i++) printf("%d ", odd[i]);
	printf("\nMax using Divide and conquer: %d\n", getMax(odd, 0, o_size-1));
	printf("Min using Divide and conquer: %d\n", getMin(odd, 0, o_size-1));

	//writeFile(a, n, getMax(a, 0, n-1), getMin(a, 0, n-1));
	
	return 0;
}
