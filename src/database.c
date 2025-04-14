#include <stdio.h>
#include <string.h>
#include "database.h"

sqlite3 *db;

int db_init(const char *db_name) {
    int rc = sqlite3_open(db_name, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return rc;
    }
    return SQLITE_OK;
}

int db_create_user(const char *username, const char *password) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO user (username, password_hash) VALUES ('%s', '%s');", username, password);
    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    return rc;
}

int db_auth_user(const char *username, const char *password) {
    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT COUNT(*) FROM user WHERE username='%s' AND password_hash='%s';", username, password);
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) return 0;
    
    rc = sqlite3_step(stmt);
    int count = (rc == SQLITE_ROW) ? sqlite3_column_int(stmt, 0) : 0;
    sqlite3_finalize(stmt);
    return count > 0;
}

int db_add_country(const char *name, const char *capital, const char *language, int population, float square, const char *currency, const char *head) {
    char sql[512];
    snprintf(sql, sizeof(sql), "INSERT INTO country (name, capital, language, population_country, square_country, currency, head_country) VALUES ('%s', '%s', '%s', %d, %.2f, '%s', '%s');",
             name, capital, language, population, square, currency, head);
    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    return rc;
}

int db_add_region(const char *name, const char *capital, int population, float square, int country_id) {
    char sql[512];
    snprintf(sql, sizeof(sql), "INSERT INTO region (name, capital_region, population_region, square_region, country_id) VALUES ('%s', '%s', %d, %.2f, %d);",
             name, capital, population, square, country_id);
    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    return rc;
}

int db_delete_country(int id) {
    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM country WHERE id=%d;", id);
    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    return rc;
}

int db_delete_region(int id) {
    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM region WHERE id=%d;", id);
    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    return rc;
}

void db_list_regions(int country_id) {
    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT id, name, capital_region, population_region, square_region FROM region WHERE country_id=%d;", country_id);
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) return;

    printf("Regions for country ID %d:\n", country_id);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("ID: %d, Name: %s, Capital: %s, Population: %d, Square: %.2f\n",
               sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_text(stmt, 2),
               sqlite3_column_int(stmt, 3),
               sqlite3_column_double(stmt, 4));
    }
    sqlite3_finalize(stmt);
}

float db_avg_region_population(int country_id) {
    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT AVG(population_region) FROM region WHERE country_id=%d;", country_id);
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) return 0.0;

    rc = sqlite3_step(stmt);
    float avg = (rc == SQLITE_ROW) ? sqlite3_column_double(stmt, 0) : 0.0;
    sqlite3_finalize(stmt);
    return avg;
}

int db_total_population() {
    char sql[] = "SELECT SUM(population_country) FROM country;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) return 0;

    rc = sqlite3_step(stmt);
    int total = (rc == SQLITE_ROW) ? sqlite3_column_int(stmt, 0) : 0;
    sqlite3_finalize(stmt);
    return total;
}

void db_close() {
    sqlite3_close(db);
}