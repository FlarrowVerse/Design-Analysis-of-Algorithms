#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Method definitions start here---------------------------------------------------------------*/
int** makeMatrix(int ,int);
//int** setMatrix(int*, int*);
void showMatrix(int**, int, int);
void eraseMatrix(int**, int*, int*);
int** getPartMatrix(int**, int, int, int);
int** add(int**, int**, int);
int** sub(int**, int**, int);
void joinMatrix(int**, int**, int**, int**, int**, int);
int** strassen(int**, int**);
int** strassenMultiply(int**, int, int**, int);
int** readFile(int*, int*, int);
void writeFile(int**, int, int);
/*Method definitions end here---------------------------------------------------------------*/

/*==============================================================================================================================================*/

/* creates an empty matrix of dimension row x col and intializes with 0 */
int** makeMatrix(int row, int col) {
    int **a;
    a = (int **)calloc(row, sizeof(int*)); // init of a 1D array of type int * 
    int i, j;
    for(i = 0; i < row; i++) {
	  a[i] = (int *)calloc(col, sizeof(int)); // init of a 1D array of type int and storing in i-th int*
        for(j = 0; j < col; j++) {
            a[i][j] = 0;
        }
    }
    return a;
}

/* creates an empty Matrix and fills them with user input */
/* int** setMatrix(int *row, int *col) {
  	int **a, k;
    printf("Enter matrix size: ");
    scanf("%d", &k); // matrix size will be 2^k
    *row = pow(2, k);
	*col = pow(2, k);

    a = makeMatrix(*row, *col); // empty matrix init
    int i, j;
    for(i = 0; i < (*row); i++) {
        for(j = 0; j < (*col); j++) {
		  printf("a[%d][%d]:", i,j); // user prompt
		  scanf("%d", &a[i][j]); // user input
        }
    }
    return a;
	}*/

/* displays the matrix passed as param */
void showMatrix(int **a, int row, int col) {
    int i, j;
    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
}

/* frees the memory of the matrix passed as param */
void eraseMatrix(int **a, int *row, int *col) {
    int i = 0;
    while(i < *row) {
        free(a[i]);
        i++;
    }
    *col = -1; *row = -1;
}

/* returns a part of the og matrix starting from (starti, startj) and of size size */
int** getPartMatrix(int **a, int starti, int startj, int size) {
  	int **part = makeMatrix(size, size);
    int i, j;

	for(i = starti; i < starti+size; i++) {
      	for(j = startj; j < startj+size; j++) {
          	part[i-starti][j-startj] = a[i][j];
      	}
    }
    
    return part;
}

/* adds two matrices and returns the result */
int** add(int **a, int **b, int size) {
  	int **sum = makeMatrix(size, size);
    int i, j;

	for(i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
          	sum[i][j] = a[i][j] + b[i][j];
        }
    }
    
  	return sum;
}

/* subtracts matrix b from a and returns the difference */
int** sub(int **a, int **b, int size) {
  	int **diff = makeMatrix(size, size);
    int i, j;

	for(i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
          	diff[i][j] = a[i][j] - b[i][j];
        }
    }
    
  	return diff;
}

/* Given four square matrices of dimensions size/2, it combines them to form a larger matrix of size size. Here, a = {{a11, a12}, {a21, a22}}*/
void joinMatrix(int **a, int **a11, int **a12, int **a21, int **a22, int size) {
  int i, j, k = 0, l = 0;
  	for(i = 0; i < size/2; i++) {
	  	for(j = 0; j < size/2; j++) {
		  a[i][j] = a11[k][l++]; // a11
		}
		k++; l = 0;
	}
	k = 0; l = 0;
	for(i = 0; i < size/2; i++) {
	  	for(j = size/2; j < size; j++) {
		  a[i][j] = a12[k][l++]; // a12
		}
		k++; l = 0;
	}
	k = 0; l = 0;
	for(i = size/2; i < size; i++) {
	  	for(j = 0; j < size/2; j++) {
		  a[i][j] = a21[k][l++]; // a21
		}
		k++; l = 0;
	}
	k = 0; l = 0;
	for(i = size/2; i < size; i++) {
	  	for(j = size/2; j < size; j++) {
		  a[i][j] = a22[k][l++]; // a22
		}
		k++; l = 0;
	}
}


