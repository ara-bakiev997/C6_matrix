#include "s21_matrix.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
  matrix_t mtr = {0};
  matrix_t mtr2 = {0};
  int rows = 5;
  int columns = 5;
  int columns2 = 4;
  s21_create_matrix(rows, columns, &mtr);
  s21_create_matrix(rows, columns2, &mtr2);
  for (int i = 0; i < mtr.rows; i++) {
    for (int j = 0; j < mtr.columns; j++) {
      mtr.matrix[i][j] = j;
    }
  }
  for (int i = 0; i < mtr2.rows; i++) {
    for (int j = 0; j < mtr2.columns; j++) {
      mtr2.matrix[i][j] = j;
    }
  }
  int res = s21_eq_matrix(&mtr, &mtr2);
  printf("RESULT=%s\n", (res) ? "SUCCESS" : "FAILURE");
  // printMatrix(mtr);
  s21_remove_matrix(&mtr);
  s21_remove_matrix(&mtr2);

  return 0;
}

/*__________________MAIN_FUNCTIONS___________________*/
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;
  result->rows = rows;
  result->columns = columns;
  double *lenStr = NULL;
  result->matrix = NULL;
  result->matrix = calloc(rows, sizeof(double *) + columns * sizeof(double));
  if (result->matrix == NULL) error = 1;
  if (!error) {
    lenStr = (double *)(result->matrix + rows);
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = lenStr + columns * i;
    }
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  free(A->matrix);
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (A->rows != B->rows || A->columns != B->columns) result = FAILURE;
  for (int i = 0; i < A->rows && result; i++) {
    for (int j = 0; j < A->columns && result; j++) {
      if (A->matrix[i][j] != B->matrix[i][j]) result = FAILURE;
    }
  }
  return result;
}

/*__________________ANOTHER_FUNCTIONS___________________*/
void printMatrix(matrix_t src) {
  for (int i = 0; i < src.rows; i++) {
    for (int j = 0; j < src.columns; j++) {
      printf("%lf ", src.matrix[i][j]);
    }
    printf("\n");
  }
}

// int s21_create_matrix_malloc(int rows, int columns, matrix_t *result) {
//   int error = 0;
//   result->rows = rows;
//   result->columns = columns;
//   double *lenStr = NULL;
//   result->matrix = NULL;
//   result->matrix =
//       malloc(rows * sizeof(double *) + rows * columns * sizeof(double));
//   if (result->matrix == NULL) error = 1;
//   if (!error) {
//     lenStr = (double *)(result->matrix + rows);
//     for (int i = 0; i < rows; i++) {
//       result->matrix[i] = lenStr + columns * i;
//     }
//   }
//   return error;
// }