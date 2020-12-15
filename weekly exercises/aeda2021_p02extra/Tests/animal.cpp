#include "animal.h"
#include <sstream>
#include <iostream>

using namespace std;

int Animal::youngest =-1;

Animal::Animal(string name, int age): name(name), age(age), vet(NULL) {
    if (Animal::youngest>age || Animal::youngest==-1) Animal::youngest=age;
}

string Animal::getName() const {
	return name;
}

int Animal::getAge() const {
    return age;
}

void Animal::setVeterinary(Veterinary *vet) {
    this->vet = vet;
}

Veterinary *Animal::getVeterinary() const {
    return vet;
}

int Animal::getYoungest() {
    return youngest;
}

string Animal::getInfo() const {
    string info = name + ", " + to_string(age);
    if (vet!=NULL) info += vet->getInfo();
    cout << info;
    return info;
}

Dog::Dog(string name, int age, string breed) : Animal(name,age), breed(breed) {}

bool Dog::isYoung() const {
    if (age<5) return true;
    return false;
}

string Dog::getInfo() const {
    string info= Animal::getInfo() + ", " + breed;
    cout << info;
    return info;
}

Flying::Flying(int maxv, int maxa) : maxVelocity(maxv), maxAltitude(maxa) {}

string Flying::getInfo() const {
    string info=", " + to_string(maxVelocity) + ", " + to_string(maxAltitude);
    cout << info;
    return info;
}

Bat::Bat(string name, int age, int maxv, int maxa): Animal(name,age), Flying(maxv,maxa) {}

bool Bat::isYoung() const {
    if (age<4) return true;
    return false;
}

string Bat::getInfo() const {
    string info=Animal::getInfo() + Flying::getInfo();
    cout << info;
    return info;
}