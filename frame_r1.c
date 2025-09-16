#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =============================== Data Structure ======================================
typedef struct {
    int id;
    char title[100];
    char author[100];
    int year;
} Book;

Book *library = NULL;   // dynamic array of books
int bookCount = 0;      // how many books exist

// ============================= Function Prototypes ==================================
void addBook(char*);
void searchBook(char*);
void displayBookEntry(int ind);
void displayBooks();
void deleteBook(char*);

//================================= Main Function =====================================
int main() {
    int option;
    char line[300];

    while (fgets(line, sizeof(line), stdin)) {
        if (sscanf(line, "%d", &option)!=1) {
            printf("Error in reading the option in main()\n");
            return -1;
        }
        
        switch(option) {
            case 1: addBook(line); break;
            case 2: searchBook(line); break;
            case 3: displayBooks(); break;
            case 4: deleteBook(line); break;
            default: printf("Invalid option!\n");
        }
    }

    free(library); // free allocated memory before exit
    return 0;
}

// ============================ Function Implementations ==============================


/* 
Your functions need to skip the first number in line which is the option number. 
To do so, you can put %*d so that sscanf skips that value. sscanf
Does not require any container or receiver for %*d. 

Your function always needs to check for errors in sscanf. If the number of expected 
values to be written into variables is not equal to the returned value
by sscanf, there is an error and your function should return after 
displaying a proper error message. 

For how to format your output, please refere to output.dat file. 
It shows how the propose output is generated based on input file inFile.dat. 
*/


// ---------------------------- Add a new book ----------------------------------------
/*
@brief: adds book object to library array
@param: char* line: the string to be parsed to create a Book object
@effects: adds a book to library and resizes the array to accomodate for it
@return: none
*/
void addBook(char *line) {
    int bookId, bookYear;
    char bookTitle[100];
    char bookAuthor[100];
    if(sscanf(line, "%*d %d \"%99[^\"]\" \"%99[^\"]\" %d", &bookId, bookTitle, bookAuthor, &bookYear) != 4) {
        printf("Error in input for addBook()!!");
        return;
    }
    Book* newBook = realloc(library, (bookCount + 1 )*(sizeof(Book)));
    if(newBook != NULL){
        library = newBook;
        library[bookCount].id = bookId;
        library[bookCount].year = bookYear;
        strcpy(library[bookCount].title, bookTitle);
        strcpy(library[bookCount].author, bookAuthor);
        bookCount++;
        printf("Book added!\n");
    }
}

// --------------------------- Search for a book ------------------------------------

/*
@brief: searches for book title in library by a search phrase
@param: char* line: string where search phrase is extracted from
@return: none
*/
void searchBook(char *line) {
    char searchPhrase[100];
    if(sscanf(line, "%*d \"%99[^\"]\"", searchPhrase) != 1){
        printf("Scan Error in searchPhrase()\n");
        return;
    }
    else{
        int resultNum = 1;
        for(int i = 0; i < bookCount; i++){
            if(strcasestr(library[i].title, searchPhrase) != NULL){
                printf("Found: ");
                displayBookEntry(i);
                resultNum++;
            }
        }
        if(resultNum == 1){
            printf("No book with title \"%s\" found.\n", searchPhrase);
        }
    }
}

// --------------------------- Display all books -----------------------------------

/*
@brief: helper function to display a book entry with pipes
@param: int ind: index of the book in library that should be displayed
@return: none
*/
void displayBookEntry(int ind){
    if(ind <= bookCount){
        printf("%d | %s | %s | %d\n", library[ind].id, library[ind].title, library[ind].author, library[ind].year);
    }
}

/*
@brief: function to display the full content of the library
@param: none
@return: none
*/
void displayBooks() {
    //Check if there are currently books in library before print
    if(bookCount > 0){
        for(int i = 1; i <= bookCount; i++){
            int ind = i - 1;
            printf("%d. ", i);
            displayBookEntry(ind);
        }
    }
    else{
        printf("No books in library.\n");
    }
}

// -------------------------- Delete book by ID -----------------------------------

/*
@brief: helper function to find the index of a book by its ID
@param: int BookId: the book ID to search for
@return: int: index of book found or -1 if no such entry exists
*/
int findBookIndex(int bookId){
    for(int i = 0; i < bookCount; i++){
        if(library[i].id == bookId){
            return i;
        }
    }
    return -1;
}

/*
@breif: function to delete a book from the library
@param: char* line: string from which to extract the ID of the book to delete
@effects: resizes library and shifts indices if book is successfully deleted
@return: none
*/
void deleteBook(char *line) {
    int removeId;
    if((sscanf(line, "%*d %d", &removeId) != 1)){
        printf("Error: scan error in deleteBook()!\n");
        return;
    }
    else{
        int index = findBookIndex(removeId);
        if(index != -1){
            for(int i = index; i < (bookCount - 1); i++){
                library[i] = library[i + 1];
            }
            printf("Book with ID %d deleted!\n", removeId);
            bookCount--;
            if(bookCount > 0){
                Book *tmp = realloc(library, (bookCount) * sizeof(Book));
                if(tmp != NULL){
                    library = tmp;
                }
            } 
        }
        else{
            printf("Book with ID %d not found to delete!\n", removeId);
        }
    }
}