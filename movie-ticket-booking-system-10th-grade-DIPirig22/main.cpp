#include <iostream>
#include "auth/auth.h"
#include "menu/menu.cpp"

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
                menu();
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
