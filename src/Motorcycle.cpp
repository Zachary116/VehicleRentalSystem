#include "Motorcycle.h"
#include <iostream>
using namespace std;
Motorcycle::Motorcycle(string lp, string b, string m, int y, double dr,
                       double dis, string t, string hs)
    : Vehicle(lp, b, m, y, dr), displacement(dis), type(t) {
    if (hs == "yes") {
        hasSidecar = true;
    } else {
        hasSidecar = false;
    }
}
double Motorcycle::getDisplacement() const {
    return displacement;
}
string Motorcycle::getType() const {
    return type;
}
bool Motorcycle::getHasSidecar() const {
    return hasSidecar;
}
void Motorcycle::displayInfo() const {
    cout << "===== Motorcycle Information =====" << endl;
    cout << "License Plate: " << getLicensePlate() << endl;
    cout << "Brand: " << getBrand() << endl;
    cout << "Model: " << getModel() << endl;
    cout << "Year: " << getYear() << endl;
    cout << "Daily Rate: " << getDailyRate() << endl;
    cout << "Rental Status: " << (getIsRented() ? "Rented" : "Available") << endl;
    if (getIsRented()) {
        cout << "Renter Name: " << getRenterName() << endl;
    }
    cout << "Displacement: " << displacement << " cc" << endl;
    cout << "Type: " << type << endl;
    cout << "Sidecar: " << (hasSidecar ? "Yes" : "No") << endl;
}
