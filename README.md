

# Airline Reservation System

A C++17 console-based application to manage flights, seat booking, and passenger records.
It simulates an airline booking workflow — allowing you to  list flights ,  book seats ,  cancel reservations , and  view passenger details  — all from the terminal.

---

## Features

*  Flight Management 

  * Add new flights (admin mode).
  * View all available flights.
  * See flight details, including seat map.

*  Passenger Management 

  * Book tickets with seat selection & food preferences.
  * View all passengers or passengers on a specific flight.
  * Cancel reservations using Passenger ID.

*  Seat Map 

  * Visual representation of booked (1) and available (0) seats.

*  Data Persistence 

  * Stores data in text files: `flights.txt`, `passengers.txt`, and `next_id.txt`.
  * Preserves data between program runs.

---

## Technologies

*  Language:  C++17
*  Concepts:  Object-Oriented Programming, Linked Lists, File Handling
*  Environment:  Works in VS Code, Code::Blocks, or any terminal compiler

---

## File Structure

| File                           | Purpose                                   |
| ------------------------------ | ----------------------------------------- |
| AirlineReservationSystem.cpp   | Main source code                          |
| flights.txt                    | Flight data (auto-generated if absent)    |
| passengers.txt                 | Passenger data (auto-generated if absent) |
| next_id.txt                    | Keeps track of Passenger IDs              |



## How to Compile and Run

1. Compile: 
     

g++ -std=c++17 AirlineReservationSystem.cpp -o AirlineReservationSystem


2. Run: 


./AirlineReservationSystem    # Linux / Mac


AirlineReservationSystem.exe  # Windows



## Menu Options

On running, you’ll see:


===== Airline Reservation System =====
1. List All Flights
2. View Flight Details
3. Book Ticket(s)
4. Cancel Reservation
5. View All Passengers
6. Add Flight (admin)
7. Exit



##  Example Data

 flights.txt (auto-generated) 

```
F100|AirWave|Pune|Mumbai|08:00|09:10|30|1500
F200|SkyHigh|Delhi|Mumbai|09:30|11:30|40|3500
F300|BlueAir|Chennai|Bengaluru|06:45|07:55|25|1200
```

 next_id.txt  (auto-generated) 
"1"


##  Future Improvements

* Switch from text files to an SQL database.
* Add a graphical user interface.
* Integrate authentication and payment simulation.

---

##  Author

*  Harsh Chavan
* GitHub: https://github.com/harsh8767


