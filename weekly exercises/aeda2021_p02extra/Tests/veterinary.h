#ifndef SRC_VETERINARY_H_
#define SRC_VETERINARY_H_

#include <string>
using namespace std;

class Veterinary {
    /**
     * Veterinary's name
     */
    string name;
    /**
     * Veterinary's code order
     */
    long codOrder;
public:
    /**
     * Constructor of the Veterinary's class
     * @param nome
     * @param cod
     */
    Veterinary(string nome, int cod);
    /**
     *
     * @return Veterinary's name
     */
    string getName() const;
    /**
     *
     * @return info concerning name and code of the veterinary
     */
    string getInfo() const;
};


#endif /* SRC_VETERINARY_H_ */
