CREATE TABLE user (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username VARCHAR(50),
    password_hash VARCHAR(128)
);

CREATE TABLE country (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(100),
    capital VARCHAR(100),
    language VARCHAR(50),
    population_country INTEGER,
    square_country FLOAT,
    currency VARCHAR(50),
    head_country VARCHAR(100)
);

CREATE TABLE region (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(100),
    capital_region VARCHAR(100),
    population_region INTEGER,
    square_region FLOAT,
    country_id INTEGER,
    FOREIGN KEY (country_id) REFERENCES country(id)
);

-- Начальные данные для стран и регионов
INSERT INTO country (name, capital, language, population_country, 
square_country, currency, head_country)
VALUES ('Беларусь', 'Минск', 'Беларуский', 9400000, 207600, 'BYN', 
'Александр Лукашенко'),
       ('Китай', 'Пекин', 'Китайский', 1400000000, 9596961, 'CNY', 'Си 
Цзиньпин');

INSERT INTO region (name, capital_region, population_region, 
square_region, country_id)
VALUES ('Минская область', 'Минск', 1400000, 39800, 1),
       ('Гомельская область', 'Гомель', 1400000, 40400, 1);

-- Тестовый пользователь
INSERT INTO user (username, password_hash)
VALUES ('admin', '12345');

-- Добавление России
INSERT INTO country (name, capital, language, population_country, 
square_country, currency, head_country)
VALUES ('Россия', 'Москва', 'Русский', 145912025, 17098246, 'RUB', 
'Владимир Путин');

-- Добавление регионов России
INSERT INTO region (name, capital_region, population_region, 
square_region, country_id)
VALUES ('Московская область', 'Москва', 7523000, 44300, 3),
       ('Ленинградская область', 'Санкт-Петербург', 1818000, 83900, 3),
       ('Новосибирская область', 'Новосибирск', 2798000, 177800, 3);
