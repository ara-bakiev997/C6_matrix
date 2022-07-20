#include "s21_matrix.h"

#include <stdio.h>
#include <stdlib.h>

/*Все операции (кроме сравнения матриц) должны возвращать результирующий код:
0 - OK
1 - Ошибка, некорректная матрица
2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя
провести вычисления и т.д.)
Если 2 строки или 2 столбца матрицы одинаковые, то детерминант равен 0
*/

int main() {
  matrix_t mtr = {0};
  // matrix_t mtr2 = {0};
  matrix_t mtr3 = {0};
  int rows = 4;
  int columns = 4;
  // int rows2 = 2;
  // int columns2 = 3;
  // double num = 0;
  s21_create_matrix(rows, columns, &mtr);
  // s21_create_matrix(rows2, columns2, &mtr2);
  mtr.matrix[0][0] = 2;
  mtr.matrix[0][1] = 5;
  mtr.matrix[0][2] = 7;
  mtr.matrix[0][3] = 4;

  mtr.matrix[1][0] = 6;
  mtr.matrix[1][1] = 3;
  mtr.matrix[1][2] = 4;
  mtr.matrix[1][3] = 5;

  mtr.matrix[2][0] = 5;
  mtr.matrix[2][1] = -2;
  mtr.matrix[2][2] = -3;
  mtr.matrix[2][3] = 2;

  mtr.matrix[3][0] = 3;
  mtr.matrix[3][1] = 3;
  mtr.matrix[3][2] = 5;
  mtr.matrix[3][3] = 2;
  // mtr2.matrix[0][0] = 1;
  // mtr2.matrix[0][1] = -1;
  // mtr2.matrix[0][2] = 1;
  // mtr2.matrix[1][0] = 2;
  // mtr2.matrix[1][1] = 3;
  // mtr2.matrix[1][2] = 4;

  printMatrix(mtr);
  printf("\n");
  // printMatrix(mtr2);
  // printf("\n");
  // int res = s21_sum_matrix(&mtr, &mtr2, &mtr3);
  // int res = s21_sub_matrix(&mtr, &mtr2, &mtr3);
  // int res = s21_mult_number(&mtr, num, &mtr3);
  // int res = s21_mult_matrix(&mtr, &mtr2, &mtr3);
  // int res = s21_calc_complements(&mtr, &mtr3);
  // s21_calc_complements(&mtr, &mtr2);
  // res = s21_transpose(&mtr2, &mtr3);
  // int res = s21_determinant(&mtr, &num);
  int res = s21_inverse_matrix(&mtr, &mtr3);
  // int res = swapStr(&mtr, 0, 0, &mtr3);

  printf("RESULT=%d\n", res);  //(res) ? "SUCCESS" : "FAILURE"
  printMatrix(mtr3);
  // printf("DETRMINANT=%f\n", num);
  s21_remove_matrix(&mtr);
  // s21_remove_matrix(&mtr3);

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
  error = (A == NULL || B == NULL)                           ? 1
          : (A->columns != B->columns || A->rows != B->rows) ? 2
                                                             : 0;
  if (!error) {
    if (!s21_create_matrix(A->rows, A->columns, result)) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      error = 1;
    }
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  error = (A == NULL || B == NULL)                           ? 1
          : (A->columns != B->columns || A->rows != B->rows) ? 2
                                                             : 0;
  if (!error) {
    if (!s21_create_matrix(A->rows, A->columns, result)) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      error = 1;
    }
  }
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = 0;
  error = (A == NULL) ? 1 : 0;
  if (!error) {
    if (!s21_create_matrix(A->rows, A->columns, result)) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    } else {
      error = 1;
    }
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  error = (A == NULL || B == NULL) ? 1 : (A->columns != B->rows) ? 2 : 0;
  if (!error) {
    if (!s21_create_matrix(A->rows, B->columns, result)) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int x = 0; x < A->columns; x++) {
            result->matrix[i][j] += A->matrix[i][x] * B->matrix[x][j];
          }
        }
      }
    } else {
      error = 1;
    }
  }
  return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = 0;
  error = (A == NULL || s21_create_matrix(A->columns, A->rows, result)) ? 1 : 0;
  if (!error) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return error;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 0;
  error = (A == NULL) ? 1 : (A->rows != A->columns) ? 2 : 0;
  if (!error) {
    matrix_t tmp;
    double sign = 1;
    s21_create_matrix(A->rows, A->columns, result);
    // s21_create_matrix(A->rows, A->columns, tmp);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
        GetMiniMatr(A, i, j, &tmp);
        s21_determinant(&tmp, &result->matrix[i][j]);
        s21_remove_matrix(&tmp);
        if ((j + i) % 2 == 0) sign = -sign;
        result->matrix[i][j] = sign * result->matrix[i][j];
      }
    }
  }
  return error;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = 0, check = 0;
  error = (A == NULL || result == NULL) ? 1 : (A->rows != A->columns) ? 2 : 0;
  double quotient = 0, sign = 1;
  if (!error) {
    *result = 1;
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      matrix_t tmp;
      s21_create_matrix(A->rows, A->columns, &tmp);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          tmp.matrix[i][j] = A->matrix[i][j];
        }
      }
      for (int i = 0; i < tmp.rows; i++) {
        if (tmp.matrix[i][i] == 0) {
          check = swapStr(&tmp, i, i, &tmp);
          sign = -sign;
        }
        if (!check) {
          for (int j = i + 1; j < tmp.rows; j++) {
            quotient = tmp.matrix[j][i] / tmp.matrix[i][i];
            for (int x = i; x < tmp.columns; x++) {
              double kkk = tmp.matrix[j][x] - quotient * tmp.matrix[i][x];
              tmp.matrix[j][x] = kkk;
            }
          }
          *result *= tmp.matrix[i][i];
        } else {
          *result = 0;
          break;
        }
      }
      if (!check) *result *= sign;
      s21_remove_matrix(&tmp);
    }
  }
  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;
  double determinant;
  error = (A == NULL) ? 1 : (A->rows != A->columns) ? 2 : 0;
  if (!error) {
    s21_determinant(A, &determinant);
    if (!determinant) {
      error = 2;
    } else {
      matrix_t tmp;
      // matrix_t tmp1;
      // printf("%lf\n", determinant);
      s21_calc_complements(A, &tmp);
      s21_transpose(&tmp, result);
      s21_mult_number(result, (1 / determinant), &tmp);
      *result = tmp;
    }
  }

  return error;
}

