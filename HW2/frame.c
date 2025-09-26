#include <stdio.h>
#include <stdlib.h>

//============================ Function prototypes =====================================

int** allocate2D(int rows, int cols);
void free2D(int** arr, int rows);
int** readGradesFromFile(const char* filename, int* s, int* c);
void writeAveragesToFile(const char* filename, int** arr, int s, int c);

//=============================== main function ========================================

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <grades_file>\n", argv[0]);
        return 1;
    }

    int S, C;
    int** grades = readGradesFromFile(argv[1], &S, &C);
    writeAveragesToFile("output.txt", grades, S, C);

    free2D(grades, S);
    return 0;
}

//=========================== Allocate 2D array dynamically ============================

/*
@brief: dynamically allocates a matrix 
@param: int rows: number of rows for matrix
@param: int cols: number of cols for matrix
@return: int** for allocates matrix
*/
int** allocate2D(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++){
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            matrix[i][j] = 0; //initializing to 0
        }
    }
    return matrix;
}

//================================ Free 2D array ========================================

/*
@brief: frees the memory allocated for the matrix
@param: int** arr: pointer to matrix to free
@param: int rows: number of rows in matrix
@effect: matrix memory is freed
@return: none
*/
void free2D(int** arr, int rows) {
    for(int i = 0; i < rows; i++){
        free(arr[i]);
    }
    free(arr);
}

//=========================== Read grades from file =====================================

/*
@brief: function builds and fills in matrix from values in the input file
@param: const char* filename: const ptr to name of the file to read from
@param: int* s: ptr to value for number of rows
@param: int* c: ptr to value of num of cols
@effect: dynamically allocates memory for 2D array
@return: ptr to new 2D Array
*/
int** readGradesFromFile(const char* filename, int* s, int* c) {
    int** matrix;
    FILE* fp = fopen(filename, "r");
    if(fp != NULL){
        if(fscanf(fp, "%d %d", s, c) != 2){
            printf("ERROR READING FIRST LINE!");
        }
        matrix = allocate2D((*s),(*c));
        int num;
        int i = 0, j = 0;
        while(fscanf(fp, "%d", &num) == 1 && i < (*s)){
            if(i < (*s) && j < (*c)){
                matrix[i][j] = num;
                j++;
                if(j == (*c)){
                    j = 0;
                    i++;
                }
            }
        }
    }
    else{
        printf("ERROR OPENING FILE!!");
    }
    fclose(fp);
    return matrix;
}

//========================= Write averages to output file ==============================

/*
@brief: computes averages for courses and students and writes them to file
@param: const char* filename: ptr to name of file to write to
@param: int** arr: ptr to 2D array that holds score values
@param: int s: num of rows
@param: int c: num of cols
@effect: writes to file
@return: none
*/
void writeAveragesToFile(const char* filename, int** arr, int s, int c) {
    FILE* fp = fopen(filename, "w");
    if(fp == NULL){
        printf("ERROR OPENING FILE TO WRITE!!");
        return;
    }
    //array to assist computing course sums
    int courseSums[c];
    for(int i = 0; i < c; i++){
        courseSums[i] = 0; //initializing to 0
    }
    double avg;
    int sum = 0;
    //computing averages
    for(int i = 0; i < s; i++){
        for(int j = 0; j < c; j++){
            sum += arr[i][j];
            courseSums[j] += arr[i][j];
        }
    avg = (double)sum / c;
    sum = 0;
    fprintf(fp, "%.2f ", avg); //writing student averages
    }
    fprintf(fp, "\n");
    for(int i = 0; i < c; i++){
        avg = (double)courseSums[i] / s;
        fprintf(fp, "%.2f ", avg); //writing course averages
    }
    fprintf(fp, "\n");
    fclose(fp);
}
