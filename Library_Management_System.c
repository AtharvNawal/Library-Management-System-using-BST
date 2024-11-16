#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int bookID;
    char title[100];
    char author[100];
    int year;
    int isIssued;
    char issuedTo[100];
    char returnDate[20];
    struct Book *left, *right;
};

void saveBooksToFile(struct Book* root);

struct Book* createBook(int bookID, char title[], char author[], int year) {
    struct Book* newBook = (struct Book*)malloc(sizeof(struct Book));
    newBook->bookID = bookID;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->year = year;
    newBook->isIssued = 0;
    strcpy(newBook->issuedTo, "None");
    strcpy(newBook->returnDate, "None");
    newBook->left = newBook->right = NULL;
    return newBook;
}

struct Book* insertBookBST(struct Book* root, struct Book* newBook) {
    if (root == NULL) {
        return newBook;
    }
    if (newBook->bookID < root->bookID) {
        root->left = insertBookBST(root->left, newBook);
    } else if (newBook->bookID > root->bookID) {
        root->right = insertBookBST(root->right, newBook);
    }
    return root;
}

struct Book* insertBook(struct Book* root, int bookID, char title[], char author[], int year) {
    struct Book* newBook = createBook(bookID, title, author, year);
    root = insertBookBST(root, newBook);
    saveBooksToFile(root);
    return root;
}

struct Book* searchBookBST(struct Book* root, int bookID) {
    if (root == NULL || root->bookID == bookID) {
        return root;
    }
    if (bookID < root->bookID) {
        return searchBookBST(root->left, bookID);
    }
    return searchBookBST(root->right, bookID);
}

struct Book* deleteBookBST(struct Book* root, int bookID) {
    if (root == NULL) {
        return root;
    }
    if (bookID < root->bookID) {
        root->left = deleteBookBST(root->left, bookID);
    } else if (bookID > root->bookID) {
        root->right = deleteBookBST(root->right, bookID);
    } else {
        if (root->left == NULL) {
            struct Book* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Book* temp = root->left;
            free(root);
            return temp;
        }
        struct Book* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        root->bookID = temp->bookID;
        strcpy(root->title, temp->title);
        strcpy(root->author, temp->author);
        root->year = temp->year;
        root->right = deleteBookBST(root->right, temp->bookID);
    }
    saveBooksToFile(root);
    return root;
}

struct Book* deleteBook(struct Book* root, int bookID) {
    root = deleteBookBST(root, bookID);
    return root;
}

void displayBooks(struct Book* root) {
    if (root == NULL) {
        printf("No books available in the library.\n");
        return;
    }

    printf("\n%-5s %-30s %-25s %-6s %-15s %-20s\n",
           "ID", "Title", "Author", "Year", "Issued", "Return Date");
    printf("-------------------------------------------------------------------------------------------\n");

    void displayBookDetails(struct Book* node) {
        if (node != NULL) {
            displayBookDetails(node->left);
            printf("%-5d %-30s %-25s %-6d %-15s %-20s\n",
                   node->bookID,
                   node->title,
                   node->author,
                   node->year,
                   node->isIssued ? node->issuedTo : "Available",
                   node->isIssued ? node->returnDate : "N/A");
            displayBookDetails(node->right);
        }
    }

    displayBookDetails(root);
}

void issueBook(struct Book* root, int bookID, char studentName[], char returnDate[]) {
    struct Book* book = searchBookBST(root, bookID);
    if (book == NULL) {
        printf("Book with ID %d not found.\n", bookID);
    } else if (book->isIssued == 1) {
        printf("Book with ID %d is already issued to %s.\n", bookID, book->issuedTo);
    } else {
        book->isIssued = 1;
        strcpy(book->issuedTo, studentName);
        strcpy(book->returnDate, returnDate);
        printf("Book issued successfully to %s. Return date is %s.\n", studentName, returnDate);
        saveBooksToFile(root);
    }
}

void returnBook(struct Book* root, int bookID) {
    struct Book* book = searchBookBST(root, bookID);
    if (book == NULL) {
        printf("Book with ID %d not found.\n", bookID);
    } else if (book->isIssued == 0) {
        printf("Book with ID %d is not issued to anyone.\n", bookID);
    } else {
        book->isIssued = 0;
        strcpy(book->issuedTo, "None");
        strcpy(book->returnDate, "None");
        printf("Book with ID %d has been returned.\n", bookID);
        saveBooksToFile(root);
    }
}

