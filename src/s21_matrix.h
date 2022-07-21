#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

/*__________________MAIN_FUNCTIONS___________________*/
int s21_create_matrix(int rows, int columns, matrix_t *result);  // leaks isn't
void s21_remove_matrix(matrix_t *A);                             // leaks isn't
int s21_eq_matrix(matrix_t *A, matrix_t *B);                     // leaks isn't
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);  // leaks isn't
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

/*__________________ANOTHER_FUNCTIONS___________________*/
void GetMiniMatr(matrix_t *A, int x, int y, matrix_t *result);
int swapStr(matrix_t *A, int x, int y, matrix_t *result);

/*____________________PRINT_FUNCTIONS___________________*/
void printMatrix(matrix_t src);

#endif  // SRC_S21_MATRIX_H_
