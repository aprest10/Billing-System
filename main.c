#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int option, num;
bool found = false;
float total;
struct orders writeOrder;
struct orders readOrder;
char saveBill = 'y';
char contLoop = 'y';
char name[50];
FILE *fp;

struct items {
    char item[20];
    float price;
    int qty;
};

struct orders {
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

//function to generate bills
void generateBillHeader (char headerName[50], char headerDate[30]) {
    printf("\n\t======================================");
    printf("\n\tDate: %s", headerDate);
    printf("\n\tInvoice for: %s", headerName);
    printf("\n\t--------------------------------------\n");
    printf("\tItems\tQty\t\t\tTotal");
    printf("\n\t--------------------------------------\n\n");
}

void generateBillBody (char item[30], int qty, float price) {
    printf("\t%-7.7s\t%-7.d\t\t%-18.2f\n", item, qty, qty * price);
}

void generateBillFooter (float footerTotal) {
    float discount = 0.1 * footerTotal;
    float netTotal = footerTotal - discount;
    float tax = 0.09 * netTotal;
    float grandTotal = netTotal + tax;
    printf("\n\t--------------------------------------\n");
    printf("\tSub Total\t\t\t%-18.2f", footerTotal);
    printf("\n\tDiscount @10%s\t   -%-18.2f", "%", discount);
    printf("\n\t         --------------------");
    printf("\n\tNet Total\t\t\t%-18.2f", netTotal);
    printf("\n\tTAX @9%s\t\t\t\t%-18.2f", "%", tax);
    printf("\n\t--------------------------------------");
    printf("\n\tGrand Total\t\t\t%-18.2f", grandTotal);
    printf("\n\t======================================\n");
}

void generateInvoice () {
    printf("\e[1;1H\e[2J");// clear screen fast!
    printf("\tPlease enter the name of the customer:\t");
    fgets(writeOrder.customer, 50, stdin);
    writeOrder.customer[strlen(writeOrder.customer) - 1] = 0; //removes newline char
    strcpy(writeOrder.date, __DATE__);
    printf("\n\tPlease enter the number of items:\t");
    scanf("%d", &num);
    writeOrder.numOfItems = num;

    for (int i = 0; i < num; ++i) {
        fgetc(stdin);
        printf("\n\tName of item %d (7 characters or less):\t", i + 1);
        fgets(writeOrder.itm[i].item, 20, stdin);
        writeOrder.itm[i].item[strlen(writeOrder.itm[i].item) - 1] = 0;
        printf("\tPlease enter the quantity:\t");
        scanf("%d", &writeOrder.itm[i].qty);
        printf("\tPlease enter the unit price:\t");
        scanf("%f", &writeOrder.itm[i].price);
        total += writeOrder.itm[i].qty * writeOrder.itm[i].price;
    }

    generateBillHeader(writeOrder.customer, writeOrder.date);

    for (int i = 0; i < writeOrder.numOfItems; ++i)
        generateBillBody(writeOrder.itm[i].item, writeOrder.itm[i].qty, writeOrder.itm[i].price);

    generateBillFooter(total);

    printf("\n\tDo you want to save the invoice [y/n]:\t");
    scanf("%s", &saveBill);

    if (saveBill == 'y') {
        fp = fopen("Invoices.dat", "a+");
        fwrite(&writeOrder, sizeof(struct orders), 1, fp);
        if (fwrite != 0)
            printf("\n\tSuccessfully saved");
        else
            printf("\n\tError saving"); //should never reach this code
        fclose(fp);
    }
}

void allInvoices () {
    printf("\e[1;1H\e[2J");// clear screen fast!
    fp = fopen("Invoices.dat", "r");
    printf("\n\t********* Previous  Invoices *********\n");
    while (fread(&readOrder, sizeof(struct orders), 1, fp)) {
        float eachTotal = 0;
        generateBillHeader(readOrder.customer, readOrder.date);
        for (int i = 0; i < readOrder.numOfItems; ++i) {
            generateBillBody(readOrder.itm[i].item, readOrder.itm[i].qty, readOrder.itm[i].price);
            eachTotal += readOrder.itm[i].qty * readOrder.itm[i].price;
        }
        generateBillFooter(eachTotal);
    }
    fclose(fp);
}

void searchInvoice() {
    printf("\n\tEnter the name of the customer:\t");
    fgets(name, 50, stdin);
    name[strlen(name) - 1] = 0;
    printf("\e[1;1H\e[2J");// clear screen fast!
    fp = fopen("Invoices.dat", "r");
    printf("\t********* Invoice of %s *********\n", name);
    while (fread(&readOrder, sizeof(struct orders), 1, fp)) {
        float eachTotal = 0;
        if (!strcmp(readOrder.customer, name)) {
            generateBillHeader(readOrder.customer, readOrder.date);
            for (int i = 0; i < readOrder.numOfItems; ++i) {
                generateBillBody(readOrder.itm[i].item, readOrder.itm[i].qty, readOrder.itm[i].price);
                eachTotal += readOrder.itm[i].qty * readOrder.itm[i].price;
            }
            generateBillFooter(eachTotal);
            found = true;
        }
    }
    if (!found) {
        printf("\n\tNo invoices found for %s", name);
    }
    fclose(fp);
}

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
    printf("\n\t\tThank You for using Bills-R-Us!");
    return 0;
}
