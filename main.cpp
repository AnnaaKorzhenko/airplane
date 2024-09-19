#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class Seat {
public:
    string flightID;
    int row;
    char place;
    mutable bool isAvailable;

    string getSeatInfo() const {
         return "Row: " + to_string(row) + ", Seat: " + place + ", Available: " + (isAvailable ? "Yes" : "No");
    }
    void initialize(const string& flightID, int row, char place, bool isAvailable) {
        this->flightID = flightID;
        this->row = row;
        this->place = place;
        this->isAvailable = isAvailable;
    }
};

class Ticket {
public:
    string passengerName;
    int ID;
    string seat;
    string flightID;
    string date;

    Ticket(const string& passengerName, int passengerID, const string& seat, const string& flightID, const string& date)
        : passengerName(passengerName), ID(passengerID), seat(seat), flightID(flightID), date(date) {}

    void showInfo() const {
        cout << "Passenger Name: " << passengerName << endl;
        cout << "Passenger ID: " << ID << endl;
        cout << "Seat: " << seat << endl;
        cout << "Flight ID: " << flightID << endl;
        cout << "Date: " << date << endl;
    }
};

class Flight {
public:
    string date;
    string flightID;
    int seatsPerRow;
    map<string, string> prices;
    vector<Seat> seats;
    vector<Ticket> bookedTickets;
    int rowsNumber;
    void showInfo() const{
        cout << "Date:" << date << endl;
        cout << "Flight ID:" << flightID << endl;
        cout << "Number of seats per row:" << seatsPerRow << endl;
        cout << "Prices for different rows:" << endl;
        for (const auto& pair : prices) {
            cout << pair.first << ":" << pair.second << endl;
        }

    }

    void initializeSeats() {
        seats.clear();
        string lastPair = prev(prices.end())->first;
        size_t index = lastPair.find('-');
        rowsNumber = stoi(lastPair.substr(index + 1));

        for (int row = 1; row <= rowsNumber; ++row) {
            for (char place = 'A'; place < 'A' + seatsPerRow; ++place) {
                Seat seat;
                seat.initialize(flightID, row, place, true);
                seats.push_back(seat);
            }
        }
    }

    void addTicket(const Ticket& ticket) {
        bookedTickets.push_back(ticket);
    }
};

class ParserFromFile:Flight{
public:
    vector<Flight> getRecords() {
        ifstream inputFile("C:/!uni/programing-paradigms/airplane/input.txt");
        if (!inputFile.is_open()) {
            cerr << "Error opening the file!" << endl;
        }
        string line;
        string word;
        string tokens[15];
        vector<Flight> flights;
        int counter = 0;
        while (getline(inputFile, line)) {
            Flight record = getFlightInfo(line, word, tokens, counter);
            flights.push_back(record);
        }
        inputFile.close();
        return flights;
    }

    static Flight getFlightInfo(const string& line, string word, string tokens[15], int counter) {
        stringstream ss(line);
        while (ss >> word) {
            tokens[counter] = word;
            counter++;
        }
        Flight record;
        record.date = tokens[0];
        record.flightID = tokens[1];
        record.seatsPerRow = stoi(tokens[2]);
        for (int i = 3; i < counter; i=i+2) {
            string key = tokens[i];
            record.prices[key] = tokens[i+1];
        }
        // record.showInfo();
        return record;
    }
};

void check(const vector<Flight>& flights) {
    string date;
    string flightNo;
    cout << "Input date of the flight" << endl;
    cin >> date;
    cout << "Input flight number" << endl;
    cin >> flightNo;
    for (const auto& flight :flights){
        if (flight.date == date && flight.flightID == flightNo){
            flight.showInfo();
            cout << "Available seats:" << endl;
            for (const auto& seat : flight.seats) {
                if (seat.isAvailable) {
                    cout << seat.row << seat.place << endl;
                }
            }
            return;
        }
    }
    cout << "No such a flight found" << endl;
}

void book(vector<Flight>& flights) {
    string date;
    string flightNo;
    int row;
    char place;
    string name;
    int ID;
    cout << "Input date of the flight" << endl;
    cin >> date;
    cout << "Input flight number" << endl;
    cin >> flightNo;
    cout << "Input the row you want to book at" << endl;
    cin >> row;
    cout << "Input the seat yo want to book" << endl;
    cin >> place;
    cout << "Input your name" << endl;
    cin >> name;
    cout << "Input your ID" << endl;
    cin >> ID;
    for (auto& flight :flights){
        if (flight.date == date && flight.flightID == flightNo){
            for (auto& seat : flight.seats) {
                if (seat.row == row && seat.place == place) {
                    if (seat.isAvailable) {
                        seat.isAvailable = false;
                        string seatStr = to_string(row) + "-" + place;
                        Ticket newTicket(name, ID, seatStr, flight.flightID, flight.date);
                        flight.addTicket(newTicket);
                        cout << "Seat " << row << place << " has been booked." << endl;
                    } else {
                        cout << "Seat " << row << place << " is not available." << endl;
                    }
                    return;
                }
            }
        }
    }
    cout << "Flight not found:(" << endl;
}

void returnSeat (vector<Flight>& flights) {
    string date;
    string flightNo;
    int row;
    char place;
    cout << "Input date of the flight" << endl;
    cin >> date;
    cout << "Input flight number" << endl;
    cin >> flightNo;
    cout << "Input the row of the seat you want to return" << endl;
    cin >> row;
    cout << "Input the seat you want to return" << endl;
    cin >> place;

    for (auto& flight : flights) {
        if (flight.date == date && flight.flightID == flightNo) {
            for (auto& seat : flight.seats) {
                if (seat.row == row && seat.place == place) {
                    if (!seat.isAvailable) {
                        seat.isAvailable = true;
                        cout << "Seat " << row << place << " has been returned." << endl;
                    } else {
                        cout << "Seat " << row << place << " is already available." << endl;
                    }
                    return;
                }
            }
        }
    }
    cout << "Flight not found:(" << endl;
}

void viewBookedTickets(const vector<Flight>& flights) {
    string date;
    string flightNo;
    cout << "Input date of the flight" << endl;
    cin >> date;
    cout << "Input flight number" << endl;
    cin >> flightNo;
    for (const auto& flight : flights) {
        if (flight.date == date && flight.flightID == flightNo) {
            cout << "Booked tickets for flight " << flight.flightID << " on " << flight.date << ":" << endl;
            for (const auto& ticket : flight.bookedTickets) {
                ticket.showInfo();
                cout << "------------------------" << endl;
            }
        }
    }
    cout << "Flight not found :(" << endl;
}


int main() {
    ParserFromFile parser;
    vector<Flight> flights = parser.getRecords();
    for (auto& flight : flights) {
        flight.initializeSeats();
    }
    flights[1].showInfo();
    bool toContinue = true;
    string choise;
    while (toContinue == true) {
        string input;
        cout << "Enter operation to execute: " << endl;
        cout << "Enter 1 to check available places" << endl;
        cout << "Enter 2 to book a ticket" << endl;
        cout << "Enter 3 to return a ticket" << endl;
        cout << "Enter 4 to view the booking info" << endl;
        cin >> input;
        switch (stoi(input)) {
            case 1:
                check(flights);
                break;
            case 2:
                book(flights);
                break;
            case 3:
                returnSeat(flights);
                break;
            case 4:
                viewBookedTickets(flights);
                break;
            default:
                cout << "Have a nice day!" << endl;
            break;
        }
        cout << "Do you want to continue? Y or N" << endl;
        cin >> choise;
        if (choise == "N") {
            toContinue = false;
        }
    }
    return 0;
}