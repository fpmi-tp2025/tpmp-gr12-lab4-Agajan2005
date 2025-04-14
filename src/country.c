#include <stdio.h>
#include "country.h"
#include "database.h"

void add_country() {
    char name[100], capital[100], language[50], currency[50], head[100];
    int population;
    float square;

    printf("Enter country name: ");
    scanf("%s", name);
    printf("Enter capital: ");
    scanf("%s", capital);
    printf("Enter language: ");
    scanf("%s", language);
    printf("Enter population: ");
    scanf("%d", &population);
    printf("Enter square (in km²): ");
    scanf("%f", &square);
    printf("Enter currency: ");
    scanf("%s", currency);
    printf("Enter head of country: ");
    scanf("%s", head);

    if (db_add_country(name, capital, language, population, square, 
currency, head) == SQLITE_OK) {
        printf("Country added successfully.\n");
    } else {
        printf("Failed to add country.\n");
    }
}

void delete_country() {
    int id;
    printf("Enter country ID to delete: ");
    scanf("%d", &id);

    if (db_delete_country(id) == SQLITE_OK) {
        printf("Country deleted successfully.\n");
    } else {
        printf("Failed to delete country.\n");
    }
}
