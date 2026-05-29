#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H
#include "Vehicle.h"
#include <string>
using namespace std;

class Motorcycle : public Vehicle {
    private:
        double displacement;
        string type;
        bool hasSidecar;
    public:
        Motorcycle(string lp, string b, string m, int y, double dr, double dis, string t, string hs);
        double getDisplacement() const;
        string getType() const;
        bool getHasSidecar() const;
        void displayInfo() const override;
};
#endif