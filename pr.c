/***************************************************************
 * Program Name : Shop Item Record Management System
 * Description  : This program manages product records of a shop.
 *                It allows the user to:
 *                - Enter details of 5 products
 *                - Store product records in a file
 *                - Display product records in tabular format
 *                - Calculate and display total bill amount
 *                - Search a product using Product ID
 *
 * Author       : Saniya
 * Date         : 04 January 2026
 * Version      : 1.0
 ***************************************************************/

#include <stdio.h>

#define PRODUCT_COUNT 5
#define FILE_NAME "products.dat"

/* Structure to store product information */
typedef struct {
    int   id;
    char  name[30];
    int   qty;
    float price;
    float total;
} Product;

/* Function Declarations */
void saveProducts(void);
void displayProducts(void);
void searchProduct(void);

int main(void) {
    int choice;

    /* Menu-driven execution */
    do {
        printf("\n=====================================\n");
        printf("   SHOP MANAGEMENT SYSTEM\n");
        printf("=====================================\n");
        printf("1. Add Product Records\n");
        printf("2. Display Products & Total Bill\n");
        printf("3. Search Product by ID\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: saveProducts();    break;
            case 2: displayProducts(); break;
            case 3: searchProduct();   break;
            case 4: printf("Application closed.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}

/*-------------------------------------------------------------
 * Function Name : saveProducts
 * Purpose       : Accept product details and store them in file
 *------------------------------------------------------------*/
void saveProducts(void) {
    FILE *fp = fopen(FILE_NAME, "wb");
    Product p;

    /* Validate file opening */
    if (!fp) {
        printf("File error.\n");
        return;
    }

    /* Accept and store fixed number of product records */
    for (int i = 0; i < PRODUCT_COUNT; i++) {
        printf("\nEnter Product %d Details\n", i + 1);

        printf("Product ID   : ");
        scanf("%d", &p.id);

        printf("Product Name : ");
        scanf(" %[^\n]", p.name);

        printf("Quantity     : ");
        scanf("%d", &p.qty);

        printf("Price        : ");
        scanf("%f", &p.price);

        /* Logic: Calculate total price for the current product */
        p.total = p.qty * p.price;

        /* Logic: Write product record into binary file */
        fwrite(&p, sizeof(Product), 1, fp);
    }

    fclose(fp);
    printf("\nRecords saved successfully.\n");
}

/*-------------------------------------------------------------
 * Function Name : displayProducts
 * Purpose       : Read product records from file, display them
 *                 in tabular format and calculate total bill
 *------------------------------------------------------------*/
void displayProducts(void) {
    FILE *fp = fopen(FILE_NAME, "rb");
    Product p;
    float bill = 0.0f;

    /* Validate file existence */
    if (!fp) {
        printf("No records found.\n");
        return;
    }

    printf("\n-------------------------------------------------\n");
    printf("ID\tName\t\tQty\tPrice\tTotal\n");
    printf("-------------------------------------------------\n");

    /* Logic: Read each record and accumulate total bill */
    while (fread(&p, sizeof(Product), 1, fp)) {
        printf("%d\t%-10s\t%d\t%.2f\t%.2f\n",
               p.id, p.name, p.qty, p.price, p.total);

        bill += p.total;
    }

    printf("-------------------------------------------------\n");
    printf("Total Bill Amount: %.2f\n", bill);

    fclose(fp);
}

/*-------------------------------------------------------------
 * Function Name : searchProduct
 * Purpose       : Search and display product using Product ID
 *------------------------------------------------------------*/
void searchProduct(void) {
    FILE *fp = fopen(FILE_NAME, "rb");
    Product p;
    int id, found = 0;

    /* Validate file existence */
    if (!fp) {
        printf("No records found.\n");
        return;
    }

    printf("Enter Product ID to search: ");
    scanf("%d", &id);

    /* Logic: Sequentially search product by matching ID */
    while (fread(&p, sizeof(Product), 1, fp)) {
        if (p.id == id) {
            printf("\nProduct Found\n");
            printf("ID       : %d\n", p.id);
            printf("Name     : %s\n", p.name);
            printf("Quantity : %d\n", p.qty);
            printf("Price    : %.2f\n", p.price);
            printf("Total    : %.2f\n", p.total);
            found = 1;
            break;
        }
    }

    /* Logic: Display message if product is not found */
    if (!found)
        printf("\nProduct not found.\n");

    fclose(fp);
}
