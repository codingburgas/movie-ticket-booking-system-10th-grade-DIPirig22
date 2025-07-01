#include <iostream>
#include "auth/auth.h"
#include "menu/seat.cpp"
#include "menu/menu.h"
#include "adminpanel/admin.h"



int main() {
    while (true) {
        cout << "\nCinema Ticket Booking System\n";
        cout << "-----------------------------\n";
        cout << "1. Login as User\n";
        cout << "2. Register as User\n";
        cout << "3. Login as Admin\n";
        cout << "4. Exit\n";
        cout << "Select option: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            string username, password;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            if (Auth::loginUser(username, password)) {
                cout << "Login successful.\n";

                while (true) {
                    cout << "\nUser Menu:\n";
                    cout << "1. Book ticket\n";
                    cout << "2. View my bookings\n";
                    cout << "3. Cancel booking\n";
                    cout << "4. Logout\n";
                    cout << "Choose option: ";

                    int action;
                    cin >> action;

                    if (action == 1) showBookingMenu(username);
                    else if (action == 2) viewUserBookings(username);
                    else if (action == 3) cancelUserBooking(username);
                    else if (action == 4) {
                        cout << "Logged out.\n";
                        break;
                    }
                    else {
                        cout << "Invalid option.\n";
                    }
                }
            }
            else {
                cout << "Login failed. Incorrect username or password.\n";
            }

        }
        else if (choice == 2) {
            string username, password;
            cout << "Create username: ";
            cin >> username;
            cout << "Create password: ";
            cin >> password;

            if (Auth::registerUser(username, password)) {
                cout << "Registration successful.\n";
            }
            else {
                cout << "Registration failed. Username may already exist.\n";
            }

        }
        else if (choice == 3) {
            string adminPass;
            cout << "Enter admin password: ";
            cin >> adminPass;

            if (adminPass == "admin1") {
                runAdminPanel();
            }
            else {
                cout << "Incorrect admin password.\n";
            }

        }
        else if (choice == 4) {
            cout << "Goodbye!\n";
            break;

        }
        else {
            cout << "Invalid selection.\n";
        }
    }

    return 0;
}