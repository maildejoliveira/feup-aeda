#include "vehicle.h"
#include <iostream>

using namespace std;

Vehicle::Vehicle(string b, int m, int y) : brand(b), month(m), year(y) {}

int Vehicle::getYear() const {
    return year;
}

string Vehicle::getBrand() const {
    return brand;
}

int Vehicle::info() const {
    cout << 3 << endl;
    return 3;
}

int Vehicle::info(ostream &o) const {
    o << "Brand: " << brand << endl;
    o << "Year: " << year << endl;
    o << "Month: " << month << endl;
    return 3;
}

bool Vehicle::operator<(const Vehicle &v) const {
    if (year<v.getYear()) return true;
    else if (year>v.getYear()) return false;
    else if(month>v.month) return false;
    else return true;
}

MotorVehicle::MotorVehicle(string b, int m, int y, string f, int cyl) : Vehicle(b,m,y), fuel(f), cylinder(cyl) {}

string MotorVehicle::getFuel() const {
    return fuel;
}

int MotorVehicle::info() const {
    cout << Vehicle::info()+2 << endl;
    return Vehicle::info()+2;
}

int MotorVehicle::info(ostream &o) const {
    int x=Vehicle::info(o);
    o << "Fuel: " << fuel << endl;
    o << "Cylinder: " << cylinder << endl;
    return x+2;
}

float MotorVehicle::calculateTax() const {
    if (fuel=="gas"){
        if (cylinder<=1000){
            if (year>1995) return 14.56;
            else return 8.10;
        }
        else if (cylinder<=1300){
            if (year>1995) return 29.06;
            else return 14.56;
        }
        else if (cylinder<=1750){
            if (year>1995) return 45.15;
            else return 22.65;
        }
        else if (cylinder<=2600){
            if (year>1995) return 113.98;
            else return 54.89;
        }
        else if (cylinder<=3500){
            if (year>1995) return 181.17;
            else return 87.13;
        }
        else{
            if (year>1995) return 320.89;
            else return 148.37;
        }
    }
    else{
        if (cylinder<=1500){
            if (year>1995) return 14.56;
            else return 8.10;
        }
        else if (cylinder<=2000){
            if (year>1995) return 29.06;
            else return 14.56;
        }
        else if (cylinder<=3000){
            if (year>1995) return 45.15;
            else return 22.65;
        }
        else {
            if (year>1995) return 113.98;
            else return 54.89;
        }
    }
}

Car::Car(string b, int m, int y, string f, int cyl) : MotorVehicle(b,m,y,f,cyl) {}

int Car::info() const {
    cout << MotorVehicle::info() << endl;
    return MotorVehicle::info();
}

int Car::info(ostream &o) const {
    o << "Car " << endl;
    int x=MotorVehicle::info(o);
    return x;
}

Truck::Truck(string b, int m, int y, string f, int cyl, int ml): MotorVehicle(b,m,y,f,cyl), maximumLoad(ml) {}

int Truck::info() const {
    cout << MotorVehicle::info()+1 << endl;
    return MotorVehicle::info()+1;
}

int Truck::info(ostream &o) const {
    o << "Truck " << endl;
    int x= MotorVehicle::info(o);
    o << "Maximum Load: " << maximumLoad << endl;
    return x+1;
}

Bicycle::Bicycle(string b, int m, int y, string t) : Vehicle(b,m,y), type(t){}

int Bicycle::info() const {
    cout << Vehicle::info()+1 << endl;
    return Vehicle::info()+1;
}

int Bicycle::info(ostream &o) const {
    o << "Bicycle " << endl;
    int x= Vehicle::info(o);
    o << "Type: " << type << endl;
    return x+1;
}

float Bicycle::calculateTax() const {
    return 0.0;
}

