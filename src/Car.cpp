#include"Car.h"
#include<iostream>
Car::Car(string lp, string b, string m, int y, double dr, int nd, string ft, string ia):
    Vehicle(lp,b,m,y,dr), numberDoor(nd), fuelType(ft) {
        if(ia == "yes"){
            isAC = true;
        }else{
            isAC = false;
        }
    }
int Car::getNumberDoor() const{
    return numberDoor;
}
string Car::getFuelType() const{
    return fuelType;
}
bool Car::getIsAC() const{
    return isAC;
}
void Car::displayInfo() const{
    cout << "===== Car Information =====" << endl;
    cout << "License Plate: " << getLicensePlate() << endl;
    cout << "Brand: " << getBrand() << endl;
    cout << "Model: " << getModel() << endl;
    cout << "Year: " << getYear() << endl;
    cout << "Daily Rate: " << getDailyRate() << endl;
    cout << "Rental Status: " << (getIsRented() ? "Rented" : "Available") << endl;
    if (getIsRented()) {
        cout << "Renter Name: " << getRenterName() << endl;
    }
    cout << "Number of Doors: " << numberDoor << endl;
    cout << "Fuel Type: " << fuelType << endl;
    cout << "Air Conditioner: " << (isAC ? "Yes" : "No") << endl;
}
double Car::calculateRentFee(int days) const{
    return Vehicle::calculateRentFee(days) + days * (isAC * 100);
}
