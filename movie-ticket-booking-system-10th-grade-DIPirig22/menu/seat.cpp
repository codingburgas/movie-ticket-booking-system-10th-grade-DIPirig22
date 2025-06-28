#include "seat.h"

SeatManager::SeatManager(int totalSeats) : seats(totalSeats, false) {}


void SeatManager::displaySeats() {
    cout << "\nHall Seating Layout:\n";
    for (size_t i = 0; i < seats.size(); ++i) {
        if (i % 10 == 0) {
            int row = i / 10 + 1;
            string label;

            if (row == 5)
                label = "25 lv (VIP)";
            else
                label = "15 lv";

            cout << "\nRow " << row << " [" << label << "]: ";
        }
        cout << "[" << i << (seats[i] ? "X" : "_") << "] ";
    }
    cout << "\n";
}

bool SeatManager::bookSeat(int seatNumber) {
    if (seatNumber < 0 || seatNumber >= seats.size()) {
        cout << "Invalid seat number! Try again.\n";
        return false;
    }
    if (seats[seatNumber]) {
        cout << "Seat already booked! Choose another.\n";
        return false;
    }

    seats[seatNumber] = true;
    cout << "Seat " << seatNumber << " booked successfully!\n";
    return true;
}


