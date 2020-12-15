#ifndef ZOO_H_
#define ZOO_H_

#include "animal.h"
#include <vector>

class Zoo {
    /**
     * Vector of Animals from Zoo
     */
	vector<Animal *> animals;
	/**
	 * Vector of the Veterinarians of the Zoo
	 */
	vector<Veterinary *> veterinarians;
public:
    /**
     *
     * @return number of animals in zoo
     */
	unsigned numAnimals() const;
	/**
	 *
	 * @return number of veterinarians from zoo
	 */
	unsigned numVeterinarians() const;
	/**
	 * Add a new animal to the zoo
	 * @param a1
	 */
    void addAnimal(Animal *a1);
    /**
     *
     * @return info from all animals concerning name, age, vet, etc corresponding to the animal
     */
    string getInfo() const;
    /**
     * if animal with nameA is young
     * @param nameA
     * @return true if it is
     */
    bool isYoung(string nameA);
    /**
     * Set veterinarians presented on the file isV to the animals in zoo in order of apearance in the vectors
     * @param isV
     */
    void allocateVeterinarians(istream &isV);
    /**
     *  removes the veterinary with nameV from vector of veterinarians
     *  if any animal is atributted to that veterinary the new vet is going to be the next in line
     *  if there's not a vet with that nameA return false
     * @param nameV
     * @return true if possible to remove
     */
    bool removeVeterinary(string nameV);
    /**
     *  a zoo is smaller from zoo2 if the sum of ages from all animals in zoo1
     *  is less than the sum of ages from animals from zoo2
     * @param zoo2
     * @return
     */
    bool operator < (Zoo& zoo2) const;
};


#endif /* ZOO_H_ */
