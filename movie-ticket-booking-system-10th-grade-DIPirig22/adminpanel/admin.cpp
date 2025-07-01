#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../json/json.hpp"      
#include "admin.h"

using namespace std;
using json = nlohmann::json;

void loadMovies(json& data) {
    ifstream in("movies.json");
    if (in.is_open()) {
        try {
            in >> data;
        }
        catch (...) {
            cout << "Error: Failed to parse movies.json\n";
            data = json::object();
        }
        in.close();
    }
    else {
        data = json::object();
    }
}

void saveMovies(const json& data) {
    ofstream out("movies.json");
    if (!out) {
        cout << "Error: Cannot write to movies.json\n";
        return;
    }
    out << data.dump(4); 
    out.close();
    cout << "Changes saved.\n";
}

void displayAll(const json& data) {
    cout << "\nCinemas and Scheduled Movies:\n";

    for (auto it = data.begin(); it != data.end(); ++it) {
        const string& cinema = it.key();
        const auto& movieList = it.value();

        cout << "\n" << cinema << ":\n";

        for (const auto& movie : movieList) {
            if (!movie.contains("title") || !movie.contains("times")) {
                cout << "  - [Invalid movie entry]\n";
                continue;
            }

            cout << "  • " << movie["title"] << " — Showtimes: ";
            for (size_t i = 0; i < movie["times"].size(); ++i) {
                cout << movie["times"][i];
                if (i != movie["times"].size() - 1) cout << ", ";
            }
            cout << "\n";
        }
    }
}

void addMovie(json& data) {
    string cinema, title;
    cout << "Enter cinema name: ";
    getline(cin >> ws, cinema);

    cout << "Enter movie title: ";
    getline(cin >> ws, title);

    int count;
    cout << "How many showtimes to add? ";
    cin >> count;

    vector<string> times;
    for (int i = 0; i < count; ++i) {
        string t;
        cout << "Enter time " << i + 1 << ": ";
        cin >> t;
        times.push_back(t);
    }

    json movie;
    movie["title"] = title;
    movie["times"] = times;

    data[cinema].push_back(movie);

    cout << "Movie \"" << title << "\" added with showtimes.\n";
}

void removeMovie(json& data) {
    string cinema;
    cout << "Enter cinema name: ";
    getline(cin >> ws, cinema);

    if (!data.contains(cinema)) {
        cout << "Cinema \"" << cinema << "\" not found.\n";
        return;
    }

    auto& movies = data[cinema];
    if (movies.empty()) {
        cout << "No movies to remove in \"" << cinema << "\".\n";
        return;
    }

    cout << "Movies in \"" << cinema << "\":\n";
    for (size_t i = 0; i < movies.size(); ++i) {
        cout << i + 1 << ". " << movies[i] << "\n";
    }

    int index;
    cout << "Enter movie number to remove: ";
    cin >> index;

    if (index < 1 || index > static_cast<int>(movies.size())) {
        cout << "Invalid index.\n";
        return;
    }

    cout << "Removed \"" << movies[index - 1] << "\" from \"" << cinema << "\".\n";
    movies.erase(movies.begin() + index - 1);
}

void runAdminPanel() {
    json data;
    loadMovies(data);

    while (true) {
        cout << "\n--- Admin Panel ---\n";
        cout << "1. View all cinemas and movies\n";
        cout << "2. Add a movie\n";
        cout << "3. Remove a movie\n";
        cout << "4. Save and exit\n";
        cout << "Choose: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: displayAll(data); break;
        case 2: addMovie(data); break;
        case 3: removeMovie(data); break;
        case 4:
            saveMovies(data);
            return;
        default:
            cout << "Invalid option.\n";
        }
    }
}
