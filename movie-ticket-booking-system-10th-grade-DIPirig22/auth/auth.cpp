#include "auth.h"
#include <iostream>

bool Auth::registerUser(const string& username, const string& password) {
    ifstream file("users.json");
    json users;

    
    if (file) {
        file >> users;
    }
    file.close();

    
    if (users.contains(username)) {
        cout << "User already exists!" << endl;
        return false;
    }

  
    users[username] = password;

    ofstream outFile("users.json");
    outFile << users.dump(4); 
    outFile.close();

    return true;
}

bool Auth::loginUser(const string& username, const string& password) {
    ifstream file("users.json");
    json users;


    if (file) {
        file >> users;
    }
    file.close();

    if (users.contains(username) && users[username] == password) {
        return true;
    }
    else {
        cout << "Invalid username or password!" << endl;
        return false;
    }
}

