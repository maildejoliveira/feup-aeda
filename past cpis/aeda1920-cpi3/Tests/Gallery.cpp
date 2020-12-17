#include "Gallery.h"
#include <ostream>
using namespace std;

Gallery::Gallery(vector<Paint*> c): catalog(PaintCatalogItem("", "", 0, 0.00)), collection(c) {

}

vector<Paint*> Gallery::getCollection() const {
    return collection;
}

void Gallery::setCollection(vector<Paint*> c) {
    collection = c;
}

priority_queue<ExhibitionItem> Gallery::getPaintsToShow() const {
    return paintsToShow;
}
HashTableAuthorRecord Gallery::getAuthorRecords () const {
    return  authorRecords;
}

void Gallery::addAuthorRecord(AuthorRecord ar) {
    authorRecords.insert(ar);
}

void Gallery::generateCatalog() {
    catalog.makeEmpty();
    for(int i = 0; i < collection.size(); i++) {
        catalog.insert(collection[i]);
    }
}

BST<PaintCatalogItem> Gallery::getCatalog() const {
    return catalog;
}


void Gallery::prepareExhibition() {
    while( !paintsToShow.empty())
        paintsToShow.pop();
    for(int i = 0; i < collection.size(); i++) {
        ExhibitionItem ei(collection[i]);
        paintsToShow.push(ei);
    }
}

//-------------------------------------------------------------------------------

//TODO a)
vector<Paint*> Gallery::getPaintsBy(string a) const {
    vector<Paint*> tmp;
    BSTItrIn<PaintCatalogItem> itrIn(catalog);
    while(!itrIn.isAtEnd()){
        if(itrIn.retrieve().getAuthor()==a){
            tmp.push_back(itrIn.retrieve().getPaint());
        }
        itrIn.advance();
    }
    return tmp;
}

//TODO b)
vector<Paint*> Gallery::getPaintsBetween(int y1, int y2) const {
    vector<Paint*> tmp;
    BSTItrIn<PaintCatalogItem> itrIn(catalog);
    while(!itrIn.isAtEnd()){
        if(itrIn.retrieve().getYear()>=y1 && itrIn.retrieve().getYear()<=y2){
            tmp.push_back(itrIn.retrieve().getPaint());
        }
        itrIn.advance();
    }
    return tmp;
}

//TODO c)
bool Gallery::updateTitle(Paint* p, string tnew) {
    BSTItrIn<PaintCatalogItem> itrIn(catalog);
    bool suceed=false;
    while(!itrIn.isAtEnd()){
        if(itrIn.retrieve().getYear()==p->getYear() && itrIn.retrieve().getAuthor()==p->getAuthor() && itrIn.retrieve().getTitle()==p->getTitle() && itrIn.retrieve().getPrice()==p->getPrice()){
            p->changeTitle(tnew);
            itrIn.retrieve().getPaint()->changeTitle(tnew);
            suceed=true;
        }
        itrIn.advance();
    }
    return suceed;
}


//TODO d)
int Gallery::recordAvailablePainters() { //carrega a tabela de dispersao com AuthorRecords
    for(int i=0; i<collection.size(); i++){
        const AuthorRecord authorRecord(collection[i]->getAuthor());
        auto it = authorRecords.find(authorRecord);
        if(it._M_cur==NULL){
            AuthorRecord ar(collection[i]->getAuthor());
            authorRecords.insert(ar);
        }
        else if(it->getAuthor()==collection[i]->getAuthor()){
            AuthorRecord ar((*it).getAuthor(),(*it).getAvailablePaints(), (*it).getTotalSells());
            ar.addAvaliablePaint();
            authorRecords.erase(it);
            authorRecords.insert(ar);
        }
    }
    return authorRecords.size();
}

//TODO f)
double Gallery::totalSells() const {
    double total=0.0;
    for(auto it = authorRecords.begin(); it!=authorRecords.end(); it++){
        total += (*it).getTotalSells();
    }
    return total;
}

//TODO e)
double Gallery::sellPaint(string a, string t) {
    double price =0.0;
    const AuthorRecord authorRecord(a);
    auto it = authorRecords.find(authorRecord);
    if(it._M_cur==NULL){
        return price;
    }
    if(it->getAuthor()==a){
        AuthorRecord ar((*it).getAuthor(),(*it).getAvailablePaints(), (*it).getTotalSells());
        ar.subAvailablePaint();
        for(auto paints=collection.begin(); paints!=collection.end(); paints++){
            if ((*paints)->getAuthor()==a && (*paints)->getTitle()==t){
                price = (*paints)->getPrice() + 0.0;
                ar.recordSell(price);
                collection.erase(paints);
                break;
            }
        }
        authorRecords.erase(it);
        authorRecords.insert(ar);
    }
    return price;
}

//TODO
vector<Paint*> Gallery::nBestExibition(int n, int maxPerYear) {  //escolhe as N mais caras pinturas, dos anos mais antigos, para realizar uma exposição
    vector<Paint*> tmp;
    pair<int,int> year; //year and number of exbitions
    year.first=paintsToShow.top().getYear();
    year.second=0;
    priority_queue<ExhibitionItem> show;
    int numberOfPaintsSelected =0;
    while (!paintsToShow.empty()){
        if(numberOfPaintsSelected<n){
            if(year.first==paintsToShow.top().getYear() && year.second<maxPerYear){
                year.second++;
                numberOfPaintsSelected++;
                tmp.push_back(paintsToShow.top().getPaint());
            }
            else if(year.first<paintsToShow.top().getYear()){
                year.first=paintsToShow.top().getYear();
                year.second=1;
                numberOfPaintsSelected++;
                tmp.push_back(paintsToShow.top().getPaint());
            }
            else{
                show.push(paintsToShow.top());
            }
        }
        else{
            show.push(paintsToShow.top());
        }
        paintsToShow.pop();
    }
    paintsToShow=show;
    return tmp;
}

//TODO g)
int Gallery::itemExibitionOrder(string a, string t) {
    priority_queue<ExhibitionItem> show=paintsToShow;
    int counter =1;
    int indx = 0;
    while (!paintsToShow.empty()){
        if(paintsToShow.top().getAuthor()==a && paintsToShow.top().getTitle()==t){
            indx = counter;
        }
        counter++;
        paintsToShow.pop();
    }
    paintsToShow=show;
    return indx;
}

