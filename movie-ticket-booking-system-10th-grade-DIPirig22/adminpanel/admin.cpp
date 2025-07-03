#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../json/json.hpp"      

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
    map<string, vector<string>> cityMap = {
        {"Burgas", {"Galleria Burgas", "Cinema Neptun"}},
        {"Varna", {"Grand Mall Cinema", "Festival Complex"}},
        {"Sofia", {"Arena Mladost", "Cinema City"}},
        {"Plovdiv", {"Eccoplexx", "Kino Lucky"}},
        {"Ruse", {"Mall Ruse Cinema", "Euro Cinema"}}
    };

    cout << "\nSelect a city:\n";
    vector<string> cities;
    int cIdx = 1;
    for (const auto& pair : cityMap) {
        cout << cIdx++ << ". " << pair.first << "\n";
        cities.push_back(pair.first);
    }
    int cityChoice;
    cout << "City number: ";
    cin >> cityChoice;
    if (cityChoice < 1 || cityChoice > cities.size()) return;
    string selectedCity = cities[cityChoice - 1];

    const auto& cinemas = cityMap[selectedCity];
    cout << "\nCinemas in " << selectedCity << ":\n";
    for (size_t i = 0; i < cinemas.size(); ++i)
        cout << i + 1 << ". " << cinemas[i] << "\n";

    int cinemaChoice;
    cout << "Cinema number: ";
    cin >> cinemaChoice;
    if (cinemaChoice < 1 || cinemaChoice > cinemas.size()) return;
    string selectedCinema = cinemas[cinemaChoice - 1];

    string title;
    cout << "Enter movie title: ";
    getline(cin >> ws, title);

    int showCount;
    cout << "Number of showtimes: ";
    cin >> showCount;

    vector<string> times;
    for (int i = 0; i < showCount; ++i) {
        string time;
        cout << "Time " << i + 1 << ": ";
        cin >> time;
        times.push_back(time);
    }

    json movie;
    movie["title"] = title;
    movie["times"] = times;

    data[selectedCity][selectedCinema].push_back(movie);
    cout << "Movie added to " << selectedCinema << " in " << selectedCity << ".\n";
}


void removeMovie(json& data) {
    if (data.empty()) {
        cout << "No movies available.\n";
        return;
    }

    vector<string> cities;
    cout << "\nAvailable Cities:\n";
    for (auto it = data.begin(); it != data.end(); ++it) {
        cities.push_back(it.key());
        cout << cities.size() << ". " << it.key() << "\n";
    }

    int cityChoice;
    cout << "Select city: ";
    cin >> cityChoice;
    if (cityChoice < 1 || cityChoice > cities.size()) return;
    string selectedCity = cities[cityChoice - 1];

    const auto& cinemas = data[selectedCity];
    vector<string> cinemaList;
    cout << "\nCinemas in " << selectedCity << ":\n";
    for (auto it = cinemas.begin(); it != cinemas.end(); ++it) {
        cinemaList.push_back(it.key());
        cout << cinemaList.size() << ". " << it.key() << "\n";
    }

    int cinemaChoice;
    cout << "Select cinema: ";
    cin >> cinemaChoice;
    if (cinemaChoice < 1 || cinemaChoice > cinemaList.size()) return;
    string selectedCinema = cinemaList[cinemaChoice - 1];

    auto& movieArray = data[selectedCity][selectedCinema];
    if (!movieArray.is_array() || movieArray.empty()) {
        cout << "No movies in selected cinema.\n";
        return;
    }

    vector<string> titles;
    cout << "\nMovies in " << selectedCinema << ":\n";
    for (size_t i = 0; i < movieArray.size(); ++i) {
        const json& movie = movieArray[i];
        if (movie.contains("title")) {
            titles.push_back(movie["title"]);
            cout << i + 1 << ". " << movie["title"] << "\n";
        }
    }

    int movieChoice;
    cout << "Select movie to delete: ";
    cin >> movieChoice;
    if (movieChoice < 1 || movieChoice > titles.size()) return;

    movieArray.erase(movieArray.begin() + (movieChoice - 1));
    cout << "Movie deleted from " << selectedCinema << ", " << selectedCity << ".\n";

    if (movieArray.empty())
        data[selectedCity].erase(selectedCinema);
    if (data[selectedCity].empty())
        data.erase(selectedCity);
}

void removeCity(json& data) {
    if (data.empty()) {
        cout << "No cities to remove.\n";
        return;
    }

    vector<string> cities;
    cout << "Available Cities:\n";
    for (auto it = data.begin(); it != data.end(); ++it) {
        cities.push_back(it.key());
        cout << cities.size() << ". " << it.key() << "\n";
    }

    int choice;
    cout << "Select city to remove: ";
    cin >> choice;
    if (choice < 1 || choice > cities.size()) return;
    string selected = cities[choice - 1];

    data.erase(selected);
    cout << "City \"" << selected << "\" removed from schedule.\n";
}


void runAdminPanel() {
    json data;
    loadMovies(data);

    while (true) {
        cout << "\n--- Admin Panel ---\n";
        cout << "1. View all cinemas and movies\n";
        cout << "2. Add a movie\n";
        cout << "3. Remove a movie\n";
        cout << "4. Remove city and all its cinemas\n";
        cout << "5. Save and exit\n";
        cout << "Choose: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: displayAll(data); break;
        case 2: addMovie(data); break;
        case 3: removeMovie(data); break;
        case 4: removeCity(data); break;
        case 5:
            saveMovies(data);
            return;
        default:
            cout << "Invalid option.\n";
        }
    }

    if (data.empty()) {
        cout << "movies.json is empty\n";
        return;
    }

}
