// AirlineReservationSystem.cpp (Final – Fixed Menu Input)
// Build: g++ -std=c++17 AirlineReservationSystem.cpp -o AirlineReservationSystem

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cctype>

using namespace std;

// -------------------- Passenger Node --------------------
struct Passenger {
    int passengerID;
    string flightID;
    string name;
    int age;
    string gender;
    string contact;
    int seatNumber;
    string foodPreference;
    Passenger* next;

    Passenger(int pid, const string& fID, const string& nm, int a, const string& g,
              const string& c, int seat, const string& food)
        : passengerID(pid), flightID(fID), name(nm), age(a), gender(g),
          contact(c), seatNumber(seat), foodPreference(food), next(nullptr) {}

    void display() const {
        cout << "ID: " << passengerID
             << " | Flight: " << flightID
             << " | Name: " << name
             << " | Age: " << age
             << " | Gender: " << gender
             << " | Contact: " << contact
             << " | Seat: " << seatNumber
             << " | Food: " << foodPreference << '\n';
    }
};

// -------------------- Flight Class --------------------
class Flight {
public:
    string flightID;
    string airline;
    string origin, destination;
    string departureTime, arrivalTime;
    int totalSeats;
    double costPerSeat;
    vector<bool> seatBooked;

    Flight() : totalSeats(0), costPerSeat(0.0) {}
    Flight(const string& id, const string& air, const string& orig, const string& dest,
           const string& dep, const string& arr, int seats, double cost)
        : flightID(id), airline(air), origin(orig), destination(dest),
          departureTime(dep), arrivalTime(arr), totalSeats(seats), costPerSeat(cost) {
        seatBooked.assign(max(0, totalSeats) + 1, false);
    }

    void displaySummary() const {
        cout << flightID << " | " << airline << " | " << origin << " -> " << destination
             << " | Dep: " << departureTime << " | Arr: " << arrivalTime
             << " | Seats: " << totalSeats << " | Fare: " << costPerSeat << '\n';
    }

    void displaySeatMap() const {
        cout << "Seat map for flight " << flightID << " (1 = booked, 0 = free):\n";
        if (totalSeats <= 0) { cout << "  No seats configured.\n"; return; }
        for (int i = 1; i <= totalSeats; ++i) {
            cout << setw(3) << i << ":" << (seatBooked[i] ? '1' : '0')
                 << (i % 10 == 0 ? '\n' : ' ');
        }
        cout << '\n';
    }

    bool isSeatAvailable(int seat) const {
        if (seat < 1 || seat > totalSeats) return false;
        return !seatBooked[seat];
    }

    bool bookSeat(int seat) {
        if (!isSeatAvailable(seat)) return false;
        seatBooked[seat] = true;
        return true;
    }

    bool cancelSeat(int seat) {
        if (seat < 1 || seat > totalSeats) return false;
        if (!seatBooked[seat]) return false;
        seatBooked[seat] = false;
        return true;
    }

    int availableSeatCount() const {
        int cnt = 0;
        for (int i = 1; i <= totalSeats; ++i)
            if (!seatBooked[i]) ++cnt;
        return cnt;
    }
};

// -------------------- Reservation System --------------------
class ReservationSystem {
private:
    vector<Flight> flights;
    Passenger* head;
    int nextPassengerID;

    const string flightsFile = "flights.txt";
    const string passengersFile = "passengers.txt";
    const string nextIdFile = "next_id.txt";

public:
    ReservationSystem() : head(nullptr), nextPassengerID(1) {
        loadNextID();
        loadFlights();
        loadPassengers();
    }

    ~ReservationSystem() {
        saveNextID();
        clearPassengerList();
    }

    void clearPassengerList() {
        Passenger* cur = head;
        while (cur) {
            Passenger* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = nullptr;
    }

    // -------------------- File I/O --------------------
    void loadNextID() {
        ifstream fin(nextIdFile);
        if (fin.is_open()) fin >> nextPassengerID;
        else nextPassengerID = 1;
    }

    void saveNextID() {
        ofstream fout(nextIdFile);
        fout << nextPassengerID;
    }

    void loadFlights() {
        flights.clear();
        ifstream fin(flightsFile);
        if (!fin.is_open()) {
            addSampleFlights();
            saveFlights();
            return;
        }
        string line;
        while (getline(fin, line)) {
            if (line.empty()) continue;
            vector<string> parts = split(line, '|');
            if (parts.size() < 8) continue;
            trimAll(parts);
            int seats = stoi(parts[6]);
            double cost = stod(parts[7]);
            flights.emplace_back(parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], seats, cost);
        }
    }

