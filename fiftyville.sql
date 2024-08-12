-- Keep a log of any SQL queries you execute as you solve the mystery.

--Crime scene July 28, 2023 Humphrey Street
SELECT *
FROM crime_scene_reports
WHERE year = 2023
AND month = 7
AND day = 28
AND street = 'Humphrey Street';

--The bakery 3 witnesses
SELECT *
FROM interviews
WHERE year = 2023
AND month = 7
AND day = 28;

--Ruth: security footage parking lot 10 minutes time frame
SELECT *
FROM bakery_security_logs
WHERE year = 2023
AND month = 7
AND day = 28
AND hour = 10
AND minute BETWEEN 10 AND 25;

-- Check license plate
SELECT people.name, people.phone_number, people.passport_number, people.license_plate,bsl.activity, bsl.year, bsl.month, bsl.day, bsl.hour, bsl.minute
FROM bakery_security_logs bsl
JOIN people ON bsl.license_plate = people.license_plate
WHERE bsl.year = 2023
AND bsl.month = 7
AND bsl.day = 28
AND bsl.hour = 10
AND bsl.minute BETWEEN 10 AND 25;


--Eugene: ATM on Leggett Street
SELECT *
FROM atm_transactions
WHERE year = 2023
AND month = 7
AND day = 28
AND atm_location = 'Leggett Street';

-- Join atm_transactions, bank_accounts and people to get the names
SELECT atm.atm_location, atm.year, atm.month, atm.day, atm.atm_location, people.name
FROM atm_transactions   atm
JOIN bank_accounts ba ON atm.account_number = ba.account_number
JOIN people ON ba.person_id = people.id
WHERE atm.year = 2023
AND atm.month = 7
AND atm.day = 28
AND atm.transaction_type = 'withdraw'
AND atm.atm_location = 'Leggett Street';

--Raymond: phone call less than a minute to take the earliest flight out of Fiftyville tomorrow
SELECT *
FROM phone_calls
WHERE year = 2023
AND month = 7
AND day = 28
AND duration < 60;

--Join people and phone_calls to get the names
SELECT people.name, pc.caller, pc.receiver, pc.year, pc.month,pc.day, pc.duration
FROM phone_calls pc
JOIN people ON pc.caller = people.phone_number
WHERE pc.year = 2023
AND pc.month = 7
AND pc.day = 28
AND pc.duration < 60;

-- flight out of Fiftyville 2023/07/29
SELECT *
FROM flights
WHERE origin_airport_id IN
(
    SELECT id
    FROM airports
    WHERE full_name LIKE 'Fiftyville%'
)
AND year = 2023
AND month = 7
AND day = 29
ORDER BY hour ASC, minute ASC;

-- Join flights, airports to get originand destination of the firts flight on 2023/07/29
SELECT org.full_name AS 'origin_airpor',flights.year, flights.month, flights.day, flights.hour, flights.minute, dest.full_name AS 'destination_airport', dest.city
FROM flights
JOIN airports org ON flights.origin_airport_id = org.id
JOIN airports dest ON flights.destination_airport_id = dest.id
WHERE org.id = 8
AND flights.year = 2023
AND flights.month = 7
AND flights.day = 29
ORDER BY flights.hour ASC, flights.minute ASC;

-- Join passenger,flights (id = 36) and people to get the name
SELECT people.*
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE flights.id = 36;


--Combine queries
SELECT people.name
FROM bakery_security_logs bsl
JOIN people ON bsl.license_plate = people.license_plate
JOIN bank_accounts ba ON ba.person_id = people.id
JOIN atm_transactions atm ON atm.account_number = ba.account_number
JOIN phone_calls pc ON pc.caller = people.phone_number
WHERE bsl.year = 2023
AND bsl.month = 7
AND bsl.day = 28
AND bsl.hour = 10
AND bsl.minute BETWEEN 10 AND 25
AND atm.year = 2023
AND atm.month = 7
AND atm.day = 28
AND atm.transaction_type = 'withdraw'
AND atm.atm_location = 'Leggett Street'
AND pc.year = 2023
AND pc.month = 7
AND pc.day = 28
AND pc.duration < 60;

-- Look for the name of the previous query (Bruce & Dina) in the flight id = 36
SELECT people.name
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE passengers.flight_id = 36
AND people.name IN ('Bruce', 'Dina');

-- Bruce call 2023/07/28 less than 60 s
SELECT cal.name, pc.caller, rec.name, pc.receiver, pc.year, pc.month, pc.day, pc.duration
FROM phone_calls pc
JOIN people cal ON pc.caller = cal.phone_number
JOIN people rec ON pc.receiver = rec.phone_number
WHERE pc.year = 2023
AND pc.month = 7
AND pc.day = 28
AND pc.duration < 60
AND cal.name LIKE 'Bruce%';

--.schema
CREATE TABLE crime_scene_reports (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    street TEXT,
    description TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE interviews (
    id INTEGER,
    name TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    transcript TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE atm_transactions (
    id INTEGER,
    account_number INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    atm_location TEXT,
    transaction_type TEXT,
    amount INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE bank_accounts (
    account_number INTEGER,
    person_id INTEGER,
    creation_year INTEGER,
    FOREIGN KEY(person_id) REFERENCES people(id)
);
CREATE TABLE airports (
    id INTEGER,
    abbreviation TEXT,
    full_name TEXT,
    city TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE flights (
    id INTEGER,
    origin_airport_id INTEGER,
    destination_airport_id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    PRIMARY KEY(id),
    FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
    FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
);
CREATE TABLE passengers (
    flight_id INTEGER,
    passport_number INTEGER,
    seat TEXT,
    FOREIGN KEY(flight_id) REFERENCES flights(id)
);
CREATE TABLE phone_calls (
    id INTEGER,
    caller TEXT,
    receiver TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    duration INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE people (
    id INTEGER,
    name TEXT,
    phone_number TEXT,
    passport_number INTEGER,
    license_plate TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE bakery_security_logs (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    activity TEXT,
    license_plate TEXT,
    PRIMARY KEY(id)
);