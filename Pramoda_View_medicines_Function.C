
#include <stdio.h>

void viewMedicines() {
    printf("**** Welcome to Pharmacy Management System ****\n");
    printf("=============== Medicine List ===============\n");
    printf("%-10s %-20s %-10s %-10s\n", "ID", "Name", "Price(Rs)", "Stock");
    printf("----------------------------------------------\n");

   
    printf("%-10s %-20s %-10.2f %-10d\n", "001", "Paracetamol", 20.0, 100);
    printf("%-10s %-20s %-10.2f %-10d\n", "002", "Amoxicillin", 45.5, 50);
    printf("%-10s %-20s %-10.2f %-10d\n", "003", "Ibuprofen", 30.0, 75);
    printf("%-10s %-20s %-10.2f %-10d\n", "004", "Cetirizine", 15.0, 120);
    printf("%-10s %-20s %-10.2f %-10d\n", "005", "Azithromycin", 60.0, 35);

    printf("==============================================\n");
}


int main() {
    viewMedicines();
    return 0;
}