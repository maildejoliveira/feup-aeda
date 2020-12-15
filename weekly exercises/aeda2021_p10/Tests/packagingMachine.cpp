#include "packagingMachine.h"
#include <sstream>

PackagingMachine::PackagingMachine(int boxCap): boxCapacity(boxCap)
{}

unsigned PackagingMachine::numberOfBoxes() {
    return boxes.size();
}

unsigned PackagingMachine::addBox(Box& b1) {
    boxes.push(b1);
    return boxes.size();
}

HeapObj PackagingMachine::getObjects() const {
    return this->objects;
}

HeapBox PackagingMachine::getBoxes() const {
    return this->boxes;
}


// TODO a)
unsigned PackagingMachine::loadObjects(vector<Object> &objs) {
    int counter =0;
    for(vector<Object>::iterator it = objs.begin(); it!= objs.end(); it++){
        if(it->getWeight()<=boxCapacity){
            objects.push(*it);
            objs.erase(it);
            it--;
            counter++;
        }
    }
	return counter;
}

// TODO b)
Box PackagingMachine::searchBox(Object& obj) {
	Box b;
	bool exists=false;
	HeapBox boxAux;
	while(!boxes.empty()){
        if(boxes.top().getFree()>=obj.getWeight() && !exists){
            b = boxes.top();
            exists = true;
            boxes.pop();
        }
        else{
            boxAux.push(boxes.top());
            boxes.pop();
        }
	}
	while(!boxAux.empty()){
	    boxes.push(boxAux.top());
	    boxAux.pop();
	}
	return b;
}

// TODO c)
unsigned PackagingMachine::packObjects() {
    while(!objects.empty()){
        Object ob(objects.top().getID(),objects.top().getWeight());
        Box b = searchBox(ob);
        b.addObject(ob);
        boxes.push(b);
        objects.pop();
    }
	return boxes.size();
}

// TODO d)
string PackagingMachine::printObjectsNotPacked() const {
    if(objects.empty())  return "No objects!\n";
    HeapObj obj = getObjects();
    string ans="";
    while(!obj.empty()){
        ans+= "O" + to_string(obj.top().getID()) + ":" + to_string(obj.top().getWeight()) + "\n";
        obj.pop();
    }
	return ans;
}

// TODO f)
Box PackagingMachine::boxWithMoreObjects() const {
    HeapBox boxesAux = boxes;
    if(boxesAux.empty()){
        throw MachineWithoutBoxes();
    }
    unsigned max=0;
    Box b = boxesAux.top();
    while(!boxesAux.empty()){
        b = boxesAux.top();
        if(b.getSize()>max){
            max = b.getSize();
        }
        boxesAux.pop();
    }
	return b;
}