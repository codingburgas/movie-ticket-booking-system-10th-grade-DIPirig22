#include "menu.h"
#include "../menu/seat.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "../json/json.hpp"
#include <fstream>
using json = nlohmann::json;
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
    vector<int> bookedSeats;

    std::ifstream inFile("bookings.json");
    if (inFile.is_open()) {
        try {
            json allBookings;
            inFile >> allBookings;
            inFile.close();

            if (allBookings.contains(username)) {
                for (const auto& booking : allBookings[username]) {
                    if (
                        booking["city"] == selectedCity &&
                        booking["cinema"] == selectedCinema &&
                        booking["movie"] == selectedMovie &&
                        booking["time"] == selectedTime
                        ) {
                        for (const auto& seat : booking["seats"]) {
                            seatManager.occupySeat(seat);
                        }
                    }
                }
            }
        }
        catch (...) {
            std::cout << "Failed to load bookings.json\n";
        }
    }

    while (true) {
        seatManager.displaySeats();
        int seatNumber;
        cout << "Enter seat number to book (0-49) or -1 to finish: ";
        cin >> seatNumber;
        if (seatNumber == -1) break;

        if (seatManager.bookSeat(seatNumber)) {
            bookedSeats.push_back(seatNumber);
        }
    }

    cout << "\nBooking complete for user: " << username << "\n";

    if (!bookedSeats.empty()) {
        json allBookings;

        std::ifstream inFile("bookings.json");
        if (inFile.is_open()) {
            try {
                inFile >> allBookings;
            }
            catch (...) {
                std::cout << "Error reading bookings.json\n";
                allBookings = json::object();
            }
            inFile.close();
        }

        json newBooking = {
            {"city", selectedCity},
            {"cinema", selectedCinema},
            {"movie", selectedMovie},
            {"time", selectedTime},
            {"seats", bookedSeats}
        };

        allBookings[username].push_back(newBooking);

        std::ofstream outFile("bookings.json");
        if (outFile.is_open()) {
            outFile << allBookings.dump(4);
            outFile.close();
            std::cout << "\n Booking successfully saved\n";
        }
        else {
            std::cout << "Failed to write to bookings.json\n";
        }
    }
}




void viewUserBookings(const string& username) {
    ifstream file("bookings.json");
    if (!file) {
        cout << "No booking file found.\n";
        return;
    }

    json bookings;
    file >> bookings;
    file.close();

    if (!bookings.contains(username)) {
        cout << "You have no bookings yet.\n";
        return;
    }

    const auto& userBookings = bookings[username];

    cout << "\n Your Bookings:\n";
    for (const auto& entry : userBookings) {
        cout << "- City: " << entry["city"] << "\n";
        cout << "  Cinema: " << entry["cinema"] << "\n";
        cout << "  Movie: " << entry["movie"] << "\n";
        cout << "  Showtime: " << entry["time"] << "\n";
        cout << "  Seats: ";
        for (const auto& seat : entry["seats"]) {
            cout << seat << " ";
        }
        cout << "\n-----------------------------\n";
    }
}



void cancelUserBooking(const string& username) {
    std::ifstream inFile("bookings.json");
    if (!inFile.is_open()) {
        std::cout << "No booking file found.\n";
        return;
    }

    json allBookings;
    inFile >> allBookings;
    inFile.close();

    if (!allBookings.contains(username) || allBookings[username].empty()) {
        std::cout << "You have no bookings to cancel.\n";
        return;
    }

    auto& bookings = allBookings[username];

    std::cout << "\nYour Bookings:\n";
    for (size_t i = 0; i < bookings.size(); ++i) {
        const auto& entry = bookings[i];
        std::cout << i + 1 << ". " << entry["city"] << ", "
            << entry["cinema"] << ", " << entry["movie"]
            << " at " << entry["time"] << " — Seats: ";
        for (const auto& s : entry["seats"]) {
            std::cout << s << " ";
        }
        std::cout << "\n";
    }

    int cancelIndex;
    std::cout << "\nEnter the booking number to cancel (0 to exit): ";
    std::cin >> cancelIndex;
    if (cancelIndex < 1 || cancelIndex >(int)bookings.size()) {
        std::cout << "Cancel aborted.\n";
        return;
    }

    bookings.erase(bookings.begin() + cancelIndex - 1);

    if (bookings.empty()) {
        allBookings.erase(username);
    }

    std::ofstream outFile("bookings.json");
    outFile << allBookings.dump(4);
    outFile.close();

    std::cout << "\nBooking cancelled successfully.\n";
}