struct Book* preloadBooks() {
    struct Book* root = NULL;
    FILE *file = fopen("booksdata.txt", "r");
    if (file == NULL) {
        printf("Could not open file for reading. Preloading default books.\n");
        root = insertBook(root, 101, "C Programming", "Dennis Ritchie", 1978);
        root = insertBook(root, 102, "Data Structures", "Mark Allen Weiss", 1995);
        root = insertBook(root, 103, "Operating Systems", "Andrew S. Tanenbaum", 1992);
        root = insertBook(root, 104, "Database Systems", "Raghu Ramakrishnan", 2002);
        root = insertBook(root, 105, "Computer Networks", "James Kurose", 2016);
    } else {
        int id, year, issued;
        char title[100], author[100], issuedTo[100], returnDate[20];
        while (fscanf(file, "%d,%99[^,],%99[^,],%d,%d,%99[^,],%19s\n", &id, title, author, &year, &issued, issuedTo, returnDate) == 7) {
            struct Book* newBook = createBook(id, title, author, year);
            newBook->isIssued = issued;
            strcpy(newBook->issuedTo, issuedTo);
            strcpy(newBook->returnDate, returnDate);
            root = insertBookBST(root, newBook);
        }
        fclose(file);
    }
    return root;
}

void saveBooksToFile(struct Book* root) {
    FILE *file = fopen("booksdata.txt", "w");
    if (file == NULL) {
        printf("Could not open file for writing.\n");
        return;
    }
    void writeBooksToFile(struct Book* node) {
        if (node != NULL) {
            fprintf(file, "%d,%s,%s,%d,%d,%s,%s\n", node->bookID, node->title, node->author, node->year, node->isIssued, node->issuedTo, node->returnDate);
            writeBooksToFile(node->left);
            writeBooksToFile(node->right);
        }
    }
    writeBooksToFile(root);
    fclose(file);
}

int validateReturnDate(char returnDate[]) {
    int day, month, year;
    sscanf(returnDate, "%d-%d-%d", &day, &month, &year);
    if (day < 1 || day > 31) {
        printf("Error: Day must be between 1 and 31.\n");
        return 0;
    }
    if (month < 1 || month > 12) {
        printf("Error: Month must be between 1 and 12.\n");
        return 0;
    }
    if (year != 2024) {
        printf("Error: Returning year should be the present year.\n");
        return 0;
    }
    return 1;
}

int main() {
    struct Book* root = preloadBooks();
    int choice, id, year;
    char title[100], author[100];
    char studentName[100], returnDate[20];
    do {
        printf("\nLibrary Management System\n");
        printf("1. Display All Books\n2. Add Book\n3. Delete Book\n4. Issue Book\n5. Return Book\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Displaying all books:\n");
                displayBooks(root);
                break;
            case 2:
                printf("Enter Book ID: ");
                scanf("%d", &id);
                printf("Enter Book Title: ");
                scanf(" %[^\n]%*c", title);
                printf("Enter Book Author: ");
                scanf(" %[^\n]%*c", author);
                printf("Enter Publication Year: ");
                scanf("%d", &year);
                if (year > 2024) {
                    printf("Error: Enter a Valid Year.\n");
                } else {
                    root = insertBook(root, id, title, author, year);
                    printf("Book added successfully!\n");
                }
                break;
            case 3:
                printf("Enter Book ID to delete: ");
                scanf("%d", &id);
                root = deleteBook(root, id);
                printf("Book deleted successfully!\n");
                break;
            case 4:
                printf("Enter Book ID to issue: ");
                scanf("%d", &id);
                printf("Enter Student Name: ");
                scanf(" %[^\n]%*c", studentName);
                printf("Enter Return Date (DD-MM-YYYY): ");
                scanf("%s", returnDate);
                if (validateReturnDate(returnDate)) {
                    issueBook(root, id, studentName, returnDate);
                }
                break;
            case 5:
                printf("Enter Book ID to return: ");
                scanf("%d", &id);
                returnBook(root, id);
                break;
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    return 0;
}
