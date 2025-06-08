#include <iostream>
#include <vector>

using namespace std;

class SeatManager {
private:
    vector<bool> seats;

public:
    SeatManager(int totalSeats); 
    void displaySeats(); 
    bool bookSeat(int seatNumber); 
};


