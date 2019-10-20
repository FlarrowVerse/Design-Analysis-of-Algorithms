#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int* input(int *len) {
	printf("Enter size of Array: ");
	scanf("%d", len);
	int *a = (int *)calloc(*len, sizeof(int)), i;
	for(i = 0; i < *len; i++) {
		printf("Enter a number for a[%d]: ", i+1);
		scanf("%d", &a[i]);
	}
	return a;
}

void show(int *a, int len) {
	int i;
	for(i = 0; i < len; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int max(int a, int b) {
	return (a > b)? a: b;
}

int getMaxSum(int *a, int lb, int ub) {

	int i;
	for(i = lb; i <= ub; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	
	if(lb == ub) return a[lb];
	
	int mid = (lb + ub)/2;
	int left_sum = getMaxSum(a, lb, mid);
	int right_sum = getMaxSum(a, mid+1, ub);
	int max_left_right = max(left_sum, right_sum);
	
	int left_max = INT_MIN, right_max = INT_MIN;
	int sum = 0;
	for(i = mid; i >= lb; i--) {
		sum += a[i];
		if(sum > left_max) left_max = sum;
	}
	sum = 0;
	for(i = mid+1; i <= ub; i++) {
		sum += a[i];
		if(sum > right_max) right_max = sum;
	}	

	return max(max_left_right, left_max+right_max);	
}

int main() {

	int size, *a = input(&size);
	printf("Original Array: ");
	show(a, size);

	int sum = getMaxSum(a, 0, size-1);
	printf("Maximum Sub-Array Sum: %d\n\n", sum);
	
	return 0;
}
