#include "seat.h"
#include <iostream>
using namespace std;

SeatManager::SeatManager(int totalSeats) : seats(totalSeats, false) {}

void SeatManager::displaySeats() {
    cout << "\n🎭 Hall Seating Layout:\n";
    for (size_t i = 0; i < seats.size(); ++i) {
        if (i % 10 == 0) {
            int row = i / 10 + 1;
            string label = (row == 5) ? "25 lv (VIP)" : "15 lv";
            cout << "\nRow " << row << " [" << label << "]: ";
        }
        cout << "[" << i << (seats[i] ? "X" : "_") << "] ";
    }
    cout << "\n";
}

bool SeatManager::bookSeat(int seatNumber) {
    if (seatNumber < 0 || seatNumber >= (int)seats.size()) {
        cout << "⚠️ Invalid seat number! Try again.\n";
        return false;
    }
    if (seats[seatNumber]) {
        cout << "⛔️ Seat already booked! Choose another.\n";
        return false;
    }

    seats[seatNumber] = true;
    cout << "✅ Seat " << seatNumber << " booked successfully!\n";
    return true;
}

void SeatManager::occupySeat(int seatNumber) {
    if (seatNumber >= 0 && seatNumber < (int)seats.size()) {
        seats[seatNumber] = true;
    }
}



