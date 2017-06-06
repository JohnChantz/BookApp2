#include <stdio.h>
#include <stdlib.h>
#include "books.h"

int main(int argc, char *argv[]) {
    int ID;
    int choice;
    list bList = NULL;
    book tmpBk = NULL;

    if (argc != 2) {
        printf(" Error\n"); // μηνυμα λαθους σε περιπτωση που δεν μπει μονο 1 παραμετρος απο την γραμμη εντολων
        abort();
    }
    // φορτωμα αρχειου κατα την εναρξη του προγραμματος η ενναλακτικα δημιουργια αρχειου
    bList = load(argv[1]);

    do {
        printMenu();
        do {
            scanf("%d", &choice);
        } while (choice <= 0 || choice >= 7); // διαβαζει την επιλογη του χρηστη εως οτου να ειναι απο 1 εως 6
        switch (choice) {
            case 1 :
                // προσθηκη βιβλιου
                tmpBk = createBook();
                addBook(tmpBk, bList);
                break;
            case 2 :
                // διαγραφη βιβλιου
                tmpBk = (book) malloc(sizeof(bookR));
                printf("Please give the book ID\n");
                scanf("%d", &ID);
                tmpBk->id = ID; //αναθεση ID
                deleteBook(tmpBk, bList);
                break;
            case 3 :
                // ανανεωση βιβλιου
                tmpBk = (book) malloc(sizeof(bookR));
                printf("Please give the book ID\n");
                scanf("%d", &ID);
                tmpBk->id = ID; //αναθεση ID
                updateBook(tmpBk, bList);
                break;
            case 4 :
                //  εκτυπωση βιβλιου
                printf("Please give the book ID\n");
                scanf("%d", &ID);
                tmpBk->id = ID; //αναθεση ID
                tmpBk = findBook(tmpBk, bList);
                if (tmpBk == NULL) {
                    printf("There is not a book in the list with this id. Please try again with a different one\n");
                } else {
                    print(tmpBk);
                }
                break;
            case 5 :
                // εκτύπωση ολων των βιβλιων απο τη λιστα
                printList(bList);
                break;
            case 6 :
                // εξοδος απο το μενου
                save(argv[1], bList);
                printf(" Exit from menu \n");
                break;
            default:
                break;
        }
    } while (choice != 6);
    return 0;
}







