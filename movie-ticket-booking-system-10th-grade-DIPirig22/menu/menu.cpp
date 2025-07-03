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

void showBookingMenu(const std::string& username) {
    json moviesData;
    ifstream in("movies.json");
    if (!in.is_open()) return;
    try { in >> moviesData; }
    catch (...) { return; }
    in.close();

    if (moviesData.empty()) return;

    cout << "Please choose a city from the list below:\n";
    vector<string> cityList;
    for (auto it = moviesData.begin(); it != moviesData.end(); ++it) {
        cityList.push_back(it.key());
    }

    for (size_t i = 0; i < cityList.size(); ++i)
        cout << i + 1 << ". " << cityList[i] << "\n";

    int cityChoice;
    cin >> cityChoice;
    if (cityChoice < 1 || cityChoice > cityList.size()) return;
    string selectedCity = cityList[cityChoice - 1];


    cout << "Now choose a cinema in " << selectedCity << ":\n";
    const auto& cinemas = moviesData[selectedCity];
    vector<string> cinemaList;
    for (auto it = cinemas.begin(); it != cinemas.end(); ++it)
        cinemaList.push_back(it.key());

    for (size_t i = 0; i < cinemaList.size(); ++i)
        cout << i + 1 << ". " << cinemaList[i] << "\n";

    int cinemaChoice;
    cin >> cinemaChoice;
    if (cinemaChoice < 1 || cinemaChoice > cinemaList.size()) return;
    string selectedCinema = cinemaList[cinemaChoice - 1];

    const auto& movieArray = cinemas[selectedCinema];
    if (!movieArray.is_array() || movieArray.empty()) return;

    cout << "Select a movie playing at " << selectedCinema << ":\n";
    vector<json> movieList;
    for (size_t i = 0; i < movieArray.size(); ++i) {
        const json& movie = movieArray[i];
        if (movie.contains("title") && movie.contains("times")) {
            cout << movieList.size() + 1 << ". " << movie["title"] << "\n";
            movieList.push_back(movie);
        }
    }

    int movieChoice;
    cin >> movieChoice;
    if (movieChoice < 1 || movieChoice > movieList.size()) return;
    const json& selectedMovie = movieList[movieChoice - 1];

    const json& times = selectedMovie["times"];
    cout << "Choose a showtime for \"" << selectedMovie["title"] << "\":\n";
    for (size_t i = 0; i < times.size(); ++i)
        cout << i + 1 << ". " << times[i] << "\n";

    int timeChoice;
    cin >> timeChoice;
    if (timeChoice < 1 || timeChoice > times.size()) return;
    string selectedTime = times[timeChoice - 1];

    SeatManager seatManager(50);
    vector<int> bookedSeats;

    json allBookings;
    ifstream bin("bookings.json");
    if (bin.is_open()) {
        try { bin >> allBookings; }
        catch (...) {}
        bin.close();
    }

    if (allBookings.contains(username)) {
        for (const auto& b : allBookings[username]) {
            if (b["city"] == selectedCity && b["cinema"] == selectedCinema &&
                b["movie"] == selectedMovie["title"] && b["time"] == selectedTime) {
                for (const auto& s : b["seats"]) seatManager.occupySeat(s);
            }
        }
    }

    while (true) {
        seatManager.displaySeats();
        cout << "Enter seat number to book (0-49) or -1 to exit:" << endl;
        int seatNum;
        cin >> seatNum;
        if (seatNum == -1) break;
        if (seatManager.bookSeat(seatNum))
            bookedSeats.push_back(seatNum);
    }

    if (!bookedSeats.empty()) {
        json booking = {
            {"city", selectedCity},
            {"cinema", selectedCinema},
            {"movie", selectedMovie["title"]},
            {"time", selectedTime},
            {"seats", bookedSeats}
        };
        allBookings[username].push_back(booking);
        ofstream bout("bookings.json");
        bout << allBookings.dump(4);
        bout.close();
        cout << "Booking confirmed\n";
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