#include <iostream>
#include "auth/auth.h"
#include "menu/seat.cpp"

int main() {
    int choice;
    string username, password;

    while (true) {
        cout << "Choose an option:\n1. Register\n2. Log in\n3. Exit\n";
        cin >> choice;

        if (choice == 3) {
            cout << "Exiting program. Goodbye!" << endl;
            break;
        }

        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (choice == 1) {
            if (Auth::registerUser(username, password)) {
                cout << "Registration successful!" << endl;
            }
            else {
                cout << "Registration failed." << endl;
            }
        }
        else if (choice == 2) {
            if (Auth::loginUser(username, password)) {
                cout << "Login successful!" << endl;
                    SeatManager seatManager(50);

                    while (true) {
                        seatManager.displaySeats();

                        int seatNumber;
                        cout << "Enter seat number to book (0-49) or -1 to exit: ";
                        cin >> seatNumber;

                        if (seatNumber == -1) {
                            cout << "Exiting booking system.\n";
                            break;
                        }

                        seatManager.bookSeat(seatNumber);
                    }
                }
            else {
                cout << "Invalid username or password." << endl;
            }
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
