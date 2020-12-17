#include <algorithm>
#include "WideFlatBox.h"

WideFlatBox::WideFlatBox(double capacity) : Box(capacity) {
}

void WideFlatBox::insert(Object object) {
	if(getContentSize()+object.getSize() <= getCapacity()) {
		objects.push_back(object);
		setContentSize(getContentSize()+object.getSize());
	} else {
		throw ObjectDoesNotFitException();
	}
}

const Object& WideFlatBox::next() const {
	return objects[0];
}

void WideFlatBox::sortObjects() {
	sort(objects.begin(), objects.end());
}

// TODO
void WideFlatBox::remove(Object object) {
    bool remove=false;
    vector<Object>::iterator it=objects.begin();
    for(it; it!=objects.end(); it++){
        if((*it)==object){
            objects.erase(it);
            it--;
            remove = true;
            setContentSize(getContentSize()-object.getSize());
        }
    }
    if(it==objects.end() && remove==false){
        throw(InaccessibleObjectException(object));
    }
}
