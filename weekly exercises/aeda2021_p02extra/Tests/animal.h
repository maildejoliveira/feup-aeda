#ifndef SRC_ANIMAL_H_
#define SRC_ANIMAL_H_

#include "veterinary.h"
#include <string>
using namespace std;

class Animal {
protected:
    /**
     * Animal's name
     */
    string name;
    /**
     * Animal's age
     */
    int age;
    /**
     * Animal's specific Veterinary
     */
    Veterinary *vet;
    /**
     * is the age of the youngest animal
     */
    static int youngest;
public:
    /**
     * Constructor of the Animal class
     * @param name
     * @param age
     */
    Animal(string name, int age);
    /**
     * @brief Destructor
     */
    virtual ~Animal(){};
    /**
     *
     * @return Animal's name
     */
    string getName() const;
    /**
     *
     * @return Animal's age
     */
    int getAge() const;
    /**
     * Animal's Veterinary
     * @return
     */
    Veterinary *getVeterinary() const;
    /**
     * Set a specific Veterinary for this animal
     * @param vet
     */
    void setVeterinary(Veterinary *vet);
    /**
     *
     * @return age of the youngest animal that exists
     */
    static int getYoungest();
    /**
     *
     * @return info concerning name, age, name of the veterinary (if any)
     */
    virtual string getInfo() const;
    virtual bool isYoung() const = 0;
};


class Dog: public Animal {
    /**
     * Dog's breed
     */
    string breed;
public:
    /**
     * Constructor of the Dog class (derived class from Animal)
     * @param name
     * @param age
     * @param breed
     */
    Dog(string name, int age, string breed);
    /**
     * Dogs are young if the dog's age is less than 5
     * @return true if the dog's age is less than 5 else false
     */
    bool isYoung() const;
    /**
     *
     * @return info concerning name, age, name of the veterinary (if any) and breed
     */
    string getInfo() const;
};


class Flying {
    /**
     * Maximum Velocity reached by the flying
     */
    int maxVelocity;
    /**
     * Maximum Altitude reached by the flying
     */
    int maxAltitude;
public:
    /**
     * Constructor of the Flying class
     * @param maxv
     * @param maxa
     */
    Flying(int maxv, int maxa);
    /**
     *
     * @return info concerning maximum velocity and maximum altitude reached
     */
    virtual string getInfo() const;
};


class Bat: public Animal, public Flying {
public:
    /**
     * Constructor of the Bat class (derived from Animal and Flying)
     * @param name
     * @param age
     * @param maxv
     * @param maxa
     */
    Bat(string name, int age, int maxv, int maxa);
    /**
     * Bats are young if the bat's age is less than 5
     * @return true if the bat's age is less than 4 else false
     */
    bool isYoung() const;
    /**
     *
     * @return info concerning name, age, name of the veterinary (if any) and maximum velocity and maximum altitude reached
     */
    virtual string getInfo() const;
};

#endif /* SRC_ANIMAL_H_ */
