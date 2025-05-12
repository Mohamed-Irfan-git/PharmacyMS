
#include <stdio.h>
#include <stdlib.h>

struct Medicine {
    int id;
    char name[100];
    int quantity;
    float price;
};

void viewMedicines() {
    FILE *file = fopen("medicines.txt", "r");
    struct Medicine med;

    if (file == NULL) {
        printf("Error: Cannot open file.\n");
        return;
    }

    printf("\n--- Medicine List ---\n");
    printf("%-5s %-20s %-10s %-10s\n", "ID", "Name", "Quantity", "Price");
    printf("-----------------------------------------------\n");

    while (fscanf(file, "%d %s %d %f", &med.id, med.name, &med.quantity, &med.price) != EOF) {
        printf("%-5d %-20s %-10d %-10.2f\n", med.id, med.name, med.quantity, med.price);
    }

    fclose(file);
}

int main() {
    viewMedicines();
    return 0;
}

