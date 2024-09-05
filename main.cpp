#include <iostream>
#include <string>
using namespace std;

class Flight {
private:
    string flightID;
    int seatsPerRow;
    string date;
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
class ParserFromBase{};
class ParserFromUser{};


int main() {
    return 0;
}