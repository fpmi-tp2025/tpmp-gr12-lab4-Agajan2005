#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include "auth.h"
#include "country.h"
#include "region.h"

void show_menu() {
    printf("\nCountryApp Menu:\n");
    printf("1. Add Country\n");
    printf("2. Delete Country\n");
    printf("3. Add Region\n");
    printf("4. Delete Region\n");
    printf("5. List Regions for a Country\n");
    printf("6. Average Population of Regions\n");
    printf("7. Total Population of All Countries\n");
    printf("8. Exit\n");
    printf("Choose an option: ");
}

int main() {
    if (db_init("countries.db") != SQLITE_OK) {
        printf("Ошибка открытия базы данных\n");
        return 1;
    }

    char username[50], password[50];
    printf("=== CountryApp ===\n");
    printf("1. Login\n2. Register\nChoose an option: ");
    int auth_choice;
    scanf("%d", &auth_choice);

    if (auth_choice == 1) {
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);
        if (!login(username, password)) {
            printf("Authentication failed.\n");
            db_close();
            return 1;
        }
    } else if (auth_choice == 2) {
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);
        if (register_user(username, password) != SQLITE_OK) {
            printf("Registration failed.\n");
            db_close();
            return 1;
        }
        printf("User registered. Please login.\n");
        main(); // Перезапускаем для логина
        return 0;
    } else {
        printf("Invalid choice.\n");
        db_close();
        return 1;
    }

    printf("Authentication successful!\n");

    int choice, country_id;
    while (1) {
        show_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_country();
                break;
            case 2:
                delete_country();
                break;
            case 3:
                add_region();
                break;
            case 4:
                delete_region();
                break;
            case 5:
                printf("Enter country ID: ");
                scanf("%d", &country_id);
                db_list_regions(country_id);
                break;
            case 6:
                printf("Enter country ID: ");
                scanf("%d", &country_id);
                printf("Average population: %.2f\n", 
db_avg_region_population(country_id));
                break;
            case 7:
                printf("Total population: %d\n", db_total_population());
                break;
            case 8:
                db_close();
                exit(0);
            default:
                printf("Invalid option.\n");
        }
    }

    db_close();
    return 0;
}
