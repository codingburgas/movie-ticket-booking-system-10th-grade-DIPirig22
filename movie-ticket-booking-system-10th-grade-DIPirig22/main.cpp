#include <iostream>
#include "auth/auth.h"
#include "menu/seat.cpp"
#include "menu/menu.h"



int main() {
    int choice;
    string username, password;

    while (true) {
        cout << "Welcome to the Cinema Booking System!" << endl;
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

                while (true) {
                    cout << "\nWhat would you like to do?\n";
                    cout << "1. Book a ticket\n";
                    cout << "2. View my bookings\n";
                    cout << "3. Cancel a booking\n";
                    cout << "4. Logout\n";
                    cin >> choice;

                    if (choice == 1) {
                        showBookingMenu(username);
                    }
                    else if (choice == 2) {
                        viewUserBookings(username); 
                    }
                    else if (choice == 3) {
                        cancelUserBooking(username);
                    }
                    else if (choice == 4) {
                        cout << "Logged out.\n";
                        break;
                    }
                    else {
                        cout << "Invalid choice.\n";
                    }
                }
            }
                    

        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
