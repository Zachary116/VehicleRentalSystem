#include "Vehicle.h"

Vehicle::Vehicle(string lp, string b, string m, int y, double dr)
    : licensePlate(lp), brand(b), model(m), year(y), dailyRate(dr) {
    isRented = false;
    renterName = "";
}
string Vehicle::getLicensePlate() const {
    return licensePlate;
}
string Vehicle::getBrand() const {
    return brand;
}
string Vehicle::getModel() const {
    return model;
}
int Vehicle::getYear() const {
    return year;
}
double Vehicle::getDailyRate() const {
    return dailyRate;
}
bool Vehicle::getIsRented() const {
    return isRented;
}
string Vehicle::getRenterName() const{
    return renterName;
}
void Vehicle::setBrand(string b){
    brand = b;
    return;
}
void Vehicle::setModel(string m){
    model = m;
    return;
}
void Vehicle::setYear(int y){
    year = y;
    return;
}
void Vehicle::setDailyRate(double dr){
    dailyRate = dr;
    return;
}
void Vehicle::rentVehicle(string rn){
    isRented = true;
    renterName = rn;
}
void Vehicle:: returnVehicle(){
    isRented = false;
    renterName = "";
}
double Vehicle::calculateRentFee(int days) const{
    return dailyRate * days;
}
Vehicle::~Vehicle() {}