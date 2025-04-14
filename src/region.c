#include <stdio.h>
#include "region.h"
#include "database.h"

void add_region() {
    char name[100], capital[100];
    int population, country_id;
    float square;

    printf("Enter region name: ");
    scanf("%s", name);
    printf("Enter capital: ");
    scanf("%s", capital);
    printf("Enter population: ");
    scanf("%d", &population);
    printf("Enter square (in km²): ");
    scanf("%f", &square);
    printf("Enter country ID: ");
    scanf("%d", &country_id);

    if (db_add_region(name, capital, population, square, country_id) == 
SQLITE_OK) {
        printf("Region added successfully.\n");
    } else {
        printf("Failed to add region.\n");
    }
}

void delete_region() {
    int id;
    printf("Enter region ID to delete: ");
    scanf("%d", &id);

    if (db_delete_region(id) == SQLITE_OK) {
        printf("Region deleted successfully.\n");
    } else {
        printf("Failed to delete region.\n");
    }
}
