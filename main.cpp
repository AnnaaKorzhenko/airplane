#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

class Record {
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

class ParserFromFile {
public:
    void getRecords() {
        ifstream inputFile("C:/!uni/programing-paradigms/airplane/input.txt");
        if (!inputFile.is_open()) {
            cerr << "Error opening the file!" << endl;
        }
        string line;
        string word;
        string tokens[15];
        int counter = 0;
        while (getline(inputFile, line)) {
            Record record = getFlightInfo(line, word, tokens, counter);
        }
        inputFile.close();
    }

    Record getFlightInfo(string line, string word, string tokens[15], int counter) {
        stringstream ss(line);
        while (ss >> word) {
            tokens[counter] = word;
            counter++;
        }
        Record record;
        record.date = tokens[0];
        record.flightID = tokens[1];
        record.seatsPerRow = stoi(tokens[2]);
        for (int i = 3; i < counter; i=i+2) {
            string key = tokens[i];
            record.prices[key] = tokens[i+1];
        }
        record.showInfo();
        return record;
    }
    /*Record getFlightInfo() {
        ifstream inputFile("C:/!uni/programing-paradigms/airplane/input.txt");
        if (!inputFile.is_open()) {
            cerr << "Error opening the file!" << endl;
        }
        string line;
        string word;
        string tokens[15];
        int counter = 0;

        while (getline(inputFile, line)) {
            stringstream ss(line);
            while (ss >> word) {
                tokens[counter] = word;
                counter++;
            }
            Record record;
            record.date = tokens[0];
            record.flightID = tokens[1];
            record.seatsPerRow = stoi(tokens[2]);
            for (int i = 3; i < counter; i=i+2) {
                string key = tokens[i];
                record.prices[key] = tokens[i+1];
            }
            record.showInfo();

        }
        inputFile.close();
    }*/
};

class Flight: Record {
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
class ParserFromUser{};


int main() {
    ParserFromFile parser;
    parser.getRecords();
    return 0;

}