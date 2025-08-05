#include<stdio.h>

#define MAX 100


void readMatrix(int mat[MAX][3]) {
    int r, c, t;
    printf("Enter number of rows: ");
    scanf("%d", &r);
    printf("Enter number of columns: ");
    scanf("%d", &c);
    printf("Enter number of non-zero elements: ");
    scanf("%d", &t);

    mat[0][0] = r; 
    mat[0][1] = c; 
    mat[0][2] = t; 
    row, column and value for each non-zero element:\n");
    for (int i = 1; i <= t; i++) {
        scanf("%d %d %d", &mat[i][0], &mat[i][1], &mat[i][2]);
    }
}
void display(int mat[MAX][3]) {
    int t = mat[0][2];
    printf("Row\tCol\tValue\n");
    for (int i = 1; i <= t; i++) {
        printf("%d\t%d\t%d\n", mat[i][0], mat[i][1], mat[i][2]);
    }
    printf("\n");
}

void sparseAdd(int A[MAX][3], int B[MAX][3], int C[MAX][3]) {
    int r1 = A[0][0], c1 = A[0][1], t1 = A[0][2];
    int r2 = B[0][0], c2 = B[0][1], t2 = B[0][2];

    if (r1 != r2 || c1 != c2) {
        printf("Incompatible matrix sizes for addition.\n");
        C[0][2] = 0;
        return;
    }

    C[0][0] = r1;
    C[0][1] = c1;

    int m = 1, n = 1, k = 1;

    while (m <= t1 && n <= t2) {
        if (A[m][0] == B[n][0] && A[m][1] == B[n][1]) {
            int val = A[m][2] + B[n][2];
            if (val != 0) {
                C[k][0] = A[m][0];
                C[k][1] = A[m][1];
                C[k][2] = val;
                k++;
            }
            m++; n++;
        }
        else if (A[m][0] < B[n][0] || (A[m][0] == B[n][0] && A[m][1] < B[n][1])) {
            C[k][0] = A[m][0];
            C[k][1] = A[m][1];
            C[k][2] = A[m][2];
            m++; k++;
        }
        else {
            C[k][0] = B[n][0];
            C[k][1] = B[n][1];
            C[k][2] = B[n][2];
            n++; k++;
        }
    }

    while (m <= t1) {
        C[k][0] = A[m][0];
        C[k][1] = A[m][1];
        C[k][2] = A[m][2];
        m++; k++;
    }

    while (n <= t2) {
        C[k][0] = B[n][0];
        C[k][1] = B[n][1];
        C[k][2] = B[n][2];
        n++; k++;
    }

    C[0][2] = k - 1; 
}


void sparseTranspose(int A[MAX][3], int T[MAX][3]) {
    int rows = A[0][0];
    int cols = A[0][1];
    int t = A[0][2];

    T[0][0] = cols; 
    T[0][1] = rows;  
    T[0][2] = t;

    int k = 1;
    for (int col = 0; col < cols; col++) {
        for (int i = 1; i <= t; i++) {
            if (A[i][1] == col) {
                T[k][0] = A[i][1]; 
                T[k][1] = A[i][0]; 
                T[k][2] = A[i][2]; 
                k++;
            }
        }
    }
}
int main() {
    int A[MAX][3], B[MAX][3], C[MAX][3], T[MAX][3];
    printf("Enter Matrix A:\n");
    readMatrix(A);
    printf("\nEnter Matrix B:\n");
    readMatrix(B);
    printf("\nMatrix A (Triplet Form):\n");
    display(A);
    printf("Matrix A (Full Matrix):\n");
    displayFullMatrix(A);
    printf("Matrix B (Triplet Form):\n");
    display(B);
    printf("Matrix B (Full Matrix):\n");
    displayFullMatrix(B);
    sparseAdd(A, B, C);
    printf("Sum Matrix C (A + B) (Triplet Form):\n");
    display(C);
    printf("Sum Matrix C (Full Matrix):\n");
    displayFullMatrix(C);
    sparseTranspose(C, T);
    printf("Transpose of Sum Matrix C (Triplet Form):\n");
    display(T);
    printf("Transpose of Sum Matrix C (Full Matrix):\n");
    displayFullMatrix(T);
    return 0;
}




