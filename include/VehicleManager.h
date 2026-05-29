#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H
#include"Car.h"
#include"Motorcycle.h"
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<stdexcept>
using namespace std;

template<class T>
class VehicleManager{
    private:
        vector<T*> vehicles;
        map<string, T*> plateIndex;
        vector<string> splitline(string line){
            vector<string> fields;
            string field;
            stringstream ss(line);
            while(getline(ss,field,',')){
                fields.push_back(field);
            }
            return fields;
        }
    public:
        void addVehicleByInput(){
            cout << "Please choose vehicle type:" << endl;
            cout << "1. Car" << endl;
            cout << "2. Motorcycle" << endl;
            cout << "Please enter your choice: ";
            int type; cin >> type;
            if(type != 1 && type != 2){
                cout << "Invalid vehicle type!" << endl;
                return;
            }
            cout << "Please enter license plate: ";
            string lp; cin >> lp;
            if(plateIndex.find(lp) != plateIndex.end()){
                cout << "The license plate already exists!" << endl;
                return;
            }
            cout << "Please enter brand, model, year and daily rate: ";
            string b,m; int y; double dr;
            cin >> b >> m >> y >> dr;
            if(y <= 0 || dr <= 0){
                cout << "Invalid year or daily rate!" << endl;
                return;
            }
            if(type == 1){
                cout << "Please enter number of doors, fuel type and AC status(yes/no): ";
                int nd; string ft; string ia;
                cin >> nd >> ft >> ia;
                if(nd <= 0){
                    cout << "Invalid number of doors!" << endl;
                    return;
                }
                addVehicle(new Car(lp,b,m,y,dr,nd,ft,ia));
                cout << endl;
            }else if(type == 2){
                cout << "Please enter displacement, motorcycle type and sidecar status(yes/no): ";
                double dis; string t; string hs;
                cin >> dis >> t >> hs;
                if(dis <= 0){
                    cout << "Invalid displacement!" << endl;
                    return;
                }
                addVehicle(new Motorcycle(lp,b,m,y,dr,dis,t,hs));
                cout << endl;
            }
            return;
        }
        bool addVehicle(T* v){
            string plate = v->getLicensePlate();
            auto it = plateIndex.find(plate);
            if(it != plateIndex.end()){
                cout << "The vehicle already exists!" ;
                delete v;       //防止内存泄漏
                return false;
            }else{
                vehicles.push_back(v);
                plateIndex[plate] = v;
                cout << "Add vehicle successfully!";
                return true;
            }
        }
        void displayAllVehicle(){
            if(vehicles.empty()){
                cout << "System is empty!" << endl;
                return;
            }
            for(T* v : vehicles){
                v->displayInfo();
                cout << endl;
            }
        }
        void displayAvailableVehicle(){
            if(vehicles.empty()){
                cout << "System is empty!" << endl;
                return;
            }
            bool found = false;
            for(T* v : vehicles){
                if(v->getIsRented()) continue;
                v->displayInfo();
                cout << endl;
                found = true;
            }
            if(!found){
                cout << "No available vehicles!" << endl;
            }
        }
        void displayRentedVehicle(){
            if(vehicles.empty()){
                cout << "System is empty!" << endl;
                return;
            }
            bool found = false;
            for(T* v : vehicles){
                if(!v->getIsRented()) continue;
                v->displayInfo();
                cout << endl;
                found = true;
            }
            if(!found){
                cout << "No rented vehicles!" << endl;
            }
        }
        void rentVehicle(string plate, string rn, int days){
            if(days <= 0){
                cout << "Invalid days! Please input again!" << endl;
                return;
            }
            T* temp = searchVehicle(plate);
            if(temp == nullptr){
                cout << "Vehicle not find!" << endl;
                return;
            }
            if(temp->getIsRented()){
                cout << "The vehicle has been already rented! Please choose another!" << endl;
            }else{
                double fee = temp->calculateRentFee(days);
                temp->rentVehicle(rn);
                cout << "Renting successfully!" << endl;
                cout << "Total renting fee: " << fee << endl;
                cout << "Thank you for choosing us!" << endl;
            }
            return;
        }
        void returnVehicle(string plate){
            T* temp = searchVehicle(plate);
            if(temp == nullptr){
                cout << "Vehicle not find!" << endl;
                return;
            }
            if(temp->getIsRented()){
                temp->returnVehicle();
                cout << "Returning successfully!" << endl;
            }else{
                cout << "The vehicle has not been rented!" << endl;
            }
            return;
        }
        T* searchVehicle(string lp) const{
            auto it = plateIndex.find(lp);
            if(it == plateIndex.end()){
                return nullptr;
            }else{
                return it->second;
            }
        }
        void displayVehiclesByBrand(string brand) const{
            if(vehicles.empty()){
                cout << "System is empty!" << endl;
                return;
            }
            auto it = vehicles.begin();
            bool found = false;
            while(true){
                it = find_if(it, vehicles.end(),
                [brand](const T* v) {
                    return v->getBrand() == brand;
                });
                if(it == vehicles.end()){
                    break;
                }
                (*it)->displayInfo();
                cout << endl;
                found = true;
                it++;
            }
            if(!found){
                cout << "No vehicle with this brand!" << endl;
            }
        }
        bool removeVehicle(string lp) {
            T* target = searchVehicle(lp);
            if (target == nullptr) {
                cout << "Vehicle not find!" << endl;
                return false;
            }
            for (int i = 0; i < vehicles.size(); i++) {
                if (vehicles[i] == target) {
                    vehicles.erase(vehicles.begin() + i);
                    break;
                }
            }
            plateIndex.erase(lp);
            delete target;
            cout << "Vehicle removed successfully!" << endl;
            return true;
        }
        int getTotalVehicle() const{
            return vehicles.size();
        }
        int getAvailableVehicle() const{
            int available = count_if(vehicles.begin(), vehicles.end(),
            [](const T* vehicle) { return !vehicle->getIsRented(); });
            return available;
        }
        int getRentedVehicle() const{
            int rent = count_if(vehicles.begin(), vehicles.end(),
            [](const T* vehicle) { return vehicle->getIsRented(); });
            return rent;
        }
        double getTotalRate() const{
            double cnt = 0;
            for(T* v : vehicles){
                cnt += v->getDailyRate();
            }
            return cnt;
        }
        void updateVehicleInfo(){
            cout << "Please enter license plate: ";
            string lp; cin >> lp;
            T* temp = searchVehicle(lp);
            if(temp == nullptr){
                cout << "Vehicle not find!" << endl;
                return;
            }
            cout << "Please choose update item:" << endl;
            cout << "1. Brand" << endl;
            cout << "2. Model" << endl;
            cout << "3. Year" << endl;
            cout << "4. Daily Rate" << endl;
            cout << "Please enter your choice: ";
            int choice; cin >> choice;
            if(choice == 1){
                cout << "Please enter new brand: ";
                string brand; cin >> brand;
                temp->setBrand(brand);
                cout << "Update successfully!" << endl;
            }else if(choice == 2){
                cout << "Please enter new model: ";
                string model; cin >> model;
                temp->setModel(model);
                cout << "Update successfully!" << endl;
            }else if(choice == 3){
                cout << "Please enter new year: ";
                int year; cin >> year;
                if(year <= 0){
                    cout << "Invalid number!" << endl;
                    return;
                }
                temp->setYear(year);
                cout << "Update successfully!" << endl;
            }else if(choice == 4){
                cout << "Please enter new daily rate: ";
                double dailyRate; cin >> dailyRate;
                if(dailyRate <= 0){
                    cout << "Invalid number!" << endl;
                    return;
                }
                temp->setDailyRate(dailyRate);
                cout << "Update successfully!" << endl;
            }else{
                cout << "Invalid choice!" << endl;
            }
            return;
        }
        void displayStatistics() const{
            if(vehicles.empty()){
                cout << "System is empty!" << endl;
                return;
            }
            cout << "Total vehicles: " << getTotalVehicle() << endl;
            cout << "Available vehicles: " << getAvailableVehicle() << endl;
            cout << "Rented vehicles: " << getRentedVehicle() << endl;
            cout << "Total daily rate: " << getTotalRate() << endl;
            return;
        }
        bool sortByInput(string input){
            if(vehicles.empty()){
                cout << "System is empty!" << endl;
                return false;
            }
            if(input != "rate" && input != "year" && input != "brand" && input != "plate"){
                cout << "Invalid sort option!" << endl;
                return false;
            }
            sort(vehicles.begin(), vehicles.end(),
            [input](const T* a, const T* b) {
                if(input == "rate"){
                    return a->getDailyRate() < b->getDailyRate();
                }else if(input == "year"){
                    return a->getYear() < b->getYear();
                }else if(input == "brand"){
                    return a->getBrand() < b->getBrand();
                }else{
                    return a->getLicensePlate() < b->getLicensePlate();
                }
            });
            cout << "Sort successfully!" << endl;
            return true;
        }
        void loadFromFile(const string& filename){
            ifstream file(filename);
            if(!file.is_open()){
                throw runtime_error("File open failed!");
            }
            string line;
            while(getline(file,line)){
                vector<string> fields = splitline(line);
                if(fields.size() < 11){
                    cout << "Invalid line format!" << endl;
                    continue;
                }
                if(fields[0] == "Car"){
                    Car* car = new Car(fields[1], fields[2], fields[3], stoi(fields[4]), stod(fields[5]), stoi(fields[8]), fields[9], fields[10] == "1" ? "yes" : "no");
                    if(fields[6] == "1"){
                        car->rentVehicle(fields[7]);
                    }
                    string plate = car->getLicensePlate();
                    if(addVehicle(car)){
                        cout << "    " << "License plate: " << plate << endl;
                    }
                }else if(fields[0] == "Motorcycle"){
                    Motorcycle* motor = new Motorcycle(fields[1], fields[2], fields[3], stoi(fields[4]), stod(fields[5]), stod(fields[8]), fields[9], fields[10] == "1" ? "yes" : "no");
                    if(fields[6] == "1"){
                        motor->rentVehicle(fields[7]);
                    }
                    string plate = motor->getLicensePlate();
                    if(addVehicle(motor)){
                        cout << "    " << "License plate: " << plate << endl;
                    }
                }
            }
            file.close();
            return;
        }
        void saveToFile(const string& filename) const{
            if(vehicles.empty()){
                throw runtime_error("System is empty!");
            }
            ofstream file(filename);
            if(!file.is_open()){
                throw runtime_error("File open failed!");
            }
            for(T* v : vehicles){
                Car* car = dynamic_cast<Car*>(v);
                Motorcycle* motor = dynamic_cast<Motorcycle*>(v);
                if(car != nullptr){
                    file << "Car";
                    file << "," << car->getLicensePlate();
                    file << "," << car->getBrand();
                    file << "," << car->getModel();
                    file << "," << car->getYear();
                    file << "," << car->getDailyRate();
                    file << "," << car->getIsRented();
                    file << "," << car->getRenterName();
                    file << "," << car->getNumberDoor();
                    file << "," << car->getFuelType();
                    file << "," << car->getIsAC();
                }else if(motor != nullptr){
                    file << "Motorcycle";
                    file << "," << motor->getLicensePlate();
                    file << "," << motor->getBrand();
                    file << "," << motor->getModel();
                    file << "," << motor->getYear();
                    file << "," << motor->getDailyRate();
                    file << "," << motor->getIsRented();
                    file << "," << motor->getRenterName();
                    file << "," << motor->getDisplacement();
                    file << "," << motor->getType();
                    file << "," << motor->getHasSidecar();
                }
                file << endl;
            }
            file.close();
        } 
        ~VehicleManager() {
            for(auto& v : vehicles){
                delete v;
            }
        }
};


#endif