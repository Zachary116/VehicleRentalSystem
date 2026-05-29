#ifndef VEHICLE_H
#define VEHICLE_H
#include <string>
using namespace std;

class Vehicle {
    private:
        string licensePlate;
        string brand;
        string model;
        int year;
        double dailyRate;
        bool isRented;
        string renterName;
    public:
        Vehicle(string lp, string b, string m, int y, double dr);
        string getLicensePlate() const;
        string getBrand() const;
        string getModel() const;
        int getYear() const;
        double getDailyRate() const;
        bool getIsRented() const;
        string getRenterName() const;
        void setBrand(string b);
        void setModel(string m);
        void setYear(int y);
        void setDailyRate(double dr);
        void rentVehicle(string rn);
        void returnVehicle();
        virtual void displayInfo() const = 0;
        virtual double calculateRentFee(int days) const;
        virtual ~Vehicle();
};
#endif