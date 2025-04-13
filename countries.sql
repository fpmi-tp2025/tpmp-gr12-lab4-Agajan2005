-- Удаление таблиц, если они существуют
DROP TABLE IF EXISTS region;
DROP TABLE IF EXISTS country;

-- Создание таблицы country (страна)
CREATE TABLE country (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(100) NOT NULL,              -- Название страны
    capital VARCHAR(100) NOT NULL,           -- Столица
    language VARCHAR(50) NOT NULL,           -- Язык
    population_country INTEGER NOT NULL,     -- Население страны
    square_country FLOAT NOT NULL,           -- Площадь страны
    currency VARCHAR(50) NOT NULL,           -- Валюта
    head_country VARCHAR(100) NOT NULL       -- Глава государства
);

-- Создание таблицы region (регион)
CREATE TABLE region (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(100) NOT NULL,              -- Название региона
    capital_region VARCHAR(100) NOT NULL,    -- Столица региона
    population_region INTEGER NOT NULL,      -- Население региона
    square_region FLOAT NOT NULL,            -- Площадь региона
    country_id INTEGER NOT NULL,              -- Внешний ключ на таблицу country
    FOREIGN KEY (country_id) REFERENCES country(id)
);

-- Наполнение таблицы country данными
INSERT INTO country (name, capital, language, population_country, square_country, currency, head_country) VALUES
('Россия', 'Москва', 'Русский', 146000000, 17125191, 'Российский рубль (RUB)', 'Владимир Путин'),
('Туркменистан', 'Ашхабад', 'Туркменский', 6000000, 491210, 'Туркменский манат (TMT)', 'Сердар Бердымухамедов'),
('Япония', 'Токио', 'Японский', 125000000, 377975, 'Японская иена (JPY)', 'Фумио Кисида'),
('Беларусь', 'Минск', 'Белорусский, Русский', 9400000, 207600, 'Белорусский рубль (BYN)', 'Александр Лукашенко');

-- Наполнение таблицы region данными
INSERT INTO region (name, capital_region, population_region, square_region, country_id) VALUES
-- Регионы для России (country_id = 1)
('Московская область', 'Москва', 7500000, 44300, 1),
('Ленинградская область', 'Гатчина', 1800000, 83900, 1),
('Краснодарский край', 'Краснодар', 5600000, 75500, 1),
-- Регионы для Туркменистана (country_id = 2)
('Ахалский велаят', 'Ашхабад', 1000000, 97300, 2),
('Балканский велаят', 'Балканабат', 600000, 139400, 2),
('Марыйский велаят', 'Мары', 1700000, 87400, 2),
-- Регионы для Японии (country_id = 3)
('Префектура Токио', 'Токио', 14000000, 2194, 3),
('Префектура Осака', 'Осака', 8800000, 1905, 3),
('Префектура Хоккайдо', 'Саппоро', 5300000, 83424, 3),
-- Регионы для Беларуси (country_id = 4)
('Минская область', 'Минск', 1400000, 39800, 4),
('Брестская область', 'Брест', 1350000, 32700, 4),
('Гомельская область', 'Гомель', 1400000, 40400, 4);