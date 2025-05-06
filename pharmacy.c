#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "pharmacy.txt"
#define SALES_FILE "sales.txt"

typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Medicine;


void addMedicine();
void viewMedicines();
void searchMedicine();
void updateMedicine();
void deleteMedicine();
void sellMedicine();
void viewLowStock();
void generateSalesReport();
void menu();

void addMedicine() {
    FILE *f = fopen(FILE_NAME, "a");
    Medicine m;
    printf("Enter Medicine ID: ");
    scanf("%d", &m.id);
    printf("Enter Name: ");
    scanf("%s", m.name);
    printf("Enter Quantity: ");
    scanf("%d", &m.quantity);
    printf("Enter Price: ");
    scanf("%f", &m.price);
    fwrite(&m, sizeof(Medicine), 1, f);
    fclose(f);
    printf("Medicine added successfully!\n");
}

void viewMedicines() {
    FILE *f = fopen(FILE_NAME, "r");
    Medicine m;
    printf("\n=== All Medicines ===\n");
    printf("%-5s %-20s %-10s %-10s\n", "ID", "Name", "Qty", "Price");
    while (fread(&m, sizeof(Medicine), 1, f)) {
        printf("%-5d %-20s %-10d %-10.2f\n", m.id, m.name, m.quantity, m.price);
    }
    fclose(f);
}

void searchMedicine() {
    FILE *f = fopen(FILE_NAME, "r");
    int id, found = 0;
    Medicine m;
    printf("Enter Medicine ID to search: ");
    scanf("%d", &id);
    while (fread(&m, sizeof(Medicine), 1, f)) {
        if (m.id == id) {
            printf("Medicine Found: %s | Qty: %d | Price: %.2f\n", m.name, m.quantity, m.price);
            found = 1;
            break;
        }
    }
    fclose(f);
    if (!found) printf("Medicine not found!\n");
}

void updateMedicine() {
    FILE *f = fopen(FILE_NAME, "r+");
    int id, found = 0;
    Medicine m;
    printf("Enter Medicine ID to update: ");
    scanf("%d", &id);
    while (fread(&m, sizeof(Medicine), 1, f)) {
        if (m.id == id) {
            printf("Enter new name: ");
            scanf("%s", m.name);
            printf("Enter new quantity: ");
            scanf("%d", &m.quantity);
            printf("Enter new price: ");
            scanf("%f", &m.price);
            fseek(f, -sizeof(Medicine), SEEK_CUR);
            fwrite(&m, sizeof(Medicine), 1, f);
            found = 1;
            printf("Medicine updated successfully!\n");
            break;
        }
    }
    fclose(f);
    if (!found) printf("Medicine not found!\n");
}

void deleteMedicine() {
    FILE *f = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    int id, found = 0;
    Medicine m;
    printf("Enter Medicine ID to delete: ");
    scanf("%d", &id);
    while (fread(&m, sizeof(Medicine), 1, f)) {
        if (m.id != id) {
            fwrite(&m, sizeof(Medicine), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(f);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    if (found) printf("Medicine deleted successfully!\n");
    else printf("Medicine not found!\n");
}

void sellMedicine() {
    FILE *f = fopen(FILE_NAME, "r+");
    int id, qty, found = 0;
    Medicine m;
    printf("Enter Medicine ID to sell: ");
    scanf("%d", &id);
    printf("Enter quantity to sell: ");
    scanf("%d", &qty);
    while (fread(&m, sizeof(Medicine), 1, f)) {
        if (m.id == id) {
            if (m.quantity >= qty) {
                m.quantity -= qty;
                fseek(f, -sizeof(Medicine), SEEK_CUR);
                fwrite(&m, sizeof(Medicine), 1, f);
                printf("Sale completed! Remaining stock: %d\n", m.quantity);

                
                FILE *sales = fopen(SALES_FILE, "a");
                fprintf(sales, "%d %d %.2f\n", id, qty, m.price);
                fclose(sales);

                found = 1;
            } else {
                printf("Not enough stock!\n");
                found = 1;
            }
            break;
        }
    }
    fclose(f);
    if (!found) printf("Medicine not found!\n");
}

void viewLowStock() {
    FILE *f = fopen(FILE_NAME, "r");
    Medicine m;
    printf("\n=== Low Stock Medicines (Less than 5) ===\n");
    while (fread(&m, sizeof(Medicine), 1, f)) {
        if (m.quantity < 5) {
            printf("ID: %d | Name: %s | Qty: %d\n", m.id, m.name, m.quantity);
        }
    }
    fclose(f);
}

void generateSalesReport() {
    FILE *f = fopen(SALES_FILE, "r");
    if (!f) {
        printf("No sales recorded yet.\n");
        return;
    }

    int id, qty, totalQty = 0;
    float price, totalRevenue = 0.0;

    printf("\n=== Sales Report ===\n");
    printf("%-5s %-10s %-10s\n", "ID", "Qty", "Price");

    while (fscanf(f, "%d %d %f\n", &id, &qty, &price) != EOF) {
        printf("%-5d %-10d %-10.2f\n", id, qty, price);
        totalQty += qty;
        totalRevenue += qty * price;
    }

    printf("\nTotal Sold: %d units\n", totalQty);
    printf("Total Revenue: Rs. %.2f\n", totalRevenue);
    fclose(f);
}

void menu() {
    int choice;
    while (1) {
        printf("\n====== Pharmacy Management System ======\n");
        printf("1. Add Medicine\n");
        printf("2. View All Medicines\n");
        printf("3. Search Medicine\n");
        printf("4. Update Medicine\n");
        printf("5. Delete Medicine\n");
        printf("6. Sell Medicine\n");
        printf("7. View Low Stock\n");
        printf("8. Generate Sales Report\n");
        printf("9. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addMedicine(); break;
            case 2: viewMedicines(); break;
            case 3: searchMedicine(); break;
            case 4: updateMedicine(); break;
            case 5: deleteMedicine(); break;
            case 6: sellMedicine(); break;
            case 7: viewLowStock(); break;
            case 8: generateSalesReport(); break;
            case 9: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
