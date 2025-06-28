#include "menu.h"
#include "../menu/seat.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

void showBookingMenu(const string& username) {
    map<string, vector<string>> cityMap = {
        {"Burgas", {"Galleria Burgas", "Cinema Neptun"}},
        {"Varna", {"Grand Mall Cinema", "Festival Complex"}},
        {"Sofia", {"Arena Mladost", "Cinema City"}},
        {"Plovdiv", {"Eccoplexx", "Kino Lucky"}},
        {"Ruse", {"Mall Ruse Cinema", "Euro Cinema"}}
    };

    map<string, vector<string>> movieMap = {
        {"Galleria Burgas", {"Avatar", "Dune"}},
        {"Cinema Neptun", {"Oppenheimer", "Inception"}},
        {"Grand Mall Cinema", {"The Batman", "Barbie"}},
        {"Festival Complex", {"Interstellar", "Avatar"}},
        {"Arena Mladost", {"Dune", "Matrix"}},
        {"Cinema City", {"Barbie", "Oppenheimer"}},
        {"Eccoplexx", {"Tenet", "Joker"}},
        {"Kino Lucky", {"Inception", "The Batman"}},
        {"Mall Ruse Cinema", {"Interstellar", "Avatar"}},
        {"Euro Cinema", {"Dune", "Oppenheimer"}}
    };

    map<string, vector<string>> showtimes = {
        {"Avatar", {"12:00", "15:00", "18:00"}},
        {"Dune", {"11:30", "14:30", "19:00"}},
        {"Oppenheimer", {"13:00", "17:30"}},
        {"Inception", {"16:00", "21:00"}},
        {"Barbie", {"10:30", "13:30", "17:00"}},
        {"Interstellar", {"11:00", "15:30"}},
        {"Tenet", {"14:15", "19:15"}},
        {"Joker", {"13:00", "18:45"}},
        {"Matrix", {"12:45", "18:00"}},
        {"The Batman", {"16:30", "20:30"}}
    };

    cout << "\nSelect a city:\n";
    int cityIndex = 1;
    vector<string> cities;
    for (const auto& pair : cityMap) {
        cout << cityIndex++ << ". " << pair.first << endl;
        cities.push_back(pair.first);
    }

    int cityChoice;
    cout << "Enter city number: ";
    cin >> cityChoice;
    if (cityChoice < 1 || cityChoice >(int)cities.size()) return;
    string selectedCity = cities[cityChoice - 1];

    const auto& cinemas = cityMap[selectedCity];
    cout << "\nCinemas in " << selectedCity << ":\n";
    for (size_t i = 0; i < cinemas.size(); ++i) {
        cout << i + 1 << ". " << cinemas[i] << endl;
    }

    int cinemaChoice;
    cout << "Enter cinema number: ";
    cin >> cinemaChoice;
    if (cinemaChoice < 1 || cinemaChoice >(int)cinemas.size()) return;
    string selectedCinema = cinemas[cinemaChoice - 1];

    const auto& movies = movieMap[selectedCinema];
    cout << "\nMovies in " << selectedCinema << ":\n";
    for (size_t i = 0; i < movies.size(); ++i) {
        cout << i + 1 << ". " << movies[i] << endl;
    }

    int movieChoice;
    cout << "Enter movie number: ";
    cin >> movieChoice;
    if (movieChoice < 1 || movieChoice >(int)movies.size()) return;
    string selectedMovie = movies[movieChoice - 1];

    const auto& times = showtimes[selectedMovie];
    cout << "\nShowtimes for " << selectedMovie << ":\n";
    for (size_t i = 0; i < times.size(); ++i) {
        cout << i + 1 << ". " << times[i] << endl;
    }

    int timeChoice;
    cout << "Enter showtime number: ";
    cin >> timeChoice;
    if (timeChoice < 1 || timeChoice >(int)times.size()) return;
    string selectedTime = times[timeChoice - 1];

    SeatManager seatManager(50);
    while (true) {
        seatManager.displaySeats();
        int seatNumber;
        cout << "Enter seat number to book (0-49) or -1 to exit: ";
        cin >> seatNumber;
        if (seatNumber == -1) break;
        seatManager.bookSeat(seatNumber);
    }

    cout << "\nBooking complete! Enjoy your movie, " << username << " ??\n";
}
