#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void quickSort(int a[], int lb, int ub) {
	if(lb >= ub) return;
	int pivot = (lb + ub)/2;
	int i = lb, j = ub;
	while(i < j) {
		while(a[i] < a[pivot]) i++;
		while(a[j] > a[pivot]) j--;
		
		if(i == pivot) pivot = j;
		else if(j == pivot) pivot = i;
		
		swap(&a[i], &a[j]);
	}
    quickSort(a, lb, pivot-1);
	quickSort(a, pivot+1, ub);
}


void readData() {	
	FILE *inp, *out;
	inp = fopen("inputData", "r");	
	if(inp == NULL) {
		printf("No such file!\n");
		return;
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
	
	quickSort(a, 0, len-1);
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
	
	fprintf(out, "Quick Sort Result:\n");
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
