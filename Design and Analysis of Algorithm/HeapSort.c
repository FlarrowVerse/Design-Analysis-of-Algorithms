#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void createHeap(int a[],int n) {
	int i;
	for(i = 1; i < n; i++) {
		int child = i;
		while(child != 0) {
			int parent = (child-1)/2;
			if(a[parent] > a[child]) break;
			swap(&(a[parent]), &(a[child]));
			child = parent;
		}
	}
}

void deleteHeap(int a[],int n) {
	int i;
	for(i = n-1; i >= 1; i--) {
		swap(&(a[0]), &(a[i]));
		createHeap(a,i);
	}
}

void heap_sort(int a[], int n) {
	createHeap(a,n);
	deleteHeap(a,n);
}

void readData() {
	
	FILE *inp, *out;
	inp = fopen("inputData", "r");
	
	if(inp == NULL) {
		printf("No such file!\n");
		exit(1);
	}
	
	int len;
	fscanf(inp, "%d\n", &len);
	
	int i, a[len];
	for(i = 0; i < len; i++) {
		fscanf(inp, "%d ", &a[i]);
	}
		
	printf("Unsorted array: \n");
	for(i = 0; i < len; i++) {
		printf("%d ", a[i]);
	}
	printf("\nSorted Array:\n");	
	
	heap_sort(a, len);
	for(i = 0; i < len; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");		
	fclose(inp);
	
	out = fopen("outputData.txt", "a");
	if(out == NULL) {
		printf("No such file!\n");
		return;
	}
	
	fprintf(out, "Heap Sort Result:\n");
	for(i = 0; i < len; i++) {
		fprintf(out, "%d ", a[i]);
	}
	fprintf(out, "\n----------------------------------------------------------------------------------------------------------\n");
	fclose(out);
}



int main() {

	readData();
	
	return 0;
}
