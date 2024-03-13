-- Keep a log of any SQL queries you execute as you solve the mystery.

-- read description of the crime
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

-- The description: |
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time
-- each of their interview transcripts mentions the bakery.
-- Littering took place at 16:36. No known witnesses.

-- read the interview
SELECT name, transcript
FROM interviews
WHERE month = 7 AND day = 28 AND transcript LIKE '%bakery%';

-- Interview results:

-- Ruth said:
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.


-- Eugene said:
-- I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- Raymond said:
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.


-- watch the bakery sercurity log, search for the cars around 10 minitues after the thief
-- find people with those plate -> suspect
WITH lisence AS (
    SELECT name, phone_number, passport_number
    FROM people
    WHERE license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE month = 7 AND day = 28
        AND HOUR = 10
        AND minute > 15 AND minute < 26
        AND activity = 'exit'
    )
),

-- See if anyone withdraw money on that day, on Leggett Street

atm AS(
    SELECT name, phone_number, passport_number
    FROM people
    WHERE id IN(
        SELECT person_id FROM bank_accounts
        WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE atm_location ='Leggett Street' and month = 7 AND day = 28
        )
    )
),

-- See if anyone make a phone call in that time, and duration less than 1 mintues

phone AS(
    SELECT name, phone_number, passport_number
    FROM people
    WHERE phone_number IN (
        SELECT caller FROM phone_calls
        WHERE month = 7 AND day = 28 AND duration <= 60
    )
),

-- search for passenger of the earliest flight out on next morning
run AS(
    SELECT name, phone_number, passport_number
    FROM people
    WHERE passport_number IN (
        SELECT passport_number FROM passengers
        WHERE flight_id = (
            SELECT id
            FROM flights
            WHERE month = 7 AND day = 29
            ORDER BY hour ASC
            LIMIT 1
        )
    )
)

SELECT phone.name, phone.phone_number, phone.passport_number
FROM phone
JOIN atm ON phone.phone_number = atm.phone_number
JOIN lisence ON phone.phone_number = lisence.phone_number
JOIN run ON phone.phone_number = run.phone_number;
--results:
-- +-------+----------------+-----------------+
-- | name  |  phone_number  | passport_number |
-- +-------+----------------+-----------------+
-- | Bruce | (367) 555-5533 | 5773159633      |
-- +-------+----------------+-----------------+

-- Mr.Bruce is the thief, not cool -> try to find his friend, who receive his phone call
-- that person bought 2 ticket, on the same flight as him

SELECT name, phone_number, passport_number
    FROM people
    WHERE phone_number IN (
        SELECT receiver FROM phone_calls
        WHERE month = 7 AND day = 28 AND duration <= 60 AND caller = '(367) 555-5533'
    );
-- results:
-- +-------+----------------+-----------------+
-- | name  |  phone_number  | passport_number |
-- +-------+----------------+-----------------+
-- | Robin | (375) 555-8161 | NULL            |
-- +-------+----------------+-----------------+

-- Where they're going:

SELECT * FROM airports
WHERE id = (
    SELECT destination_airport_id
    FROM flights
    WHERE month = 7 AND day = 29
    ORDER BY hour ASC
    LIMIT 1
);
