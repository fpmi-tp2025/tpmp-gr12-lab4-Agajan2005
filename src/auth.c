#include <stdio.h>
#include <string.h>
#include "auth.h"
#include "database.h"

int login(const char *username, const char *password) {
    return db_auth_user(username, password);
}

int register_user(const char *username, const char *password) {
    return db_create_user(username, password);
}