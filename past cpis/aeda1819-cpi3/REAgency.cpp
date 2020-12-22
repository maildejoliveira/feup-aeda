#include "REAgency.h"

REAgency::REAgency(): catalogItems(PropertyTypeItem("", "","", 0)) {
	//do nothing!
}

REAgency::REAgency(vector<Property*> properties): catalogItems(PropertyTypeItem("", "","", 0)) {
	this->properties = properties;
}

void REAgency::addProperty(Property* property) {
	this->properties.push_back(property);
}

void REAgency::addProperties(vector<Property*> properties) {
	this->properties = properties;
}

vector<Property*> REAgency::getProperties() const{
	return this->properties;
}

PropertyTypeItem REAgency::getTypeItem(string address, string postalCode, string typology) {
	PropertyTypeItem itemNotFound("", "", "", 0);
	BSTItrIn<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getAddress() == address && it.retrieve().getPostalCode() == postalCode && it.retrieve().getTypology() == typology) {
			PropertyTypeItem pti(it.retrieve().getAddress(), it.retrieve().getPostalCode(), it.retrieve().getTypology(), 0);
			pti.setItems(it.retrieve().getItems());
			return pti;
		}
		it.advance();
	}
	return itemNotFound;
}

void REAgency::addTypeItem(Property* property) {
	PropertyTypeItem itemNotFound("", "","", 0);
	PropertyTypeItem pti(property->getAddress(), property->getPostalCode(), property->getTypology(), property->	getPrice());
	PropertyTypeItem ptiX = catalogItems.find(pti);
	if(ptiX == itemNotFound) {
		pti.addItems(property);
		this->catalogItems.insert(pti);
	}
	else {
		this->catalogItems.remove(ptiX);
		ptiX.addItems(property);
		this->catalogItems.insert(ptiX);
	}
	properties.push_back(property);
}

BST<PropertyTypeItem> REAgency::getTypeItems() const {
	return this->catalogItems;
}

vector<ClientRecord> REAgency::getClientRecords() const {
	vector<ClientRecord> records;
	HashTabClientRecord::const_iterator it1 = this->listingRecords.begin();
	HashTabClientRecord::const_iterator it2 = this->listingRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void REAgency::setClientRecords(vector<ClientRecord>& crs) {
	for(unsigned int i = 0; i < crs.size(); i++) {
		listingRecords.insert(crs[i]);
	}

}

priority_queue<Client> REAgency::getClientProfiles() const {
	return clientProfiles;
}

void REAgency::setClientProfiles(priority_queue<Client>& profiles) {
	clientProfiles = profiles;
}

//
// TODO: Part I   - BST
//

//TODO a)
void REAgency::generateCatalog() {
    PropertyTypeItem itemNotFound("", "","", 0);
    for(int i = 0; i<properties.size(); i++){
        PropertyTypeItem pti(properties[i]->getAddress(), properties[i]->getPostalCode(), properties[i]->getTypology(), properties[i]->getPrice());
        PropertyTypeItem ptiX = catalogItems.find(pti);
        if(ptiX == itemNotFound) {
            pti.addItems(properties[i]);
            this->catalogItems.insert(pti);
        }
        else {
            this->catalogItems.remove(ptiX);
            ptiX.addItems(properties[i]);
            this->catalogItems.insert(ptiX);
        }
    }
}

//TODO b)
vector<Property*> REAgency::getAvailableProperties(Property* property) const {
	vector<Property*> temp;
    BSTItrIn<PropertyTypeItem> itrIn(catalogItems);
    while(!itrIn.isAtEnd()){
        if(itrIn.retrieve().getAddress()==property->getAddress() && itrIn.retrieve().getPostalCode()==property->getPostalCode() && itrIn.retrieve().getTypology()==property->getTypology()){
            vector <Property*> items = itrIn.retrieve().getItems();
            for(int i = 0; i!= items.size(); i++){
                if(get<0>(items[i]->getReservation())==NULL){
                    temp.push_back(items[i]);
                }
            }
        }
        itrIn.advance();
    }
	return temp;
}

//TODO c)
bool REAgency::reservePropertyFromCatalog(Property* property, Client* client, int percentage) {
    BSTItrIn<PropertyTypeItem> itrIn(catalogItems);
    while(!itrIn.isAtEnd()){
        if(itrIn.retrieve().getAddress()==property->getAddress() && itrIn.retrieve().getPostalCode()==property->getPostalCode() && itrIn.retrieve().getTypology()==property->getTypology()){
            vector <Property*> items = itrIn.retrieve().getItems();
            for(int i = 0; i!= items.size(); i++){
                if(get<0>(items[i]->getReservation())==NULL){

                    int price = items[i]->getPrice()-(items[i]->getPrice()*(percentage))/100;
                    items[i]->setReservation(make_tuple(client,  price));
                    client->addVisiting(items[i]->getAddress(), items[i]->getPostalCode(), items[i]->getTypology(),
                                        to_string(items[i]->getPrice()));
                    return true;
                }
            }
        }
        itrIn.advance();

    }
	return false;
}

//
// TODO: Part II  - Hash Table
//

//TODO d)
void REAgency::addClientRecord(Client* client) {
    listingRecords.insert(client);
}

//TODO e)
void REAgency::deleteClients() {
    auto it=listingRecords.begin();
    while(it!=listingRecords.end()){
        if(get<0>((*it).getClientPointer()->getVisiting())=="" && get<1>((*it).getClientPointer()->getVisiting())=="" && get<2>((*it).getClientPointer()->getVisiting())=="" && get<3>((*it).getClientPointer()->getVisiting())=="" && (*it).getClientPointer()->getVisitedProperties().size()==0){
            it = listingRecords.erase(it);
        }
        else{
            it++;
        }
    }
}

//
// TODO: Part III - Priority Queue
//

//TODO f)
void REAgency::addBestClientProfiles(const vector<Client>candidates, int min) {
        for(int i=0; i<candidates.size(); i++){
            int reservations = 0;
            for(int j =0; j<properties.size(); j++){
                if(get<0>(properties[j]->getReservation())->getEMail()==candidates[i].getEMail()){
                    reservations++;
                }
            }
            int size = candidates[i].getVisitedProperties().size();
            int racio = reservations / size;
            if(reservations%size>0) racio++;
            if(racio > min){
                clientProfiles.push(candidates[i]);
            }
        }
}

//TODO g)s
vector<Property*> REAgency::suggestProperties() {
	vector<Property*> tempProperties;
	priority_queue<Client> notChanged = clientProfiles;
	while(!clientProfiles.empty()){
	  string postalCode = get<1>(clientProfiles.top().getVisiting());
	  int postCode = stoi(postalCode);
	  int reserved=true;
	  if(get<0>(properties[0]->getReservation())==NULL){
	      reserved=false;
	  }
	  int indx = 0; int min=(stoi(properties[0]->getPostalCode())-postCode);
	  for(int i=1; i<properties.size(); i++){
	      if(stoi(properties[i]->getPostalCode())-postCode<min && get<0>(properties[i]->getReservation())==NULL){
	          indx = i;
	          reserved=false;
	          min = stoi(properties[i]->getPostalCode())-postCode;
	      }
	  }
	  if(reserved==false){
          tempProperties.push_back(properties[indx]);
	  }
	  clientProfiles.pop();
	}
    clientProfiles=notChanged;
	return tempProperties;
}
