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

INSERT INTO country (name, capital, language, population_country, 
square_country, currency, head_country) VALUES
('Россия', 'Москва', 'Русский', 146000000, 17125191, 'Российский рубль 
(RUB)', 'Владимир Путин'),
('Туркменистан', 'Ашхабад', 'Туркменский', 6000000, 491210, 'Туркменский 
манат (TMT)', 'Сердар Бердымухамедов'),
('Япония', 'Токио', 'Японский', 125000000, 377975, 'Японская иена (JPY)', 
'Фумио Кисида'),
('Беларусь', 'Минск', 'Белорусский, Русский', 9400000, 207600, 
'Белорусский рубль (BYN)', 'Александр Лукашенко');

INSERT INTO region (name, capital_region, population_region, 
square_region, country_id) VALUES

('Московская область', 'Москва', 7500000, 44300, 1),
('Ленинградская область', 'Гатчина', 1800000, 83900, 1),
('Краснодарский край', 'Краснодар', 5600000, 75500, 1),

('Ахалский велаят', 'Ашхабад', 1000000, 97300, 2),
('Балканский велаят', 'Балканабат', 600000, 139400, 2),
('Марыйский велаят', 'Мары', 1700000, 87400, 2),

('Префектура Токио', 'Токио', 14000000, 2194, 3),
('Префектура Осака', 'Осака', 8800000, 1905, 3),
('Префектура Хоккайдо', 'Саппоро', 5300000, 83424, 3),

('Минская область', 'Минск', 1400000, 39800, 4),
('Брестская область', 'Брест', 1350000, 32700, 4),
('Гомельская область', 'Гомель', 1400000, 40400, 4);

INSERT INTO user (username, password_hash)
VALUES ('admin', '12345');
