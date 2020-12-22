#include "Warehouse.h"
#include <algorithm>

Warehouse::Warehouse()  {
}

queue<ThinTallBox> Warehouse::getBoxes() {
	return boxes;
}

queue<Object> Warehouse::getObjects() {
    return objects;
}

void Warehouse::setBoxes(queue<ThinTallBox> q) {
    while (!q.empty()) {
        boxes.push(q.front());
        q.pop();
    }
}

void Warehouse::addObject(Object o1) {
    objects.push(o1);
}

bool compObjOposite(const Object o1, const Object o2){
    return (o1.getSize()>o2.getSize());
}

//TODO
int Warehouse::InsertObjectsInQueue(vector <Object> obj){
    sort(obj.begin(), obj.end(), compObjOposite);
    int counter=0;
    for(int i=0; i<obj.size(); i++){
        this->addObject(obj[i]);
        counter++;
    }
    return counter;
}

//TODO
Object Warehouse::RemoveObjectQueue(int maxSize){
    queue<Object> objF;
    Object obj;
    bool existsMaxSize = false;
    bool exists=false;
    while(!objects.empty()){
        if(objects.front().getSize()<=maxSize && existsMaxSize == false){
            existsMaxSize = true;
            exists = true;
            obj = objects.front();
        }
        else{
            objF.push(objects.front());
        }
        objects.pop();
    }
    int max=0;
    objects = objF;
    if(!exists){
        Object o("dummy",maxSize);
        obj = o;
    }
    return obj;
}

//TODO
int Warehouse::addPackOfBoxes(vector <ThinTallBox> boV) {
    for(int i=0; i<boV.size(); i++){
        boxes.push(boV[i]);
    }
    return boxes.size();
}

//TODO
vector<ThinTallBox> Warehouse::DailyProcessBoxes() {
    vector<ThinTallBox> res;
    queue<ThinTallBox> final;
    while(!boxes.empty()){
        if(boxes.front().full()){
            res.push_back(boxes.front());
            boxes.pop();
        }
        else if(boxes.front().getDays()==0){
            int maxSize=boxes.front().getCapacity()-boxes.front().getContentSize();
            Object obj=RemoveObjectQueue(maxSize);
            if(obj.getName()=="dummy"){
                obj.setSize(0);
            }
            boxes.front().insert(obj);
            res.push_back(boxes.front());
            boxes.pop();
        }
        else {
            int maxSize=boxes.front().getCapacity()-boxes.front().getContentSize();
            Object obj=RemoveObjectQueue(maxSize);
            if(obj.getName()=="dummy"){
                obj.setSize(0);
            }
            boxes.front().insert(obj);
            boxes.front().setDaysToSend(boxes.front().getDays()-1);
            final.push(boxes.front());
            boxes.pop();
        }
    }
    return res;
}


