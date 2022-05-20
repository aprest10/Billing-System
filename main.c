#include <stdio.h>
#include <stdlib.h>
#include "bills.h"

int option;
char contLoop = 'y';

int main() {
    while (contLoop == 'y') {
        printf("\e[1;1H\e[2J");// clear screen fast!

        //dashboard
        printf("\t============= Bills-R-Us =============");
        printf("\n\n\tPlease select an option");
        printf("\n\n\t1. Generate Invoice");
        printf("\n\t2. Show all Invoices");
        printf("\n\t3. Search Invoices by name");
        printf("\n\t4. Exit");
        printf("\n\n\tEnter number:\t");
        scanf("%d", &option);
        fgetc(stdin);

        switch (option) {
            case 1:
                generateInvoice();
                break;
            case 2:
                if (fopen("Invoices.dat", "r"))
                    allInvoices();
                else {
                    printf("\e[1;1H\e[2J");// clear screen fast!
                    printf("\n\tNo Invoices\n");
                }
                break;
            case 3:
                if (fopen("Invoices.dat", "r"))
                    searchInvoice();
                else {
                    printf("\e[1;1H\e[2J");// clear screen fast!
                    printf("\n\tNo Invoices\n");
                }
                break;
            case 4:
                printf("\e[1;1H\e[2J");// clear screen fast!
                printf("\n\t\tThank You for using Bills-R-Us!");
                exit(0);
            default:
                printf("\tInvalid input\n\tPlease enter a valid number\n");
                break;
        }
        printf("\n\tDo you want to continue? [y/n]\t");
        scanf("%s", &contLoop);
    }
    printf("\e[1;1H\e[2J");// clear screen fast!
    printf("\n\t\tThank You for using Bills-R-Us!\n");
    return 0;
}
