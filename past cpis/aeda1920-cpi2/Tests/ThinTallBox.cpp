#include "ThinTallBox.h"
#include "WideFlatBox.h"

ThinTallBox::ThinTallBox(double capacity) : Box(capacity) {
}

ThinTallBox::ThinTallBox(double capacity, stack<Object> objects, double content_size) : Box(capacity) {
	this->objects = objects;
	this->setContentSize(content_size);
}

stack<Object> ThinTallBox::getObjects() const {
    return objects;
}

void ThinTallBox::remove(Object object) {
	Object next_object = next();
	if(!(next_object == object)) {
		throw InaccessibleObjectException(object);
	} else {
		setContentSize(getContentSize()-next_object.getSize());
		objects.pop();
	}
}

const Object& ThinTallBox::next() const {
	return objects.top();
}

// TODO
void ThinTallBox::insert(Object object) {
    if(object.getSize()+this->getContentSize()>this->getCapacity() || this->full()){
        throw(ObjectDoesNotFitException());
    }
    this->objects.push(object);
    this->setContentSize(this->getContentSize()+object.getSize());
}

// TODO
void ThinTallBox::sortObjects() {
    WideFlatBox bb(this->getCapacity());
    while(!this->empty()){
        bb.insert(this->next());
        this->remove(this->next());
    }
    bb.sortObjects();
    while(!bb.empty()){
        this->insert(bb.next());
        bb.remove(bb.next());
    }
}