    void saveFlights() {
        ofstream fout(flightsFile);
        for (const Flight& f : flights) {
            fout << f.flightID << '|' << f.airline << '|' << f.origin << '|' << f.destination
                 << '|' << f.departureTime << '|' << f.arrivalTime << '|' << f.totalSeats
                 << '|' << f.costPerSeat << '\n';
        }
    }

    void loadPassengers() {
        clearPassengerList();
        ifstream fin(passengersFile);
        if (!fin.is_open()) return;

        string line;
        while (getline(fin, line)) {
            if (line.empty()) continue;
            vector<string> parts = split(line, '|');
            if (parts.size() < 8) continue;
            trimAll(parts);
            int pid = stoi(parts[0]);
            int age = stoi(parts[3]);
            int seat = stoi(parts[6]);
            Passenger* p = new Passenger(pid, parts[1], parts[2], age, parts[4], parts[5], seat, parts[7]);
            appendPassengerNode(p);
            Flight* ff = findFlightByID(parts[1]);
            if (ff && seat >= 1 && seat <= ff->totalSeats)
                ff->seatBooked[seat] = true;
        }
    }

    void savePassengers() {
        ofstream fout(passengersFile);
        Passenger* cur = head;
        while (cur) {
            fout << cur->passengerID << '|' << cur->flightID << '|' << escapePipe(cur->name)
                 << '|' << cur->age << '|' << cur->gender << '|' << cur->contact << '|'
                 << cur->seatNumber << '|' << escapePipe(cur->foodPreference) << '\n';
            cur = cur->next;
        }
    }

    // -------------------- Utilities --------------------
    static vector<string> split(const string& s, char delim) {
        vector<string> out; string cur;
        for (char ch : s) {
            if (ch == delim) { out.push_back(cur); cur.clear(); }
            else cur.push_back(ch);
        }
        out.push_back(cur);
        return out;
    }

