#include <stdio.h>
#include <stdlib.h>
#include "books.h"

void printMenu() {
    printf("\t\t Welcome to the Book Application Menu !!!\n\n");
    printf(" Press a number from 1 to 6 for the following actions : \n");
    printf(" Add a new book... -> 1.\n");
    printf(" Delete a book... -> 2.\n");
    printf(" Update a book...-> 3.\n");
    printf(" Print a book...-> 4. \n");
    printf(" Print all the books from the list...-> 5.\n");
    printf(" Quit...-> 6\n");
}

void print(book b) {
    printf(" ID is : %d\n", b->id);
    printf(" Author is : %s\n", b->author);
    printf(" Title is : %s\n", b->title);
    if (b->genre == 0) {
        printf(" Genre is : Fiction\n");
    } else if (b->genre == 1) {
        printf(" Genre is : Scientific\n");
    } else {
        printf(" Genre is : politics\n");
    }
    printf(" Reviews : %s\n", b->reviews[1]);
}

int addBook(book b, list bList) {
    list crtBk = bList;
    list lastBk = bList;
    // προσθηκη βιβλιου στην αρχη της λιστας, οταν ο 1ος κομβος ειναι αδειος
    if (crtBk->nextBk == NULL && crtBk->x == NULL) {
        bList->x = b;
        bList->nextBk = NULL;
        return 1;
    }
    // διασχιζει τη λιστα και οταν βρει το τελευταιο βιβλιο, τοτε βαζει στο τελος το νεο βιβλιο
    while ((crtBk != NULL)) {
        crtBk = crtBk->nextBk;
        if ((crtBk != NULL)) {
            lastBk = crtBk;
        }
    }
    list newListItem = (list) malloc(sizeof(list));
    newListItem->x = b;
    newListItem->nextBk = NULL;
    lastBk->nextBk = newListItem;
    return 1;
}

book findBook(book b, list bList) {
    list crtBk = bList;
    if (crtBk->x->id == 0) {
        return NULL;
    }
    // ψαχνει σε ολη την λιστα και οταν εντοπισει το id που θελουμε επιστρεφει το βιβλιο
    do {
        if (crtBk->x->id == b->id) {
            return crtBk->x;
        }
        crtBk = crtBk->nextBk;
    } while (crtBk != NULL); // σε περιπτωση που δεν βρει το id
    printf(" There is not a book in the list with this id. Please try again with a different one\n");
    return NULL;
}

int deleteBook(book b, list bList) {
    list prevBook = bList;
    list crtBk = bList;
    if (b == NULL) {
        return 0;
    }
    while (1) {
        if (crtBk->x->id == b->id) {           //διαγραφη του πρωτου βιβλιου ενω υπαρχουν και αλλα βιβλια στη λιστα
            if (crtBk == bList && crtBk->nextBk != NULL) {
                bList->x = bList->nextBk->x;
                bList->nextBk = bList->nextBk->nextBk;
            } else if (crtBk == bList &&
                       bList->nextBk == NULL) {      //διαγραφη του πρωτου βιβλιου οταν ειναι το μοναδικο στη λιστα
                bList->x = NULL;
                bList->nextBk = NULL;
            } else if (crtBk->nextBk == NULL) {            //διαγραφη του τελευταιου βιβλιου
                prevBook->nextBk = NULL;
                free(crtBk);
            } else if (crtBk->nextBk != NULL) {            //διαγραφη καποιου ενδιαμεσου βιβλιου
                prevBook->nextBk = crtBk->nextBk;
                free(crtBk);
            }
            return 1;
        }
        prevBook = crtBk;
        crtBk = crtBk->nextBk;
    }
}

int updateBook(book b, list bList) {
    list crtBk = bList;
    int choice; // επιλογη του χρηστη
    if (b == NULL) { // αν το βιβλιο δεν εχει τιποτα μεσα
        return 0;
    }
    while (crtBk != NULL) {
        if (b->id == crtBk->x->id) {
            do {
                printf("\t\t Press 1 if you want to change/add the name of author\n");
                printf("\t\t Press 2 if you want to change/add the title of book\n");
                printf("\t\t Press 3 if you want to change/add the genre\n");
                printf("\t\t Press 4 if you want to change/add reviews\n");
                printf("\t\t Press 5 if you want to quit\n");

                scanf("%d", &choice);
                switch (choice) {
                    case 1 :
                        printf(" Give me the new name of author\n");
                        scanf("%s", crtBk->x->author);
                        break;
                    case 2 :
                        printf(" Give me the new title\n");
                        scanf("%s", crtBk->x->title);
                        break;
                    case 3 :
                        printf(" Give the new genre\n");
                        printf("For fiction press 1, for scientific 2 and 3 for politics\n");
                        scanf("%d", &crtBk->x->genre);
                        break;
                    case 4 :
                        printf(" Type the new reviews\n");
                        scanf("%s", crtBk->x->reviews[1]);
                        break;
                    case 5 :
                        printf(" Update completed\n");
                    default:
                        break;
                }
            } while (choice != 5);
        }
        crtBk = crtBk->nextBk; // συνεχισε στο επομενο βιβλιο
    }
    return 1;
}