/* Underdeveloped Strassen Multiplication algorithm for n x n matrix, where n = 2^k */
int** strassenMultiply(int **a, int asize, int **b, int bsize) {
  	if(asize == 2) {
	  return strassen(a, b); // base case for recursive calls
  	}
    int **prod = makeMatrix(asize, asize); // init of product matrix
	int subSize = asize/2; // size of sub matrices

    int **a11 = getPartMatrix(a, 0, 0, subSize), **a12 = getPartMatrix(a, 0, subSize, subSize);
    int **a21 = getPartMatrix(a, subSize, 0, subSize), **a22 = getPartMatrix(a, subSize, subSize, subSize); // sub-parts of a  
    int **b11 = getPartMatrix(b, 0, 0, subSize), **b12 = getPartMatrix(b, 0, subSize, subSize);
    int **b21 = getPartMatrix(b, subSize, 0, subSize), **b22 = getPartMatrix(b, subSize, subSize, subSize); // sub-parts of b

	int **p1 = strassenMultiply(a11, subSize, sub(b12, b22, subSize), subSize); // a11 x ( b12 - b22 )
	int **p2 = strassenMultiply(add(a11, a12, subSize), subSize, b22, subSize); // ( a11 + a12 ) x b22
	int **p3 = strassenMultiply(add(a21, a22, subSize), subSize, b11, subSize); // ( a21 + a22 ) x b11
	int **p4 = strassenMultiply(a22, subSize, sub(b21, b11, subSize), subSize); // a22 x ( b21 - b11 )
	int **p5 = strassenMultiply(add(a11, a22, subSize), subSize, add(b11, b22, subSize), subSize); // ( a11 + a22 ) x ( b11 + b22 )
	int **p6 = strassenMultiply(sub(a12, a22, subSize), subSize, add(b21, b22, subSize), subSize); // ( a12 - a22 ) x ( b21 + b22 )
	int **p7 = strassenMultiply(sub(a11, a21, subSize), subSize, add(b11, b12, subSize), subSize); // ( a11 - a21 ) x ( b11 + b12 )

	int **prod11 = add(sub(add(p5, p4, subSize), p2, subSize), p6, subSize);
	int **prod12 = add(p1, p2, subSize);
	int **prod21 = add(p3, p4, subSize);
	int **prod22 = sub(sub(add(p1, p5, subSize), p3, subSize), p7, subSize);
	
	joinMatrix(prod, prod11, prod12, prod21, prod22, asize); // forming product matrix
    
    return prod;
}

/* multiplication algorithm for 2x2 matrix */
int** strassen(int **a, int **b) {
  	int p1, p2, p3, p4, p5, p6, p7; // the 7 basic sub-problems for Strassen's algorithm
  	p1 = a[0][0]*(b[0][1] - b[1][1]);
	p2 = (a[0][0] + a[0][1]) * b[1][1];
	p3 = (a[1][0] + a[1][1]) * b[0][0];
	p4 = a[1][1] * (b[1][0] - b[0][0]);
	p5 = (a[0][0] + a[1][1]) * (b[0][0] + b[1][1]);
	p6 = (a[0][1] - a[1][1]) * (b[1][0] + b[1][1]);
	p7 = (a[0][0] - a[1][0]) * (b[0][0] + b[0][1]);
	int **prod = makeMatrix(2, 2);
	prod[0][0] = p5 + p4 - p2 + p6;
	prod[0][1] = p1 + p2;
	prod[1][0] = p3 + p4;
	prod[1][1] = p1 + p5 - p3 - p7;
	return prod;
}

int** readFile(int *row, int *col, int seek) {
	
	char buff[256];	
	int n, **a, i, j;	
	FILE *fp = fopen("InputMatrix.txt", "r");
	
	if(fp == NULL) {
		printf("No such file!\n");
		return NULL;
	}
	
	while(seek > 0) {
		fgets(buff, 256, fp);
		seek--;
	}
	fscanf(fp, "%d", &n);
	*row = pow(2, n);
	*col = pow(2, n);
	a = makeMatrix(*row, *col);
	for(i = 0; i < *row; i++) {
		for(j = 0; j < *col; j++) {
			fscanf(fp, "%d", &a[i][j]);			
		}		
	}
	fclose(fp);
	return a;
}

void writeFile(int **a, int row, int col) {
	FILE *fp = fopen("OutputMatrix.txt", "a");
	int i, j;
    if(fp == NULL) {
		printf("No such file!\n");
		return;
	}
	fprintf(fp, "PRODUCT MATRIX::\n");
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			fprintf(fp, "%d\t", a[i][j]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n-------------------------------------------------------------------------------------------------------------------------\n");
	fclose(fp);
}


int main() {

    int **a, **b, **c;
    int ar = -1, ac = -1, br = -1, bc = -1, cr = -1, cc = -1, i, j;

	printf("STRASSEN'S METHOD OF MATRIX MULTIPLICATION::\n-------------------------------------------------------------------\n");
	printf("\nStrassen's Method works for matrices of size 2^k, so to enter the matrix size enter the value of k only.\n");

    //while(1) {
        
        printf("Matrix-1:\n");
        a = readFile(&ar, &ac, 0);
        showMatrix(a, ar, ac);

        printf("Matrix-2:\n");
        b = readFile(&br, &bc, ar+1);        
        showMatrix(b, br, bc);
		
		cr = ar; cc = ac;
		printf("\nThe product Matrix is:\n");
        c = strassenMultiply(a, ar, b, br); // multiplying matrices A and B
        showMatrix(c, cr, cc);

		writeFile(c, cr, cc);

        eraseMatrix(a, &ar, &ac);
        eraseMatrix(b, &br, &bc);
		eraseMatrix(c, &cr, &cc);

        /**printf("Do you want to continue?(Y/N): ");
        getchar();
		char choice = getchar();
        if(choice != 'Y' && choice != 'y') {
		  	printf("Exiting Program!......\n\n");
            break;
			}*/

		//}
    return 0;
}
