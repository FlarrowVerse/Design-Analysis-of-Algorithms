#include <stdio.h>
#include <stdlib.h>

int binarySearch(int a[], int lb, int ub, int num) {
	if(lb <= ub) {
		int mid = (lb + ub)/2;
		if(a[mid] == num) return mid;
		else if(a[mid] > num) return binarySearch(a, lb, mid-1, num);
		else return binarySearch(a, mid+1, ub, num);
	}
	return -1;
}


void readData() {	
	FILE *inp, *out;
	inp = fopen("binaryInput.txt", "r");	
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
	
	int q;
	fscanf(inp, "%d\n", &q);	
	int query[q];
	for(i = 0; i < q; i++) {
		fscanf(inp, "%d ", &query[i]);
	}
	
	printf("\nSorted Array:\n");	
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
	
	fprintf(out, "Binary Search Result:\n");
	for(i = 0; i < q; i++) {
		int index = binarySearch(a, 0, len-1, query[i]);
		if(index == -1) fprintf(out, "%d not found!\n", query[i]);
		else fprintf(out, "%d found at position %d.\n", query[i], index+1);
	}
	fprintf(out, "\n----------------------------------------------------------------------------------------------------------\n");
	fclose(out);
}

int main() {

	readData();
	
	return 0;
}
