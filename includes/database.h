#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

int db_init(const char *db_name);
int db_create_user(const char *username, const char *password);
int db_auth_user(const char *username, const char *password);
int db_add_country(const char *name, const char *capital, const char *language, int population, float square, const char *currency, const char *head);
int db_add_region(const char *name, const char *capital, int population, float square, int country_id);
int db_delete_country(int id);
int db_delete_region(int id);
void db_list_regions(int country_id);
float db_avg_region_population(int country_id);
int db_total_population();
void db_close();

#endif