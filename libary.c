#include <stdio.h>
#include <stdlib.h>

#define TOTAL_BOOKS 5

// Global array to store book availability (1 = available, 0 = borrowed)
int availableBooks[TOTAL_BOOKS] = {1, 1, 1, 1, 1};  // Initially all books are available

// Function prototypes
int checkAvailability(int bookId);
int borrowBook(int bookId);
void displayAvailability(void);
void displayMenu(void);
int validateBookId(int bookId);

// Check if a book is available
int checkAvailability(int bookId) {
    if (!validateBookId(bookId)) {
        return -1;  // Invalid book ID
    }
    return availableBooks[bookId - 1];
}

// Borrow a book
int borrowBook(int bookId) {
    if (!validateBookId(bookId)) {
        return 0;  // Failed to borrow
    }
    
    if (availableBooks[bookId - 1] == 0) {
        return 0;  // Book already borrowed
    }
    
    availableBooks[bookId - 1] = 0;  // Mark as borrowed
    return 1;  // Successfully borrowed
}

// Display current availability of all books
void displayAvailability(void) {
    printf("\nCurrent Book Availability:\n");
    printf("-------------------------\n");
    for (int i = 0; i < TOTAL_BOOKS; i++) {
        printf("Book ID %d: %s\n", 
               i + 1, 
               availableBooks[i] ? "Available" : "Borrowed");
    }
    printf("-------------------------\n");
}

// Validate book ID
int validateBookId(int bookId) {
    return (bookId >= 1 && bookId <= TOTAL_BOOKS);
}

// Display menu options
void displayMenu(void) {
    printf("\nLibrary Management System\n");
    printf("1. Check book availability\n");
    printf("2. Borrow a book\n");
    printf("3. Display all books\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice, bookId;
    
    while (1) {
        displayMenu();
        
        // Get user choice
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');  // Clear input buffer
            continue;
        }
        
        switch (choice) {
            case 1:  // Check availability
                printf("Enter book ID (1-%d): ", TOTAL_BOOKS);
                scanf("%d", &bookId);
                
                int available = checkAvailability(bookId);
                if (available == -1) {
                    printf("Invalid book ID!\n");
                } else {
                    printf("Book %d is %s\n", 
                           bookId, 
                           available ? "available" : "not available");
                }
                break;
                
            case 2:  // Borrow book
                printf("Enter book ID to borrow (1-%d): ", TOTAL_BOOKS);
                scanf("%d", &bookId);
                
                if (borrowBook(bookId)) {
                    printf("Successfully borrowed book %d\n", bookId);
                } else {
                    printf("Failed to borrow book %d (either invalid ID or already borrowed)\n", bookId);
                }
                break;
                
            case 3:  // Display availability
                displayAvailability();
                break;
                
            case 4:  // Exit
                printf("Thank you for using the Library Management System!\n");
                return 0;
                
            default:
                printf("Invalid choice! Please select 1-4\n");
        }
    }
    
    return 0;
}3