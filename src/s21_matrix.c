#include "s21_matrix.h"

#include <stdio.h>
#include <stdlib.h>

/*Все операции (кроме сравнения матриц) должны возвращать результирующий код:
0 - OK
1 - Ошибка, некорректная матрица
2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя
провести вычисления и т.д.)*/

int main() {
  matrix_t mtr = {0};
  matrix_t mtr2 = {0};
  int rows = 2;
  int columns = 3;
  // int columns2 = 3;
  double num = 0.5;
  s21_create_matrix(rows, columns, &mtr);
  // s21_create_matrix(rows, columns2, &mtr2);
  for (int i = 0; i < mtr.rows; i++) {
    for (int j = 0; j < mtr.columns; j++) {
      mtr.matrix[i][j] = j;
    }
  }
  // for (int i = 0; i < mtr2.rows; i++) {
  //   for (int j = 0; j < mtr2.columns; j++) {
  //     mtr2.matrix[i][j] = j;
  //   }
  // }
  printMatrix(mtr);
  printf("\n");
  // printMatrix(mtr2);
  // int res = s21_sub_matrix(&mtr, &mtr2, &mtr);
  int res = s21_mult_number(&mtr, num, &mtr);

  printf("RESULT=%d\n", res);  //(res) ? "SUCCESS" : "FAILURE"
  printMatrix(mtr);
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
  if (A == NULL || B == NULL || A->rows != B->rows || A->columns != B->columns)
    result = FAILURE;
  for (int i = 0; i < A->rows && result; i++) {
    for (int j = 0; j < A->columns && result; j++) {
      if (A->matrix[i][j] != B->matrix[i][j]) result = FAILURE;
    }
  }
  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  error = (A->matrix == NULL || B->matrix == NULL)           ? 1
          : (A->columns != B->columns || A->rows != B->rows) ? 2
                                                             : 0;
  if (!error) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  error = (A->matrix == NULL || B->matrix == NULL)           ? 1
          : (A->columns != B->columns || A->rows != B->rows) ? 2
                                                             : 0;
  if (!error) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = 0;
  error = (A->matrix == NULL) ? 1 : 0;
  if (!error) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return error;
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