list load(char *filename) {
    int size, number, i;
    book tmp;
    list bList = (list) malloc(sizeof(bookList));   //φτιαξε νεα λιστα για να φορτωσει τα δεδομενα του αρχειου
    bList->x = NULL;
    bList->nextBk = NULL;
    FILE *fd;
    if ((fd = fopen(filename, "a+")) == NULL) {    // συνδεση με το αρχειο
        fprintf(stderr, " File could not be opened\n");
        exit(1);
    }
    fseek(fd, 0, SEEK_END);
    size = ftell(fd); // υπολογισμος μεγεθους αρχειου
    if (size == 0) {
        printf("Empty file, nothing to load!\n");
        return bList;
    }
    number = size / sizeof(bookR); // υπολογισμος αριθμου στοιχειων
    fseek(fd, 0, SEEK_SET);
    for (i = 0; i < number; i++) {
        tmp = (book) malloc(sizeof(bookR));
        if (tmp == NULL) {
            fprintf(stderr, "Could not allocate memory!");
            abort();
        }
        fread(tmp, sizeof(bookR), 1, fd); // για καθε στοιχειο που υπαρχει, χρησιμοποιουμε την tmp η οποια..
        addBook(tmp, bList);    //.. στη συνεχεια το περναει στη λιστα
    }
    fclose(fd);
    return bList;    // επιστροφη λιστας βιβλιων
}

void save(char *filename, list bList) {
    list crtBk = bList;
    FILE *fd;
    if ((fd = fopen(filename, "w")) == NULL) {    // συνδεση με το αρχειο
        fprintf(stderr, " File could not be opened\n");
        exit(1);
    }
    while (crtBk != NULL) {    // οσο το βιβλιο εχει στοιχεια μεσα
        fwrite(crtBk->x, sizeof(bookR), 1, fd);
        crtBk = crtBk->nextBk;        // πηγαινε στο επομενο βιβλιο
    }
    fclose(fd);
    return;
}

// οι συναρτησεις μου
void printList(list bList) {
    list crtBk = bList;
    if (crtBk->x == NULL && crtBk->nextBk == NULL) {
        printf(" List is empty\n");
        return;
    }
    // οσο η λιστα εχει βιβλια καλεσε την print(book) και στη συνεχεια πηγαινε στο επομενο βιβλιο
    while (crtBk != NULL) {
        print(crtBk->x);
        crtBk = crtBk->nextBk;
    }
    return;
}

book createBook() {
    int size;
    book newBk = (book) malloc(sizeof(bookR));
    if (newBk == NULL) {
        fprintf(stderr, " Could not allocate memory!\n");
        abort();
    }
    printf("Give book ID: ");
    scanf("%d", &newBk->id);
    printf("Give book Title: ");
    fseek(stdin, 0,
          SEEK_END);        // επειδη διαβαζουμε int πιο πανω, το \n μενει στον buffer του stdin, για αυτο και καθαριζουμε τον buffer
    fgets(newBk->title, MAXSTRING, stdin);
    size = strlen(newBk->title);
    newBk->title[size - 1] = '\0';
    printf("Give book Genre (1=fiction,2=scientific,3=politics): \n");
    scanf("%d", &newBk->genre);
    printf("Give book Author: ");
    fseek(stdin, 0, SEEK_END);
    fgets(newBk->author, MAXSTRING, stdin);
    size = strlen(newBk->author);
    newBk->author[size - 1] = '\0';
    printf("Give book Review: ");
    fgets(newBk->reviews[1], MAXSTRING, stdin);
    size = strlen(newBk->reviews[1]);
    newBk->reviews[1][size - 1] = '\0';
    return newBk;
}






































