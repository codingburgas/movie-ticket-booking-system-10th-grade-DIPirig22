#include "seat.h"

SeatManager::SeatManager(int totalSeats) : seats(totalSeats, false) {}

void SeatManager::displaySeats() {
    cout << "Available Seats:\n";
    for (size_t i = 0; i < seats.size(); ++i) {
        cout << "[" << i << (seats[i] ? "X" : "_") << "] ";
        if ((i + 1) % 10 == 0) cout << endl;
    }
    cout << endl;
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


