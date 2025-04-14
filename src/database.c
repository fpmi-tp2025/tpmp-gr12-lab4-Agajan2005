#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "database.h"

// Создание таблиц (если не существуют)
int db_init(sqlite3 *db) {
    char *err_msg = NULL;
    const char *sql = "CREATE TABLE IF NOT EXISTS user ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "username TEXT NOT NULL UNIQUE,"
                      "password_hash TEXT NOT NULL);"
                      "CREATE TABLE IF NOT EXISTS country ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "name TEXT NOT NULL,"
                      "capital TEXT NOT NULL,"
                      "language TEXT,"
                      "population INTEGER,"
                      "area REAL,"
                      "currency TEXT,"
                      "government TEXT);"
                      "CREATE TABLE IF NOT EXISTS region ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "name TEXT NOT NULL,"
                      "capital_region TEXT,"
                      "population_region INTEGER,"
                      "area_region REAL,"
                      "country_id INTEGER,"
                      "FOREIGN KEY(country_id) REFERENCES country(id));";

    int rc = sqlite3_exec(db, sql, NULL, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return -1;
    }
    return 0;
}

// Добавление пользователя
int db_add_user(sqlite3 *db, const char *username, const char *password) {
    char sql[512];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO user (username, password_hash) "
             "VALUES ('%s', '%s');", 
             username, password);

    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, NULL, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return -1;
    }
    return 0;
}

// Проверка пользователя
int db_check_user(sqlite3 *db, const char *username, const char *password) 
{
    char sql[512];
    snprintf(sql, sizeof(sql), 
             "SELECT COUNT(*) FROM user WHERE "
             "username='%s' AND password_hash='%s';", 
             username, password);

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return count;
}

// Добавление страны
int db_add_country(sqlite3 *db, const char *name, const char *capital, 
                   const char *language, int population, float area, 
                   const char *currency, const char *government) {
    char sql[1024];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO country (name, capital, language, population, "
             "area, currency, government) "
             "VALUES ('%s', '%s', '%s', %d, %.2f, '%s', '%s');",
             name, capital, language, population, area, currency, 
government);

    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, NULL, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return -1;
    }
    return 0;
}

// Добавление региона
int db_add_region(sqlite3 *db, const char *name, const char *capital, 
                  int population, float area, int country_id) {
    char sql[512];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO region (name, capital_region, population_region, 
"
             "area_region, country_id) "
             "VALUES ('%s', '%s', %d, %.2f, %d);",
             name, capital, population, area, country_id);

    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, NULL, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return -1;
    }
    return 0;
}

// Получение списка регионов по ID страны
int db_get_regions(sqlite3 *db, int country_id) {
    char sql[512];
    snprintf(sql, sizeof(sql), 
             "SELECT id, name, capital_region, population_region, 
area_region "
             "FROM region WHERE country_id=%d;", 
             country_id);

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char *name = (const char *)sqlite3_column_text(stmt, 1);
        const char *capital = (const char *)sqlite3_column_text(stmt, 2);
        int population = sqlite3_column_int(stmt, 3);
        float area = sqlite3_column_double(stmt, 4);

        printf("ID: %d, Name: %s, Capital: %s, Population: %d, Area: 
%.2f\n",
               id, name, capital, population, area);
    }
    sqlite3_finalize(stmt);
    return 0;
}

// Получение средней популяции регионов страны
float db_avg_region_population(sqlite3 *db, int country_id) {
    char sql[256];
    snprintf(sql, sizeof(sql), 
             "SELECT AVG(population_region) FROM region "
             "WHERE country_id=%d;", 
             country_id);

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return -1.0f;
    }

    float avg = 0.0f;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        avg = sqlite3_column_double(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return avg;
}
