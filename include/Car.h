#ifndef CAR_H
#define CAR_H
#include"Vehicle.h"
#include<string>
using namespace std;

class Car : public Vehicle{
    private:
        int numberDoor;
        string fuelType;
        bool isAC;
    public:
        Car(string lp, string b, string m, int y, double dr, int nd, string ft, string ia);
        int getNumberDoor() const;
        string getFuelType() const;
        bool getIsAC() const;
        void displayInfo() const override;
        double calculateRentFee(int days) const override;
};

#endif