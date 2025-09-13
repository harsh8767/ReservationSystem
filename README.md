

#  Airline Reservation System  

A lightweight **C++17 console application** that handles airline flight schedules, ticket booking, passenger records, and cancellations — all in one place.  
This project was built to practice **file handling** and **object-oriented programming** concepts while simulating a real-world airline reservation workflow.  

---

##  What It Does  

- **Manage Flights**  
  - View a list of all flights with departure/arrival details.  
  - Add new flights (admin mode).  
  - Show seat maps to check availability at a glance.  

- **Handle Passengers**  
  - Book tickets with custom seat selection and food preferences.  
  - View all passengers or just those on a specific flight.  
  - Cancel reservations quickly using Passenger ID.  

- **Data Persistence**  
  - All flights, passengers, and IDs are stored in simple text files, so your data survives after program restarts.  

---

##  Technologies Used  

- **Language:** C++17  
- **Core Concepts:** Classes, Linked Lists, File I/O  
- **Environment:** Works in VS Code, Code::Blocks, or any C++17-compatible compiler  

---

## Project Structure  

| File | Purpose |  
|-------|---------|  
| `AirlineReservationSystem.cpp` | Main program source code |  
| `flights.txt` | Stores flight data (auto-created if missing) |  
| `passengers.txt` | Stores passenger data (auto-created if missing) |  
| `next_id.txt` | Tracks Passenger IDs between runs |  

---

## How to Build and Run  

1. **Compile:**  

```
g++ -std=c++17 AirlineReservationSystem.cpp -o AirlineReservationSystem
````

2. **Run:**

```
./AirlineReservationSystem       # on Linux / Mac
AirlineReservationSystem.exe     # on Windows
```

---

## Menu Overview

When you start the program, you’ll see:

```
===== Airline Reservation System =====
1. List All Flights
2. View Flight Details
3. Book Ticket(s)
4. Cancel Reservation
5. View All Passengers
6. Add Flight (admin)
7. Exit
```

---

##  Screenshots

### Main Menu

![Main Menu](images/menu.png)

### Flights List

![Flights List](images/list-flights.png)

### Booking Tickets

![Booking Tickets](images/book-ticket.png)

### View Passengers

![View Passengers](images/view-passengers.png)

---

## 📄 Example Flight Data

If you don’t have a `flights.txt` file, the program will create one with sample data like:

```
F100|AirWave|Pune|Mumbai|08:00|09:10|30|1500
F200|SkyHigh|Delhi|Mumbai|09:30|11:30|40|3500
F300|BlueAir|Chennai|Bengaluru|06:45|07:55|25|1200
```

`next_id.txt` simply holds the next passenger ID (starts at 1).

---

## Future Ideas

* Store data in a database instead of text files.
* Add a GUI or a web front-end.
* Include authentication and mock payment handling.

---

## Author

Made by harsh8767 — (https://github.com/harsh8767)
---