/*__________________ANOTHER_FUNCTIONS___________________*/
void GetMiniMatr(matrix_t *A, int x, int y, matrix_t *result) {
  int di = 0, dj;
  double lll = 0;
  for (int i = 0; i < (A->rows - 1); i++) {  // проверка индекса строки
    if (i == x) di = 1;
    dj = 0;
    for (int j = 0; j < (A->rows - 1); j++) {  // проверка индекса столбца
      if (j == y) dj = 1;
      lll = A->matrix[i + di][j + dj];
      result->matrix[i][j] = lll;
    }
  }
}

int swapStr(matrix_t *A, int x, int y, matrix_t *result) {
  int error = 0;
  int i = 0;
  *result = *A;  //   внимание
  for (i = x; i < A->rows; i++) {
    if (A->matrix[i][y] != 0) {
      error = 0;
      break;
    } else {
      error = 1;
    }
  }
  if (!error) {
    double tmp = 0;
    for (int j = 0; j < A->columns; j++) {
      tmp = A->matrix[x][j];
      A->matrix[x][j] = result->matrix[i][j];
      result->matrix[i][j] = tmp;
    }
  }
  return error;
}

/*____________________PRINT_FUNCTIONS___________________*/
void printMatrix(matrix_t src) {
  for (int i = 0; i < src.rows; i++) {
    for (int j = 0; j < src.columns; j++) {
      printf("%lf ", src.matrix[i][j]);
    }
    printf("\n");
  }
}

// int s21_determinant(matrix_t *A, double *result) {
//   int error = 0;
//   error = (A->matrix == NULL) ? 1 : (A->rows != A->columns) ? 2 : 0;
//   if (!error) {
//     *result = 0;
//     if (A->rows == 1) {
//       *result = A->matrix[0][0];
//     } else if (A->rows == 2) {
//       *result =
//           A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] *
//           A->matrix[1][0];
//     } else {
//       matrix_t tmpMtr = {0};
//       int sign = 1;
//       double tmp = 0;
//       for (int j = 0; j < A->columns; j++) {
//         s21_calc_complements(A, &tmpMtr);
//         s21_determinant(&tmpMtr, &tmp);
//         *result += sign * A->matrix[0][j] * tmp;
//         sign = -sign;
//         s21_remove_matrix(&tmpMtr);
//       }
//     }
//   }
//   return error;
// }