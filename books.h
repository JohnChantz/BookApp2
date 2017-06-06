#ifndef BOOKS_H_INCLUDED
#define BOOKS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRING 100
#define MAXREVIEWS 10

enum genres {
    fiction, scientific, politics
};

typedef struct bookR bookR;
typedef struct bookR *book;

struct bookR {
    char author[MAXSTRING];
    char title[MAXSTRING];
    enum genres genre;
    int id;
    char reviews[MAXREVIEWS][MAXSTRING];
};

typedef struct bookList bookList;
typedef bookList *list;

struct bookList {
    book x;
    list nextBk;
};

// απαραίτητες συναρτήσεις !
// εκτύπωση του μενου
void printMenu();

// εκτύπωση βιβλίου
void print(book b);

// ανάκτηση λίστας βιβλίων από αρχείο
list load(char *filename);

// αποθήκευση λίστας βιβλίων στο αρχείο
void save(char *filename, list bList);

// προσθήκη βιβίου στη λίστα
int addBook(book b, list bList);

// αναζήτηση με βάση το b->id
book findBook(book b, list bList);

// διαγραφή με βάση το b->id
int deleteBook(book b, list bList);

// ανανέωση με βάση το b->id
int updateBook(book b, list bList);

// οι συναρτήσεις μου
// εκτύπωση όλων των βιβλίων
void printList(list bList);

// δημιουργία βιβλίου
book createBook();

#endif
