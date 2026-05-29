#include"Vehicle.h"
#include"Car.h"
#include"Motorcycle.h"
#include"VehicleManager.h"
#include<iostream>
#include<vector>
#include<string>
#include<stdexcept>
using namespace std;

void showmenu(){
    cout << "===============================================" << endl;
    cout << "       Vehicle Rental Management System       " << endl;
    cout << "===============================================" << endl;
    cout << "1. Add Vehicle" << endl;
    cout << "2. Display All Vehicles" << endl;
    cout << "3. Display Available Vehicles" << endl;
    cout << "4. Display Rented Vehicles" << endl;
    cout << "5. Search Vehicle" << endl;
    cout << "6. Rent Vehicle" << endl;
    cout << "7. Return Vehicle" << endl;
    cout << "8. Update Vehicle Information" << endl;
    cout << "9. Statistics" << endl;
    cout << "10. File Operations" << endl;
    cout << "11. Exit" << endl;
    cout << "===============================================" << endl;
}

int main() {
    VehicleManager<Vehicle> manager;
    while(true){
        showmenu();
        int n; cin >> n;
        switch (n){
            case 1:{
                manager.addVehicleByInput();
                break;
            }
            case 2:{
                manager.displayAllVehicle();
                break;
            }
            case 3:{
                manager.displayAvailableVehicle();
                break;
            }
            case 4:{
                manager.displayRentedVehicle();
                break;
            }
            case 5:{
                cout << "========== Search Menu ==========" << endl;
                cout << "1. Search by license plate" << endl;
                cout << "2. Search by brand" << endl;
                cout << "Please enter your choice: ";
                int s; cin >> s;
                if(s == 1){
                    cout << "Please enter a license plate: ";
                    string lp; cin >> lp;
                    auto t = manager.searchVehicle(lp);
                    if(t == nullptr){
                        cout << "Vehicle not find!" << endl;
                    }else{
                        cout << "Vehicle find! Enter 'yes' to get more information.";
                        string y; cin >> y;
                        if(y == "yes") t->displayInfo();
                    }
                }else if(s == 2){
                    cout << "Please enter brand: ";
                    string brand; cin >> brand;
                    manager.displayVehiclesByBrand(brand);
                }else{
                    cout << "Invalid choice!" << endl;
                }
                break;
            }
            case 6:{
                cout << "Please enter the license plate, your name and renting days : ";
                string lp; string rn; int days; cin >> lp >> rn >> days;
                manager.rentVehicle(lp,rn,days);
                break;
            }
            case 7:{
                cout << "Please enter the license plate: ";
                string lp; cin >> lp;
                manager.returnVehicle(lp);
                break;
            }
            case 8:{
                manager.updateVehicleInfo();
                break;
            }
            case 9:{
                cout << "========== Statistics Menu ==========" << endl;
                cout << "1. Sort Vehicles" << endl;
                cout << "2. Show Statistics" << endl;
                cout << "0. Back to Main Menu" << endl;
                cout << "Please enter your choice: ";
                int s; cin >> s;
                if(s == 2){
                    manager.displayStatistics();
                }else if(s == 1){
                    cout << "Please enter sort option: rate / year / brand / plate" << endl;
                    string input; cin >> input;
                    if(manager.sortByInput(input)) manager.displayAllVehicle();
                }else if(s == 0){
                    break;
                }else{
                    cout << "Invalid choice!" << endl;
                }
                break;
            }
            case 10:{
                cout << "========== File Operations ==========" << endl;
                cout << "1. Load from file" << endl;
                cout << "2. Save to data folder" << endl;
                cout << "0. Back to Main Menu" << endl;
                cout << "Please enter your choice: ";
                int f; cin >> f;
                if(f == 1){
                    cout << "Please enter file path to load: ";
                    string filename; cin >> filename;
                    try {
                        manager.loadFromFile(filename);
                        cout << "全部加载成功！" << endl;
                    } catch (const exception& e) {
                        cout << "错误：" << e.what() << endl;
                    }
                }else if(f == 2){
                    cout << "Please enter file name to save: ";
                    string filename; cin >> filename;
                    try {
                        manager.saveToFile("data/" + filename);
                        cout << "保存成功！" << endl;
                    } catch (const exception& e) {
                        cout << "错误：" << e.what() << endl;
                    }
                }else if(f == 0){
                    break;
                }else{
                    cout << "Invalid choice!" << endl;
                }
                break;
            }
            case 11:{
                cout << "Thanks for using the system!" << endl;
                
                return 0;
            }
            default:{
                cout << "Invalid choice!" << endl;
            }
        }
    }
    return 0;
}