#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a book
struct Book {
    char title[100];
    char author[50];
    int id;
    int availability;
    struct Book* next;
};

// Structure for a student
struct Student {
    char name[50];
    char email[50];
    int registrationNumber;
    char borrowedBook[100];
    struct Student* next;
};

// Global variables
struct Book* bookList = NULL;
struct Student* studentList = NULL;

// Function prototypes
void displayMenu();
void addBook();
void displayLibrary();
void registerStudent();
void issueBook();
void returnBook();
void displayStudentDetails();

    printf("\n\n");
    printf("\t\t\t     ****************************************\n");
    printf("\t\t\t     *                                      *\n");
    printf("\t\t\t     *                                      *\n");
    printf("\t\t\t     *     ----------------------------     *\n");
    printf("\t\t\t     *      WELCOME TO STUDENT LIBRARY      *\n");
    printf("\t\t\t     *     ----------------------------     *\n");
    printf("\t\t\t     *                                      *\n");
    printf("\t\t\t     *                                      *\n");
    printf("\t\t\t     ****************************************\n");
    printf("\n\n");
    printf("\t\t\t     ****************************************\n");
    printf("\t\t\t     *                                      *\n");
    printf("\t\t\t     *       ------------------------       *\n");
    printf("\t\t\t     *           STUDENT LIBRARY            *\n");
    printf("\t\t\t     *       ------------------------       *\n");
    printf("\t\t\t     *                                      *\n");
    printf("\t\t\t     *                                      *\n");
    printf("\t\t\t     *       SRMIST,KTR CHENNAI ,India      *\n");
    printf("\t\t\t     *     Email: studentlib@gmail.com      *\n");
    printf("\t\t\t     *     OWNERS : 441,444,445             *\n");
    printf("\t\t\t     *                                      *\n");
    printf("\t\t\t     ****************************************\n");
    printf("\n\n\t\t\t             Press any key to continue: ");




int main() {
    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayLibrary();
                break;
            case 3:
                registerStudent();
                break;
            case 4:
                issueBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                displayStudentDetails();
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);

    return 0;
}

void displayMenu() {
    printf("\n************ Library Management System ************\n");
    printf("1. Add Book\n");
    printf("2. Display Library\n");
    printf("3. Register Student\n");
    printf("4. Issue Book\n");
    printf("5. Return Book\n");
    printf("6. Display Student Details\n");
    printf("7. Exit\n");
    printf("***************************************************\n");
    printf("Enter your choice: ");
}

void addBook() {
    struct Book* newBook = (struct Book*)malloc(sizeof(struct Book));

    printf("\nEnter Book Title: ");
    scanf(" %[^\n]s", newBook->title);
    printf("Enter Author Name: ");
    scanf(" %[^\n]s", newBook->author);
    printf("Enter Book ID: ");
    scanf("%d", &(newBook->id));
    printf("Enter Availability (0 for not available, 1 for available): ");
    scanf("%d", &(newBook->availability));

    newBook->next = bookList;
    bookList = newBook;

    printf("\nBook added successfully!\n");
}

void displayLibrary() {
    struct Book* current = bookList;

    if (current == NULL) {
        printf("\nLibrary is empty!\n");
    } else {
        printf("\n************ Library ************\n");
        while (current != NULL) {
            printf("Title: %s\n", current->title);
            printf("Author: %s\n", current->author);
            printf("ID: %d\n", current->id);
            printf("Availability: %s\n", (current->availability == 1) ? "Available" : "Not Available");
            printf("--------------------------------\n");
            current = current->next;
        }
    }
}

void registerStudent() {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));

    printf("\nEnter Student Name: ");
    scanf(" %[^\n]s", newStudent->name);
    printf("Enter Email: ");
    scanf(" %[^\n]s", newStudent->email);
    printf("Enter Registration Number: ");
    scanf("%d", &(newStudent->registrationNumber));
    strcpy(newStudent->borrowedBook, "None");

    newStudent->next = studentList;
    studentList = newStudent;

    printf("\nStudent registered successfully!\n");
}

void issueBook() {
    int bookID, regNumber;
    struct Book* current = bookList;
    struct Student* currentStudent = studentList;

    printf("\nEnter Book ID: ");
    scanf("%d", &bookID);

    while (current != NULL && current->id != bookID) {
        current = current->next;
    }

    if (current == NULL) {
        printf("\nBook not found!\n");
        return;
    }

    printf("\nEnter Student Registration Number: ");
    scanf("%d", &regNumber);

    while (currentStudent != NULL && currentStudent->registrationNumber != regNumber) {
        currentStudent = currentStudent->next;
    }

    if (currentStudent == NULL) {
        printf("\nStudent not found!\n");
        return;
    }

    if (current->availability == 0) {
        printf("\nBook is not available for issuance.\n");
    } else {
        current->availability = 0;
        strcpy(currentStudent->borrowedBook, current->title);
        printf("\nBook '%s' issued to %s.\n", current->title, currentStudent->name);
    }
}

void returnBook() {
    int regNumber;
    struct Book* current = bookList;
    struct Student* currentStudent = studentList;

    printf("\nEnter Student Registration Number: ");
    scanf("%d", &regNumber);

    while (currentStudent != NULL && currentStudent->registrationNumber != regNumber) {
        currentStudent = currentStudent->next;
    }

    if (currentStudent == NULL) {
        printf("\nStudent not found!\n");
        return;
    }

    if (strcmp(currentStudent->borrowedBook, "None") == 0) {
        printf("\nNo books borrowed by %s.\n", currentStudent->name);
        return;
    }

    while (current != NULL && strcmp(current->title, currentStudent->borrowedBook) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("\nBook not found!\n");
        return;
    }

    current->availability = 1;
    strcpy(currentStudent->borrowedBook, "None");

    printf("\nBook '%s' returned by %s.\n", current->title, currentStudent->name);
}

void displayStudentDetails() {
    struct Student* current = studentList;

    if (current == NULL) {
        printf("\nNo students registered!\n");
    } else {
        printf("\n************ Student Details ************\n");
        while (current != NULL) {
            printf("Name: %s\n", current->name);
            printf("Email: %s\n", current->email);
            printf("Registration Number: %d\n", current->registrationNumber);
            printf("Borrowed Book: %s\n", current->borrowedBook);
            printf("---------------------------------------\n");
            current = current->next;
        }
    }
}
