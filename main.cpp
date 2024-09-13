#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class Flight {
public:
    string date;
    string flightID;
    int seatsPerRow;
    map<string, string> prices;
    void showInfo(){
        cout << "Date:" << date << endl;
        cout << "Flight ID:" << flightID << endl;
        cout << "Number of seats per row:" << seatsPerRow << endl;
        cout << "Prices for different rows:" << endl;
        for (const auto& pair : prices) {
            cout << pair.first << ":" << pair.second << endl;
        }
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

    Flight getFlightInfo(string line, string word, string tokens[15], int counter) {
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
class Ticket {
private:
    string passengerName;
    int passengerID;
    string seat;
    string flightID;
    string date;

};
class Seat {
private:
    string flightID;
    int row;
    char place;
    bool isAvailable;

};
class ParserFromUser{};

void check(vector<Flight> flights) {
    string date;
    string flightNo;
    cout << "Input date of the flight" << endl;
    cin >> date;
    cout << "Input flight number" << endl;
    cin >> flightNo;
    for (int i = 0; i < flights.size(); i++){
        if (flights[i].date == date) {
            if (flights[i].flightID == flightNo) {
                flights[i].showInfo();
            }
        }
    }
}

int main() {
    ParserFromFile parser;
    vector<Flight> flights = parser.getRecords();
    flights[1].showInfo();
    string input;
    cout << "Enter operation to execute: " << endl;
    cout << "Enter 1 to check available places" << endl;
    cout << "Enter 2 to book a ticket" << endl;
    cout << "Enter 3 to return a ticket" << endl;
    cout << "Enter 4 to view the booking info" << endl;
    cout << "Enter 5 to view all of your booked tickets (per user)" << endl;
    cout << "Enter 6 to view all the booked tickets for the flight" << endl;
    cin >> input;
    switch (stoi(input)) {
        case 1:
            check(flights);
            break;
        case 2:
            cout << "book";
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
    }
    return 0;

}