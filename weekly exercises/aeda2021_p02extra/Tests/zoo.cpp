#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

unsigned Zoo::numAnimals() const {
    return animals.size();
}

unsigned Zoo::numVeterinarians() const {
    return veterinarians.size();
}

void Zoo::addAnimal(Animal *a1) {
    animals.push_back(a1);
}

string Zoo::getInfo() const {
    string info="";
    for (auto it=animals.begin();it!=animals.end(); ++it){
        info += (*it)->getInfo();
    }
    return info;
}

bool Zoo::isYoung(string nameA) {
    for (auto it=animals.begin();it!=animals.end(); ++it){
        if((*it)->getName()==nameA && (*it)->isYoung()) return true;
    }
    return false;
}

void Zoo::allocateVeterinarians(istream &isV) {
    string name1,name2, name;
    istringstream inStream;
    long cod;
    vector<Animal *>::iterator it=animals.begin();
    while(isV >> name1 >> name2 >> cod){
        name = name1 + " " + name2;
        Veterinary *v=new Veterinary(name, cod);
        veterinarians.push_back(v);
        (*it)->setVeterinary(v);
        ++it;
    }
    vector<Veterinary*>::iterator itv=veterinarians.begin();
    if (it!=animals.end()){
        (*it)->setVeterinary(*itv);
        ++it;
        ++itv;
    }
}

bool Zoo::removeVeterinary(string nameV) {
    bool exists=false;
    vector<Veterinary *>::iterator el;
    for (auto it=veterinarians.begin();it!=veterinarians.end(); ++it){
        if((*it)->getName()==nameV){
            exists=true;
            for (auto ita=animals.begin(); ita!=animals.end(); ++ita)
            {
                if ((*ita)->getVeterinary()==(*it)){
                    veterinarians.erase(it);
                    (*ita)->setVeterinary((*it));
                }
            }
            --it;
        }
    }
    return exists;
}

bool Zoo::operator<(Zoo &zoo2) const {
    int age1=0, age2=0;
    for (auto it=animals.begin(); it!=animals.end(); ++it){
        age1+=(*it)->getAge();
    }
    for (auto it=zoo2.animals.begin(); it!=zoo2.animals.end(); ++it){
        age2+=(*it)->getAge();
    }
    if(age1<age2) return true;
    return false;
}