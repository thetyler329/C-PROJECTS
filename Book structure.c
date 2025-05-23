#include <stdio.h>
#include <string.h>

struct Book {
char title[100];
char author[100];
float price;
};

int main() {
struct Book book;
FILE *file;
int choice;

printf("1. Add book\n2. View books\nChoice: ");
scanf("%d", &choice);
getchar();

if (choice == 1) {
printf("Title: ");
fgets(book.title, 100, stdin);
book.title[strcspn(book.title, "\n")] = 0;

printf("Author: ");
fgets(book.author, 100, stdin);
book.author[strcspn(book.author, "\n")] = 0;

printf("Price: ");
scanf("%f", &book.price);

file = fopen("books.dat", "ab");
fwrite(&book, sizeof(book), 1, file);
fclose(file);
}
else if (choice == 2) {
file = fopen("books.dat", "rb");
if (file == NULL) {
printf("No books found\n");
return 1;
}

while (fread(&book, sizeof(book), 1, file)) {
printf("\nTitle: %s\nAuthor: %s\nPrice: $%.2f\n",
book.title, book.author, book.price);
}
fclose(file);
}

return 0;

}