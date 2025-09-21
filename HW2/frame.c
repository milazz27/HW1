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

int** allocate2D(int rows, int cols) {
    /* 
       This is the function where you need to allocate a 
       2d array and return its address. Make sure that 
       all error handlings are done where needed. You need
       to have an array of pointers in which each element
       points to one row of the matrix. You may use
       malloc() library function for memory allocation. 
    */

    int** matrix = (int**)malloc(rows * sizeof(int*));

    for(int i = 0; i < rows; i++){
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            matrix[i][j] = 0;
        }
    }

    return matrix;
}

//================================ Free 2D array ========================================

void free2D(int** arr, int rows) {

    /*  
        This function frees the allocated memory. 
        Freeing a memory allocation is usually the reverse
        of allocation. 
    */

    for(int i = 0; i < rows; i++){
        free(arr[i]);
    }

    free(arr);
}

//=========================== Read grades from file =====================================

int** readGradesFromFile(const char* filename, int* s, int* c) {
    
    /* 
       This is the part that your program needs to handle files.
       The program needs to read from the file specified
       by the filename and return a pointer to the matrix
       of the numbers read from that file. Within this function, 
       your program needs to call allocate2D() function to allocate
       the 2d array for storing the numbers. Do not forget to do error
       handling when opening the file. The program also needs to close 
       the file when needed. Argumnets s and c are referenced meaning that
       the calling function will use them. Therefore, you need to read 
       those values from the file and put those values in s and c. But
       remember s and c are pointers to integers (not integers themselves). 
    */
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

void writeAveragesToFile(const char* filename, int** arr, int s, int c) {

    /* 
       This function uses array arr and computes the average for each student
       and writes each student average in the same line of the file specified
       by filename. Then, it computes the average of each course and writes
       each course average in the same line (the line after the student 
       averages). Make sure to do error handling. compute bothaverages as 
       doubles and write the average with 2 decimal points in the file. 
    */
    double avg;
    int sum = 0;
    for(int i = 0; i < s; i++){
        for(int j = 0; j < c; j++){
            sum += arr[i][j];
        }
    avg = (double)sum / c;
    sum = 0;
    printf("%.2f  ", avg);
    }
}