#include "s21_matrix.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
  matrix_t mtr = {0};
  int rows = 5;
  int columns = 5;
  s21_create_matrix(rows, columns, &mtr);
  for (int i = 0; i < mtr.rows; i++) {
    for (int j = 0; j < mtr.columns; j++) {
      mtr.matrix[i][j] = j;
    }
  }
  printMatrix(mtr);
  s21_remove_matrix(&mtr);

  return 0;
}

/*__________________MAIN_FUNCTIONS___________________*/
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;
  result->matrix = (double **)malloc(rows * sizeof(double *));
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)malloc(columns * sizeof(double));
  }
  result->rows = rows;
  result->columns = columns;
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  A->rows = 0;
  A->columns = 0;
}

void printMatrix(matrix_t src) {
  for (int i = 0; i < src.rows; i++) {
    for (int j = 0; j < src.columns; j++) {
      printf("%f ", src.matrix[i][j]);
    }
    printf("\n");
  }
}