    static void trimAll(vector<string>& v) {
        for (string& s : v) {
            s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char c){return !isspace(c);} ));
            s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char c){return !isspace(c);} ).base(), s.end());
        }
    }

    static string escapePipe(const string& s) {
        string r = s;
        for (char &c : r) if (c == '|') c = '/';
        return r;
    }

    Flight* findFlightByID(const string& id) {
        for (auto &f : flights) if (f.flightID == id) return &f;
        return nullptr;
    }

    void appendPassengerNode(Passenger* node) {
        if (!head) head = node;
        else {
            Passenger* cur = head;
            while (cur->next) cur = cur->next;
            cur->next = node;
        }
    }

    Passenger* findPassengerByID(int pid, Passenger** prevOut = nullptr) {
        Passenger* cur = head;
        Passenger* prev = nullptr;
        while (cur) {
            if (cur->passengerID == pid) {
                if (prevOut) *prevOut = prev;
                return cur;
            }
            prev = cur;
            cur = cur->next;
        }
        return nullptr;
    }

    // -------------------- Sample Data --------------------
    void addSampleFlights() {
        flights.push_back(Flight("F100", "AirWave", "Pune", "Mumbai", "08:00", "09:10", 30, 1500));
        flights.push_back(Flight("F200", "SkyHigh", "Delhi", "Mumbai", "09:30", "11:30", 40, 3500));
        flights.push_back(Flight("F300", "BlueAir", "Chennai", "Bengaluru", "06:45", "07:55", 25, 1200));
    }

    // -------------------- Core Operations --------------------
    void listAllFlights() {
        cout << "\n--- Available Flights ---\n";
        for (const Flight& f : flights) f.displaySummary();
        cout << '\n';
    }

    void viewFlightDetails() {
        cout << "Enter Flight ID: ";
        string fid; getline(cin, fid);
        Flight* f = findFlightByID(fid);
        if (!f) { cout << "Flight not found.\n"; return; }
        f->displaySummary();
        cout << "Available seats: " << f->availableSeatCount() << '\n';
        f->displaySeatMap();
        displayPassengersByFlight(fid);
    }

    void displayPassengersByFlight(const string& fid) {
        cout << "\nPassengers on flight " << fid << ":\n";
        bool any = false;
        Passenger* cur = head;
        while (cur) {
            if (cur->flightID == fid) {
                cur->display();
                any = true;
            }
            cur = cur->next;
        }
        if (!any) cout << "  (none)\n";
    }

    void viewAllPassengers() {
        cout << "\n--- All Passengers ---\n";
        if (!head) { cout << "No passengers found.\n"; return; }
        Passenger* cur = head;
        while (cur) { cur->display(); cur = cur->next; }
    }

    void addFlightInteractive() {
        cout << "Add new flight (admin):\n";
        string id, air, orig, dest, dep, arr; int seats; double fare;
        cout << "Flight ID: "; getline(cin, id);
        cout << "Airline name: "; getline(cin, air);
        cout << "Origin: "; getline(cin, orig);
        cout << "Destination: "; getline(cin, dest);
        cout << "Departure time: "; getline(cin, dep);
        cout << "Arrival time: "; getline(cin, arr);
        cout << "Total seats: "; cin >> seats;
        cout << "Cost per seat: "; cin >> fare;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        flights.emplace_back(id, air, orig, dest, dep, arr, seats, fare);
        saveFlights();
        cout << "Flight added.\n";
    }

    void bookTicketsInteractive() {
        cout << "Enter Flight ID to book: ";
        string fid; getline(cin, fid);
        Flight* f = findFlightByID(fid);
        if (!f) { cout << "Flight not found.\n"; return; }

        int avail = f->availableSeatCount();
        if (avail == 0) { cout << "No seats available.\n"; return; }

        cout << "Available seats: " << avail << '\n';
        f->displaySeatMap();
        cout << "How many passengers to book? ";
        int num; cin >> num;
        if (num <= 0) {cin.ignore(numeric_limits<streamsize>::max(), '\n'); return;}
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        double totalBill = 0.0;
        for (int i = 0; i < num; ++i) {
            cout << "\n--- Passenger " << (i+1) << " ---\n";
            string name, gender, contact, food;
            int age, seat;

            cout << "Name: "; getline(cin, name);
            cout << "Age: "; cin >> age; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Gender: "; getline(cin, gender);
            cout << "Contact: "; getline(cin, contact);

            // Validate seat
            do {
                cout << "Choose seat number (1.." << f->totalSeats << "): ";
                cin >> seat; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (!f->isSeatAvailable(seat)) {
                    cout << "Seat invalid or taken. Try again.\n";
                } else break;
            } while (true);

            cout << "Food preference: "; getline(cin, food);

            int pid = nextPassengerID++;
            Passenger* p = new Passenger(pid, fid, name, age, gender, contact, seat, food);
            f->bookSeat(seat);
            appendPassengerNode(p);
            totalBill += f->costPerSeat;
        }

        savePassengers();
        saveFlights();
        saveNextID();

        cout << "\nBooking completed. Total bill: " << totalBill << '\n';
    }

    void cancelReservationInteractive() {
        cout << "Enter Passenger ID to cancel: ";
        string pidStr; getline(cin, pidStr);
        int pid = stoi(pidStr);
        Passenger* prev = nullptr;
        Passenger* p = findPassengerByID(pid, &prev);
        if (!p) { cout << "Passenger not found.\n"; return; }
        Flight* f = findFlightByID(p->flightID);
        if (f) f->cancelSeat(p->seatNumber);
        if (!prev) head = p->next; else prev->next = p->next;
        delete p;
        savePassengers();
        saveFlights();
        cout << "Cancelled reservation.\n";
    }

    // -------------------- Menu --------------------
    void mainMenu() {
        while (true) {
            cout << "\n===== Airline Reservation System =====\n";
            cout << "1. List All Flights\n";
            cout << "2. View Flight Details\n";
            cout << "3. Book Ticket(s)\n";
            cout << "4. Cancel Reservation\n";
            cout << "5. View All Passengers\n";
            cout << "6. Add Flight (admin)\n";
            cout << "7. Exit\n";
            cout << "Enter choice: ";

            string choiceStr;
            getline(cin, choiceStr);
            if (choiceStr.empty()) continue;

            int choice = 0;
            try { choice = stoi(choiceStr); }
            catch (...) { cout << "Invalid choice.\n"; continue; }

            switch (choice) {
                case 1: listAllFlights(); break;
                case 2: viewFlightDetails(); break;
                case 3: bookTicketsInteractive(); break;
                case 4: cancelReservationInteractive(); break;
                case 5: viewAllPassengers(); break;
                case 6: addFlightInteractive(); break;
                case 7:
                    savePassengers(); saveFlights(); saveNextID();
                    cout << "Exiting.\n"; return;
                default: cout << "Invalid choice.\n";
            }
        }
    }
};

// -------------------- main --------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ReservationSystem system;
    system.mainMenu();
    return 0;
}







// g++ -std=c++17 AirlineReservationSystem.cpp -o AirlineReservationSystem
// ./AirlineReservationSystem

// 1

// 2
// F100

// 3
// F100
// 1
// harsh 
// 23
// male 
// 67625637
// 5
// veg

// 5

// 4
// 1

// 7


