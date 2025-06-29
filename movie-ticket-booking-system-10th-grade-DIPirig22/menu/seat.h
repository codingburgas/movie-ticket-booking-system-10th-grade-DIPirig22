#include <vector>

class SeatManager {
private:
    std::vector<bool> seats;
public:
    SeatManager(int totalSeats);
    void displaySeats();
    bool bookSeat(int seatNumber);
    void occupySeat(int seatNumber);
};



